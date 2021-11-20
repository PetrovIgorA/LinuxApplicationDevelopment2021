#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <optional>

#include <regex.h>

constexpr int ARGUMENTS_COUNT = 4;

enum : size_t 
{
    REGEX_ARG = 1,
    SUBSTITUTION_ARG = 2,
    STRING_ARG = 3
};

using pmatches_t = std::vector<regmatch_t>;

std::optional<std::string> simple_change(const std::string& substitution, const pmatches_t& pmatch, const std::string& str)
{
    std::string result = str.substr(0, pmatch[0].rm_so);
    const size_t sub_len = substitution.length();
    for (size_t i = 0; i < sub_len; ++i) {
        if (substitution[i] == '\\') {
            i += 1;
            if (i == sub_len) {
                std::cerr << "unterminated command" << std::endl;
                return {};
            }
            if (isdigit(substitution[i]))
            {
                size_t digit = substitution[i] - '0';
                if (digit < pmatch.size()) {
                    result += str.substr(pmatch[digit].rm_so, pmatch[digit].rm_eo - pmatch[digit].rm_so);
                } else {
                    std::cerr << "invalid reference \\" << digit << std::endl;
                    return {};
                }
            } else {
                result.push_back(substitution[i]);
            }
        } else {
            result.push_back(substitution[i]);
        }
    }

    return result + str.substr(pmatch[0].rm_eo);
}

int main(int argc, char *argv[])
{
    if (argc != ARGUMENTS_COUNT) {
        std::cerr << "Incorrect input. Usage:" << std::endl;
        std::cerr << "\t" << argv[0] << " <regexp> <substitution> <string>" << std::endl;
        return 2;
    }

    std::string regex_str = argv[REGEX_ARG];
    std::string substitution = argv[SUBSTITUTION_ARG];

    size_t match_n = std::count(regex_str.begin(), regex_str.end(), '(') + 1;
    regex_t regex;
    pmatches_t pmatch(match_n);
    
    if (regcomp(&regex, argv[REGEX_ARG], REG_EXTENDED)) {
        perror("regcomp");
        return 1;
    }

    if (!regexec(&regex, argv[STRING_ARG], match_n, pmatch.data(), 0)) {
        auto result = simple_change(substitution, pmatch, argv[STRING_ARG]);
        if (result.has_value()) {
            std::cout << result.value() << std::endl;
        }
    } else {
        std::cout << argv[STRING_ARG] << std::endl;
    }
    
    return 0;
}
