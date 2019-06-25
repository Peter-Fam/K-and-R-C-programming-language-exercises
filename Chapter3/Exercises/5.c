#include <limits.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise 5
 * Page: 64
 * Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s .
 * In particular, itob(n,s,16) formats n 
 * as a hexadecimal integer in s .
 * */
static void itob(unsigned int n, /*@out@*/ char s[], unsigned short int b);
static void reverse(/*@in@*/ char s[]);
int main(void) {
    char s[100];
    unsigned int n = UINT_MAX;
    itob(n, s, 2);
    printf("%s,%u", s, n);
    return 0;
}
static void itob(unsigned int n, char s[], unsigned short int b) {
    int i;
    i = 0;
    do {
        if ((b > 1) && b < 36) {
            s[i++] = (char)((n % b)) + ((n % b) > 10 ? 'a' - (char)10 : '0');
        } else {
            s[i] = '\0';
            return;
        }
    } while ((n /= b) != 0);
    s[i] = '\0';
    reverse(s);
}
void reverse(/*@in@*/ char s[]) {
    int c, i, j;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        c    = (int)s[i];
        s[i] = s[j];
        s[j] = (char)c;
    }
}
