#include <stdio.h>
/*
 * Exercise 16
 * Page: 30
 * Revise the main routine of the longest-line program so
 * it will correctly print the lenght of arbitrarily long
 * input lines, and as much as possible of the text
 * */
#define MAXLINE 1000

static int get_line(/*@out@*/ char line[], int maxline);
static void copy(/*@out@*/ char to[], /*@in@*/ char from[]);

int main(void) {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {
        /*@i@*/ printf("%s\n%d", longest, max); /* longest will be defined in
                                           copy and if max > 0,copy is called*/
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

static void copy(char to[], char from[]) {
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}
