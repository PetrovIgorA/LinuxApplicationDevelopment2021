#include <stdio.h>
#include "outlib.h"
void output(char* str)
{
printf("%d: %s\012", Count++, str);
}

void usage(char* prog)
{
    // Change %s to %.6s for correct logs comparison
    fprintf(stderr,
        "%.6s v%.2f: Print all arguments\012\t"
        "Usage: %.6s arg1 [arg2 […]]\012",
        prog, VERSION, prog);
}