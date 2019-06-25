#include <ctype.h>
#include <stdio.h>
/*
 * Exercise 2
 * Page: 97
 * Write getfloat , the floating-point analog of getint .
 * What type does getfloat return as its function value?
 * */
static int getch(void);
static void ungetch(int);

static int getfloat(double *pn) {
    double val, power, epower;

    int sign, esign, c;

    while (isspace(c = getch())) {
        ;
    }
    while (!isdigit(c) && c != EOF && c != (int)'+' && c != (int)'-') {
        ungetch(c);
        return -1;
    }
    sign = (c == (int)'-') ? -1 : 1;

    if (c == (int)'-' || c == (int)'+') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            return -1;
        }
    }
    for (val = 0.0; isdigit(c); c = getch()) {
        val = 10.0 * val + (double)(c - (int)'0');
    }
    if (c == (int)'.') {
        c = getch();
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        val = 10.0 * val + (double)(c - (int)'0');
        power *= 10;
    }
    if (tolower(c) == (int)'e') {
        c     = getch();
        esign = (c == (int)'-') ? -1 : 1;

        if (c == (int)'-' || c == (int)'+') {
            c = getch();
        }
        for (epower = 0; isdigit(c); c = getch()) {
            epower = 10.0 * epower + (double)(c - (int)'0');
        }
        for (; epower > 0; epower--) {
            if (esign < 0) {
                power *= 10;
            } else {
                power /= 10;
            }
        }
    }
    if (c != EOF) {
        ungetch(c);
    }
    *pn = sign * val / power;
    return 0;
}

int main(void) {
    int x;
    x = -1;
    int y;
    double z;
    z = 0.4;
    y = getfloat(&z);
    printf("%f\n", z);
    printf("%d", x);
    return 0;
}
#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
static void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char)c;
}

