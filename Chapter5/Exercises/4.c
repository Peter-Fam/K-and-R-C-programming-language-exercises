#include <stdio.h>
#include <string.h>
/*
 * Exercise 4
 * Page:107
 * Write the function strend(s,t) , which returns 1
 * if the string t occurs at the end of the string s
 * ,and zero otherwise.
 * */
static int str_end(const char *s, const char *t);

int main(void) {
    char s[] = " this is a test";
    char t[] = "";
    printf("%d", str_end(s, t));
    return 0;
}

int str_end(const char *s, const char *t) {
    const char *s_end;
    if (strlen(s) < strlen(t)) {
        return 0;
    }
    while (*s != '\0') {
        s++;
    }
    s_end = s;
    while (*t != '\0') {
        t++;
    }
    while (s_end - s <= (int)strlen(t)) {
        if (*s-- != *t--) {
            return 0;
        }
    }
    return 1;
}
