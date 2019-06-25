#include <ctype.h>
#include <stdio.h>
/*
 * Exercise 1
 * Page: 97
 * As written, getint treats a + or - not followed
 * by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input.
 * */
static int getch(void);
static void ungetch(int);

static int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch())) {
        ;
    }
    while (!isdigit(c) && c != EOF && c != (int)'+' && c != (int)'-') {
        ungetch(c);
        return 0;
    }
    sign = (c == (int)'-') ? -1 : 1;
    if (c == (int)'+' || c == (int)'-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
        }
    }
    if (isdigit(c)) {
        for (*pn = 0; isdigit(c); c = getch()) {
            *pn = 10 * *pn + (c - (int)'0');
        }
        *pn *= sign;
    }
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}
int main(void) {
    int x;
    x = -1;
    int y;
    y = getint(&x);
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

