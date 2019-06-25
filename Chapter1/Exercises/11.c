#include <stdio.h>
/*
 * Exercise 11
 * Page: 21
 * how would you test the word count program?
 * what kind of input are most likely to uncover bugs if there are any?
 * */

#define IN 1
#define OUT 0

/*Using the word definition: a single distinct meaningful element of speech
 * or writing, used with others (or sometimes alone) to form a sentence
 * and typically shown with a space on either side
 * when written or printed.*/

/* Puncitation Marks are not words,
 * and it can be argued that numbers are not technically words
 * but for sake of simplicity, numbers will be considered words here.*/

/*** Input that can cause bugs ***/

/* 1. Puncitation marks with blank characters around it
 * will be counted as a word
 * e.g. "... but , this is ..."
 * the comma here will be wrongly erroneously counted as a word*/

int main(void) {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == (int)'\n')
            ++nl;
        if (c == (int)' ' || c == (int)'\n' ||
            c == (int)'\t') /* ||(c == '\'').... will solve bug no.1*/
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d", nl, nw, nc);

    return 0;
}

