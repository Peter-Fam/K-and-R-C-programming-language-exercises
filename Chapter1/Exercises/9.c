#include <stdio.h>
/*
 * Exercise 9
 * Page: 20
 * Write a program to copy its input to its output,
 * replaceing each string of one or more blanks by a single blank
 * */
int main(void) {
    int c, last_c;

    last_c = 0;
    while ((c = getchar()) != EOF) {
        if (!(c == (int)' ' && last_c == (int)' ')) {
            /*@i@*/ putchar(c);
        }
        last_c = c;
    }

    return 0;
}
