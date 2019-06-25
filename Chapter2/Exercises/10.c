#include <stdio.h>
/*
 * Exercise 10
 * Page: 52
 * Rewrite the function lower, which converts upper case
 * letters to lower case, with a conditional expression 
 * instead of if-else .
 * */

static char lower(char c);

int main(void) {
    char s[] = "ABCJSjaldjadjkKAJLKDJLK";
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = lower(s[i]);
    }
    printf("%s", s);
    return 0;
}

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

