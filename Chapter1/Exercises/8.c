#include <stdio.h>
/*
 * Exercise 8
 * Page: 20
 * Write a program to count blanks, tabs, and newlines.
 * */
int main(void) {
    int bs, tabs, nl;
    int c;

    bs   = 0;
    nl   = 0;
    tabs = 0;

    while ((c = getchar()) != EOF) {
        /*@i@*/ putchar(c);
        if (c == (int)' ')
            bs++;
        if (c == (int)'\t')
            tabs++;
        if (c == (int)'\n')
            nl++;
    }
    printf("Spaces:%5d,Tabs:%5d,New Lines:%5d.\n", bs, tabs, nl);

    return 0;
}
