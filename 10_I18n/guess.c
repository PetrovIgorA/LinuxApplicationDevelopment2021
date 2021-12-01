#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(eng_string) gettext(eng_string)

#define MIN_NUMBER 0
#define MAX_NUMBER 100
#define BUFFER_SIZE 16U
#define NUMBER_SCANF_FORMAT "%14s"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, "po");
    textdomain(PACKAGE);

    printf(_("Guess number between %d and %d\n"), MIN_NUMBER, MAX_NUMBER);

    int left_border = MIN_NUMBER - 1;
    int right_border = MAX_NUMBER;
    char buffer[BUFFER_SIZE];
    while (right_border - left_border > 1) {
        int middle = (left_border + right_border) / 2;
        while (1) {
            printf(_("Is your number greater than %d? Print 'yes' or 'no'\n"), middle);
            scanf(NUMBER_SCANF_FORMAT, buffer);
            if (!strcmp(buffer, _("yes"))) {
                left_border = middle;
            } else if (!strcmp(buffer, _("no"))) {
                right_border = middle;
            } else {
                printf("%s\n", _("Incorrect input, print 'yes' or 'no'"));
                continue;
            }
            break;
        }
    }
    printf(_("Answer: %d\n"), right_border);
    return 0;
}
