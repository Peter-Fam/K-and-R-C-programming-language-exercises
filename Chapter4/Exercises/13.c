#include <stdio.h>
#include <string.h>
/*
 * Exercise 13
 * Page: 88
 * Write a recursive version of the
 * function reverse(s) , which reverses
 * the string s in place.
 * */
static void reverse(char s[], int i, int j);
int main(void) {
    char s[] = "1324ahffahfa=";
    reverse(s, 0, (int)strlen(s) - 1);
    printf("%s\n", s);
    return 0;
}
static void reverse(char s[], int i, int j) {
    if (i >= j) {
        return;
    }
    char temp;
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    reverse(s, ++i, --j);
}

