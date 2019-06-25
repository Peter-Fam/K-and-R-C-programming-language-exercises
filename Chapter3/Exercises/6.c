#include "../Examples/5.c"
#include <limits.h>
#include <stdio.h>
/*
 * Exercise 6
 * Page: 64
 * Write a version of itoa that accepts three arguments
 * instead of two. The third argument is a minimum field
 * width; the converted number must be padded with blanks
 * on the left if necessary to make it wide enough.
 * */
static void itoa(int n, /*@out@*/ char s[], unsigned int width);
int main(void) {
    char s[100];
    int n = INT_MIN;
    itoa(n, s, 100);
    printf("%s,%d", s, n);
    return 0;
}
static void itoa(int n, char s[], unsigned int width) {
    int i, sign;
    sign = n;
    i    = 0;
    do {
        s[i++] = (char)(sign < 0 ? -(n % 10) : n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    for (; i < (int)width; i++) {
        s[i] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

