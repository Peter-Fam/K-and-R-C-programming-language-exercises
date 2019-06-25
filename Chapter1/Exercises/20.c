#include <stdio.h>
/*
 * Exercise 20
 * Page: 34
 * Write a program detab that replace tabs in the input with
 * the proper number of blanks to space to the next tab stop.
 * Assume a fixed set of tabs stops, say every n columns.
 * Should n be a variable or a symbolic parameter
 * Answer: Both
 * */
#define TABSTOP 8
#define MAXLINE 1000

static int get_line_detab(/*@out@*/ char line[], int maxline, int n_col);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line_detab(line, MAXLINE, TABSTOP)) > 0) {
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

