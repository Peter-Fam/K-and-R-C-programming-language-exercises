#include <stdio.h>
/*
 * Exercise 10
 * Page:20
 * Write a program to copy its input to its output,
 * replacing each tab by \t, each blank by \b and
 * each backslash by \\ . This makes tabs and blanks
 * and backslash visible in unambiguous way
 * */
int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == (int)' ') {
            /*@i@*/ putchar('\\');
            /*@i@*/ putchar('b');
        } else if (c == (int)'\t') {
            /*@i@*/ putchar('\\');
            /*@i@*/ putchar('t');
        } else if (c == (int)'\\') {
            /*@i@*/ putchar('\\');
            /*@i@*/ putchar('\\');
        } else {
            /*@i@*/ putchar(c);
        }
    }

    return 0;
}
