#include <stdio.h>
/* Exercise 14
 * Page: 24
 * Writ a program to print a histogram of
 * the frequencies of different character in its input.
 * */
#define CHARSNUM 26
#define VMARGIN 3

int main(void) {
    int c;
    int chars[CHARSNUM];
    int max;

    int i;
    for (i = 0; i < CHARSNUM; i++) {
        chars[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (((c >= (int)'a' && c <= (int)'z'))) {
            ++chars[c - (int)'a'];
        }
    }

    max = chars[0];
    for (i = 1; i < CHARSNUM; i++) {
        if (max <= chars[i])
            max = chars[i];
    }

    for (i = max + VMARGIN; i > 0; i--) {
        int j = 0;
        printf("%3d|", i);
        for (j = 0; j < CHARSNUM; j++) {
            printf("%4s", chars[j] >= i ? "|" : " ");
        }
        printf("\n");
    }
    printf("%3s|", " ");
    for (i = 0; i < CHARSNUM; i++) {
        printf("%3c|", i + (int)'a');
    }
    printf("\n");

    return 0;
}
