#include <stdio.h>

void usage(const char* prog)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "%s <infile> <outfile>\n", prog);
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        usage(argv[0]);
        return 2;
    }
    if (rename(argv[1], argv[2]) != 0) {
        perror("move");
    }
    return 0;
}
