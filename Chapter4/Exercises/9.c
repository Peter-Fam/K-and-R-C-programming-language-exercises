#include <stdio.h>
#include <string.h>
/*
 * Exercise 9
 * Page: 79
 * Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be
 * if an EOF is pushed back, then implement your design.
 * */

#define BUFSIZE 100
static int buf[BUFSIZE];
static int bufp = 0;
int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
void ungets(char s[]) {
    int i = (int)strlen(s);
    if (bufp + i >= BUFSIZE) {
        printf("ungets: string too long\n");
    } else {
        for (; i >= 0; i--) {
            buf[bufp++] = (int)s[i];
        }
    }
}
int main(void) {
    return 0;
}
