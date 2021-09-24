#include <iostream>

#include "file_window.h"

static constexpr int ARGUMENTS_COUNT = 2;

int main(int argc, char* argv[])
{
    if (argc != ARGUMENTS_COUNT) {
        std::cerr << "Incorrect arguments count\nUsage:" << std::endl;
        std::cerr << argv[0] << " <file>" << std::endl;
        return 0;
    }

    FileWindow(argv[1]).Draw();

    return 0;
}
