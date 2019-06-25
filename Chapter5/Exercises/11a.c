#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise 11 (entab)
 * Page: 118
 * Modify the programs entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments. Use the default tab settings
 * if there are no arguments.
 * */
#define MAXLINE 1000
#define ENTABSTOP 8
static int get_line_entab(/*@out@*/ char line[], int maxline, int n_col);

int main(int argc, char **argv) {
    int len;
    char line[MAXLINE];
    int entab = ENTABSTOP;
    while (--argc > 0) {
        if (argc == 1) {
            entab = atoi(*(++argv));
            if (entab <= 0) {
                printf("Error: invalid argument\nPlease, provide correct n "
                       "where n > 0\n");
                return -1;
            }
        } else {
            printf("Error: invalid number of argument\n");
            return -1;
        }
    }
    while ((len = get_line_entab(line, MAXLINE, entab)) > 0) {
        printf("\n%s\n%d\n", line, len);
    }
    return 0;
}

static int get_line_entab(char s[], int lim, int n_col) {
    int c, i, screen_index, blanks;

    screen_index = 0;
    blanks       = 0;
    i            = 0;
    while ((c = getchar()) != EOF && c != (int)'\n' && i < lim - 1) {
        if (c != (int)' ' && c != (int)'\t') {
            if ((blanks > 0) && (screen_index % n_col == 0)) {
                s[i++] = '\t';
                blanks = 0;
            } else {
                while (blanks > 0) {
                    s[i++] = ' ';
                    blanks--;
                }
            }
            s[i++] = (char)c;
        } else if (c == (int)'\t' ||
                   (screen_index % n_col == (n_col - 1) && blanks > 0)) {
            s[i++] = '\t';
            blanks = 0;
        } else {
            blanks += 1;
        }

        if (c == (int)'\t') {
            screen_index += n_col - (screen_index % n_col);
        } else {
            screen_index += 1;
        }
    }
    if (c == (int)'\n' && (i < lim - 1)) {
        s[i] = (char)c;
        i++;
    }
    if ((i < lim - 1)) {
        s[i] = '\0';
    } else {
        s[lim - 1] = '\0';
        s[lim - 2] = '\n';
    }
    return i;
}
