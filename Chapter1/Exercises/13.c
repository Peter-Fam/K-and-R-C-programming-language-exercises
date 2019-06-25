#include <stdio.h>
/* Exercise 13
 * Page: 24
 * Write a program to print a histgram of the lengths of words in its input,
 * It is easy to draw the histogram with bars horizonatal; a vertical
 * orientaiton is more challanging.
 * */
/* TODO: better a definition for what makes word a word * */
#define IN 1
#define OUT 0
#define MAXCHARS 15
#define VMARGIN 3

int main(void) {
    int c, state;
    int words[MAXCHARS];
    int wc;
    int max;

    state = OUT;
    wc    = 0;
    int i;
    for (i = 0; i < MAXCHARS; i++) {
        words[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (!((c >= (int)'a' && c <= (int)'z') ||
              (c >= (int)'A' && c <= (int)'Z') ||
              (c >= (int)'0' && c <= (int)'9'))) {
            state = OUT;
            if (!(wc == 0)) {
                if (wc >= MAXCHARS)
                    wc = 0;
                ++words[wc];
                wc = 0;
            }
        } else if (state == OUT) {
            state = IN;
            ++wc;
        } else {
            ++wc;
        }
    }

    max = words[0];
    for (i = 1; i < MAXCHARS; i++) {
        if (max <= words[i])
            max = words[i];
    }

    for (i = max + VMARGIN; i > 0; i--) {
        int j = 0;
        printf("%3d|", i);
        for (j = 1; j < MAXCHARS; j++) {
            printf("%4s", words[j] >= i ? "|" : " ");
        }
        printf("%4s\n", words[0] >= i ? "|" : " ");
    }
    printf("%3s|", " ");
    for (i = 1; i < MAXCHARS; i++) {
        printf("%3d|", i);
    }
    printf("%+3d|\n", MAXCHARS);

    return 0;
}
