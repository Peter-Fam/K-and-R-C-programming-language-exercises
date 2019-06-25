#include <stdio.h>
/*
 * Exercise 21
 * Page: 34
 * Write a program entab that replaces strings of blanks
 * by the minimum number of tabs and blanks to achieve
 * the same spacing.
 * Use the same tab stops as for detab.
 * When Either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 * */
#define MAXLINE 1000

static int get_line_entab(/*@out@*/ char line[], int maxline, int n_col);

int main(void) {
    int len;
    char line[MAXLINE];

    printf("\e[4m");
    while ((len = get_line_entab(line, MAXLINE, 8)) > 0) {
        printf("\n%s\n%d\n", line, len);
    }
    printf("\e[0m");
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
            } else if (blanks > 0) {
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

