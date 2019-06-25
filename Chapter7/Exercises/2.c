#include <ctype.h>
#include <stdio.h>
/*
 * Exercise: 2
 * Page: 155
 * Write a program that will print arbitrary input in a sensible way. As a
 * minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 * */
#define WIDTH 40
int main(void) {
    int c;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (isgraph(c) || isspace(c)) {
            (void)putchar(c);
        } else {
            printf("0X%x", (unsigned int)c);
        }
        if (c == (int)'\n') {
            i = 0;
        } else {
            i++;
            if (i % WIDTH == 0) {
                (void)putchar('\n');
            }
        }
    }
    return 0;
}
