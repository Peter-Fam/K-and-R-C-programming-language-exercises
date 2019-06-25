#include <stdio.h>
/*
 * Exercise 6
 * Page: 17
 * Verify that expression getchar()!=EOF is 0 or 1
 * */
int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        /*@i@*/ putchar(c);
        /*@i@*/ putchar((char)((c != EOF) + '0'));
    }
    /*@i@*/ putchar((char)((c != EOF) + '0'));

    return 0;
}
