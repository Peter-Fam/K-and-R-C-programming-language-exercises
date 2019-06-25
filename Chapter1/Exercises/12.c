#include <stdio.h>
/* Exercise 12
 * Page:21
 * Write a Program that prints its input one word per line.
 * */
/* TODO: better a definition for what makes word a word * */
#define IN 1
#define OUT 0

int main(void) {
    int c, state;
    state = OUT;

    while ((c = getchar()) != EOF) {
        if (!((c >= (int)'a' && c <= (int)'z') ||
              (c >= (int)'A' && c <= (int)'Z') ||
              (c >= (int)'0' && c <= (int)'9'))) {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            /*@i@*/ putchar('\n');
        }
        /*@i@*/ putchar(c);
    }

    return 0;
}

