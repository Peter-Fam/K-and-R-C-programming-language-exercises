#include <stdio.h>
#include <string.h>
/*
 * Exercise 7
 * Page: 79
 * Write a routine ungets(s) that will push back
 * an entire string onto the input. Should ungets
 * know about buf and bufp ,
 * or should it just use ungetch ?
 * */

#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char)c;
}
void ungets(char s[]) {
    int i = (int)strlen(s);
    if (bufp + i >= BUFSIZE) {
        printf("ungets: string too long\n");
    } else {
        for (; i >= 0; i--) {
            buf[bufp++] = s[i];
        }
    }
}
int main(void) {
    return 0;
}
