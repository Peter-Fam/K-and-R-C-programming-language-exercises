#include <stdio.h>
/*
 * Exercise 19
 * Page: 31
 * Write a function reverse(s) that reverse the character string s.
 * Use it to write a program that reverse its input line at a time
 * */
#define MAXLINE 1000

static int get_line(/*@out@*/ char line[], int maxline);
static void reverse(/*@in@*/ char s[]);

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
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

static void reverse(char s[]) {
    int index, i;
    char temp;
    for (i = 0; s[i] != '\0'; i++)
        ;
    index = i - 1;
    for (i = 0; i <= index / 2; i++) {
        temp         = s[i];
        s[i]         = s[index - i];
        s[index - i] = temp;
    }
}
