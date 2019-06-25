#include <ctype.h>
#include <limits.h>
#include <stdio.h>
/*
 * Exercise 6
 * Page: 107
 * Rewrite appropriate programs from earlier chapters
 * and exercises with pointers instead of array indexing.
 * Good possibilities include getline (Chapters 1 and 4),
 * atoi , itoa , and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 * */
#define MAXLEN 100
static int get_line(char *s, int lim);
static void reverse(char s[]);
int main(void) {
    char s[MAXLEN] = "";
    while (get_line(s, MAXLEN - 1) > 0) {
        printf("%s\n", s);
        reverse(s);
        printf("%s\n", s);
    }
    return 0;
}
static int get_line(char *s, int lim) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != (int)'\n'; ++i) {
        if ((i < lim - 1))
            *s++ = (char)c;
    }
    if (c == (int)'\n' && (i < lim - 1)) {
        *s++ = (char)c;
        i++;
    }
    if ((i < lim - 1))
        *s++ = '\0';
    else {
        *s-- = '\0';
        *s   = '\n';
    }
    return i;
}
static void reverse(char *s) {
    char temp;
    char *s_iter = s;
    while (*s != '\0') {
        s++;
    }

    s--;
    while (s - s_iter > 0) {
        temp    = *s;
        *s      = *s_iter;
        *s_iter = temp;
        --s;
        ++s_iter;
    }
}
