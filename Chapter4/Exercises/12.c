#include <limits.h>
#include <stdio.h>
/*
 * Exercise 12
 * Page: 88
 * Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string
 * by calling a recursive routine.
 * */
static int /*@alt void@*/ itoa(char s[], int n);
int main(void) {
    char s[100] = "";
    itoa(s, 1237001);
    printf("%s\n%d\n", s, 1237001);
    itoa(s, -1237001);
    printf("%s\n", s);
    itoa(s, INT_MIN);
    printf("%s\n%d\n", s, INT_MIN);
    itoa(s, INT_MAX);
    printf("%s\n", s);
    return 0;
}
static int itoa(char s[], int n) {
    int i    = 0;
    int sign = 1;
    if (n / 10 != 0) {
        i = itoa(s, n / 10);
    }

    if (n < 0) {
        sign = -1;
        if (i == 0) {
            s[i++] = '-';
        }
    }
    s[i]     = (char)((n % 10) * sign) + '0';
    s[i + 1] = '\0';
    return i + 1;
}

