#include <stdio.h>
/*
 * Exercise 2
 * Page: 42
 *  for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i){
 *      s[i] = c;
 *  }
 * Write a loop equivalent to the for loop above without using && or ||.
 * */
#define MAXLINE 100

int main(void) {
    int i, c, lim;
    lim = MAXLINE;
    char s[MAXLINE];
    for (i = 0; (c = getchar()) != EOF; i++) {
        if (i > lim - 1)
            break;
        if (c == (int)'\n')
            break;
        s[i] = (char)c;
    }

    return 0;
}
