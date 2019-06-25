#include <stdio.h>
/*
 * Exercise 18
 * Page: 31
 * Write a program to remove trailling blanks and
 * tabs from each line of input, and to delete
 * entirely blank lines.
 * */
#define MAXLINE 1000

static int get_line(/*@out@*/ char line[], int maxline);
static void r_strip(/*@in@*/ char s[]);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        r_strip(line);
        printf("%s", line);
    }
    return 0;
}

static int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != (int)'\n'; ++i) {
        if ((i < lim - 1))
            s[i] = (char)c;
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

static void r_strip(char s[]) {
    int index, i;
    index = 0;
    i     = 0;
    for (i = 0; s[i] != '\0'; ++i)
        ;
    index = i - 1;
    for (i = index; s[i] == '\t' || s[i] == ' ' || s[i] == '\n'; i--)
        s[i] = '\0';
    if (i > 0)
        s[i + 1] = '\n';
}
