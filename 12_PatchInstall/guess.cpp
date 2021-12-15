/** @file guess.cpp
 *  Usage: guess [OPTION...]
 *  Guess number in arabic or roman format from 0 to 100
 *  
 *    -r, --roman                Guess numbers in roman format;
 *    -?, --help                 Give this help list;
 *        --usage                Give a short usage message;
 *    -V, --version              Print program version;
 *  
 *  Report bugs to petrov.igor.a@gmail.com.
 */

#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <argp.h>

#include <string>
#include <iostream>
#include <unordered_map>

/**
 * Macros for gettext usage for translation
 */
#define GETTEXT(eng_string) gettext(eng_string)

constexpr int MIN_NUMBER = 0; /**< minimal value for guessing */
constexpr int MAX_NUMBER = 100; /**< maximum value for guessing */

const char *argp_program_version = "guess 1.0"; /**< version of guessing program */
const char *argp_program_bug_address = "petrov.igor.a@gmail.com"; /**< address for bug reporting */

/**
 * Transform arabic number to string value in roman format
 * @param value integer value in arabic format (from 0 to 100)
 * @return string in roman format
 */
std::string to_roman(int value)
{
    if (value == 0) {
        return "0";
    }
    struct romandata_t { unsigned int value; char const* numeral; };
    constexpr struct romandata_t romandata[] =
    {
        {100, "C"}, { 90, "XC"},
        { 50, "L"}, { 40, "XL"},
        { 10, "X"}, { 9, "IX"},
        { 5, "V"}, { 4, "IV"},
        { 1, "I"},
        { 0, NULL}
    };

    std::string result;
    for (const romandata_t* current = romandata; current->value > 0; ++current)
    {
        while (value >= current->value)
        {
             result += current->numeral;
             value -= current->value;
        }
    }
    return result;
}

/**
 * Transform string value in roman format to arabic number
 * @param number string in roman format (from 0 to 100)
 * @return value integer value in arabic format
 */
int to_arabic(std::string number)
{
    if (number == "0") {
        return 0;
    }
    static std::unordered_map<std::string, int> r_to_a = {
        { "I", 1 },
        { "II", 2 },
        { "III", 3 },
        { "IV", 4 },
        { "V", 5 },
        { "VI", 6 },
        { "VII", 7 },
        { "VIII", 8 },
        { "IX", 9 },
        { "X", 10 },
        { "XI", 11 },
        { "XII", 12 },
        { "XIII", 13 },
        { "XIV", 14 },
        { "XV", 15 },
        { "XVI", 16 },
        { "XVII", 17 },
        { "XVIII", 18 },
        { "XIX", 19 },
        { "XX", 20 },
        { "XXI", 21 },
        { "XXII", 22 },
        { "XXIII", 23 },
        { "XXIV", 24 },
        { "XXV", 25 },
        { "XXVI", 26 },
        { "XXVII", 27 },
        { "XXVIII", 28 },
        { "XXIX", 29 },
        { "XXX", 30 },
        { "XXXI", 31 },
        { "XXXII", 32 },
        { "XXXIII", 33 },
        { "XXXIV", 34 },
        { "XXXV", 35 },
        { "XXXVI", 36 },
        { "XXXVII", 37 },
        { "XXXVIII", 38 },
        { "XXXIX", 39 },
        { "XL", 40 },
        { "XLI", 41 },
        { "XLII", 42 },
        { "XLIII", 43 },
        { "XLIV", 44 },
        { "XLV", 45 },
        { "XLVI", 46 },
        { "XLVII", 47 },
        { "XLVIII", 48 },
        { "XLIX", 49 },
        { "L", 50 },
        { "LI", 51 },
        { "LII", 52 },
        { "LIII", 53 },
        { "LIV", 54 },
        { "LV", 55 },
        { "LVI", 56 },
        { "LVII", 57 },
        { "LVIII", 58 },
        { "LIX", 59 },
        { "LX", 60 },
        { "LXI", 61 },
        { "LXII", 62 },
        { "LXIII", 63 },
        { "LXIV", 64 },
        { "LXV", 65 },
        { "LXVI", 66 },
        { "LXVII", 67 },
        { "LXVIII", 68 },
        { "LXIX", 69 },
        { "LXX", 70 },
        { "LXXI", 71 },
        { "LXXII", 72 },
        { "LXXIII", 73 },
        { "LXXIV", 74 },
        { "LXXV", 75 },
        { "LXXVI", 76 },
        { "LXXVII", 77 },
        { "LXXVIII", 78 },
        { "LXXIX", 79 },
        { "LXXX", 80 },
        { "LXXXI", 81 },
        { "LXXXII", 82 },
        { "LXXXIII", 83 },
        { "LXXXIV", 84 },
        { "LXXXV", 85 },
        { "LXXXVI", 86 },
        { "LXXXVII", 87 },
        { "LXXXVIII", 88 },
        { "LXXXIX", 89 },
        { "XC", 90 },
        { "XCI", 91 },
        { "XCII", 92 },
        { "XCIII", 93 },
        { "XCIV", 94 },
        { "XCV", 95 },
        { "XCVI", 96 },
        { "XCVII", 97 },
        { "XCVIII", 98 },
        { "XCIX", 99 },
        { "C", 100 },
    };
    return r_to_a[number];
}

/**
 * Tranform number to string arabic or roman format
 * @param is_roman true if need represent string in roman format and false if in arabic
 * @param value integer value for representation
 * @return string representation of input number for choosen format
 */
std::string number_format(bool is_roman, int value)
{
    return is_roman ? to_roman(value) : std::to_string(value);
}

struct arguments
{
    /** @brief true if roman format is used ant false otherwise */
    bool roman = false;
};

/**
 * Parsing input arguments
 * @param key key for argument
 * @param arg unused
 * @param state pointer to arguments structure
 * @return error code
 */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{   
    /* Get the input argument from argp_parse, which we
    know is a pointer to our arguments structure. */
    struct arguments *arguments = (struct arguments *)(state->input);

    switch (key)
    {
    case 'r':
      arguments->roman = true;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess", "../share/locale");
    textdomain("guess");

    static char *doc = GETTEXT("Guess number in arabic or roman format from 0 to 100");
    static char args_doc[] = " ";
    static struct argp_option options[] = {
        {"roman", 'r', 0, 0, GETTEXT("Guess numbers in roman format")},
        { 0 }
    };
    struct arguments arguments;
    static struct argp argp = { options, parse_opt, args_doc, doc };
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    std::cout << GETTEXT("Guess number between 0 and ") << number_format(arguments.roman, 100) << std::endl;

    int left_border = MIN_NUMBER - 1;
    int right_border = MAX_NUMBER;
    std::string buffer;
    while (right_border - left_border > 1) {
        int middle = (left_border + right_border) / 2;
        while (1) {
            std::cout << GETTEXT("Is your number greater than ") << number_format(arguments.roman, middle) << GETTEXT("? Print 'yes' or 'no': ");
            std::cin >> buffer;
            if (buffer == GETTEXT("yes")) {
                left_border = middle;
            } else if (buffer == GETTEXT("no")) {
                right_border = middle;
            } else {
                std::cout << GETTEXT("Incorrect input, print 'yes' or 'no'") << std::endl;
                continue;
            }
            break;
        }
    }
    std::cout << GETTEXT("Answer: ") << number_format(arguments.roman, right_border) << std::endl;
    return 0;
}
