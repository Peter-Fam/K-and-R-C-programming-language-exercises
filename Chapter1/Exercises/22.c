#include <stdio.h>
/*
 * Exercise 22
 * Page: 34
 * Write a program to "fold" long input lines into two or
 * more shorter lines after the last non-blank character
 * that occurs before the n -th column of input.
 * Make sure your program does something intelligent with
 * very long lines, and if there are no blanks or tabs
 * before the specified column.
 * */
#define MAXLINE 1000
#define TABSTOP 8
#define COLUMN 40

static int get_line_folded(/*@out@*/ char line[], int maxline, int n_col);

int main(void) {
    int len;
    char line[MAXLINE];

    printf("\e[4m");
    while ((len = get_line_folded(line, MAXLINE, COLUMN)) > 0) {
        printf("\n%s\n%d\n", line, len);
    }
    printf("\e[0m");
    return 0;
}

static int get_line_folded(char s[], int lim, int n_col) {
    int c, i, screen_index, last_blank;

    screen_index = 0;
    i            = 0;
    last_blank   = -1;
    while ((c = getchar()) != EOF && c != (int)'\n' && i < lim - 1) {
        if (screen_index >= (n_col)) {
            if (last_blank >= 0) {
                s[last_blank] = '\n';
                last_blank    = i - last_blank;
                screen_index  = last_blank;
            } else {
                s[i++]       = '-';
                s[i++]       = '\n';
                screen_index = 0;
            }
            last_blank = -1;
        }

        if (c == (int)' ' || c == (int)'\t') {
            last_blank = i;
        }
        if (c == (int)'\t') {
            screen_index += TABSTOP - (screen_index % TABSTOP);
        } else {
            screen_index += 1;
        }
        s[i++] = (char)c;
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

