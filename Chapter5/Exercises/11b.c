#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise 11 (detab)
 * Page: 118
 * Modify the programs entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments. Use the default tab settings
 * if there are no arguments.
 * */
#define TABSTOP 8
#define MAXLINE 1000

static int get_line_detab(/*@out@*/ char line[], int maxline, int n_col);

int main(int argc, char **argv) {
    int len;
    char line[MAXLINE];

    int detab = TABSTOP;
    while (--argc > 0) {
        if (argc == 1) {
            detab = atoi(*(++argv));
            if (detab <= 0) {
                printf("Error: invalid argument\nPlease, provide correct n "
                       "where n > 0\n");
                return -1;
            }
        } else {
            printf("Error: invalid number of argument\n");
            return -1;
        }
    }
    while ((len = get_line_detab(line, MAXLINE, detab)) > 0) {
        printf("%s\n", line);
    }

    return 0;
}

static int get_line_detab(char s[], int lim, int n_col) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != (int)'\n'; ++i) {
        if ((i < lim - 1)) {
            if (c != (int)'\t') {
                s[i] = (char)c;
            } else {
                int blanks = n_col - (i % n_col);
                while (blanks != 0) {
                    s[i++] = ' ';
                    blanks--;
                }
                i--; /* as not to skip an index*/
            }
        }
    }

    if (c == (int)'\n' && (i < lim - 1)) {
        s[i] = (char)c;
        i++;
    }

    if ((i < lim - 1))
        s[i] = '\0';
    else {
        s[lim - 1] = '\0';
        s[lim - 2] = '\n';
    }
    return i;
}
