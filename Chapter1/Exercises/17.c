#include <stdio.h>
/*
 * Exercise 17
 * Page: 31
 * Write a program to print all input lines
 * that are longer than 80 characters.
 * */
#define MAXLINE 1000
#define MAXCHAR 80

static int get_line(/*@out@*/ char line[], int maxline);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > MAXCHAR)
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
    else
        s[lim - 1] = '\0';
    return i;
}

