#include "../Examples/5.c"
#include <limits.h>
#include <stdio.h>
/*
 * Exercise 4
 * Page: 64
 * In a two's complement number representation,
 * our version of itoa does not handle the largest
 * negative number, that is, the value of n equal
 * to -(2 to the power (wordsize - 1)) .
 * Explain why not.
 * Modify it to print that value correctly regardless
 * of the machine on which it runs.
 * */
static void itoa(int n, /*@out@*/ char s[]);
int main(void) {
    char s[100];
    int n = INT_MIN;
    itoa(n, s);
    printf("%s,%d", s, n);
    return 0;
}
static void itoa(int n, char s[]) {
    int i, sign;
    sign = n;
    i    = 0;
    do {
        s[i++] = (char)(sign < 0 ? -(n % 10) : n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

