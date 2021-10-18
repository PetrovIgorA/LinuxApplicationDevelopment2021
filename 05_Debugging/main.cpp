#include <iostream>
#include "range.h"
#include <string>

void print_help(const char* argv_0)
{
    std::cerr << "Usage:\n";
    std::cerr << argv_0 << " <N> - range [0, ..., N - 1]\n";
    std::cerr << argv_0 << " <M> <N> - range [M, M + 1, ..., M + N -1]\n";
    std::cerr << argv_0 << " <M> <N> <S> - range [M, M + S, M + 2S, ..., N - 1]" << std::endl;
}

int main(int argc, char* argv[])
{
    Range range;
    if (argc <= 1 || argc > 4) {
        print_help(argv[0]);
        return 0;
    }
    else if (argc == 2) {
        range = Range(std::stoi(argv[1]));
    }
    else if (argc == 3) {
        range = Range(std::stoi(argv[1]), std::stoi(argv[2]));
    }
    else {
        range = Range(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    }

    for (auto it = range.begin(); it != range.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}