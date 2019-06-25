#include <stdio.h>
/*
 * Exercise 3
 * Page: 107
 * Write a pointer version of the function strcat
 * that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s.
 * */
static void str_cat(char *s, const char *t);

int main(void) {
    char s[100] = "this is a ";
    char t[]    = "test";
    str_cat(s, t);
    printf("%s\n", s);
    return 0;
}

void str_cat(char *s, const char *t) {
    while (*s != '\0') {
        s++;
    }
    while ((*s++ = *t++) != '\0') {
    }
}
