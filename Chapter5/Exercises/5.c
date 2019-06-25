#include <stdio.h>
#include <string.h>
/*
 * Exercise 5
 * Page: 107
 * Write versions of the library functions strncpy
 * ,strncat ,and strncmp ,which operate on at most
 * the first n characters of their argument strings.
 * For example, strncpy(s,t,n) copies at most n
 * characters of t to s.
 * Full descriptions are in Appendix B.
 * */
static void strn_cat(char *s, const char *t, int n);
static void strn_cpy(char *s, const char *t, int n);
static int strn_cmp(const char *s, const char *t, int n);

int main(void) {
    char s[100] = "This is a test";
    char *t     = "This is b test";
    char d[100] = "";
    printf("%s\n%s\n%s\n", d, t, s);
    strn_cpy(d, s, 10);
    strn_cat(d, t, 10);
    printf("%d\n", strn_cmp(s, t, 110));
    printf("%s\n%s\n%s\n", d, t, s);
    return 0;
}

void strn_cat(char *s, const char *t, int n) {
    while (*s != '\0') {
        s++;
    }
    char *const s_end = s;
    while ((*s = *t) != '\0' && s - s_end <= n) {
        s++;
        t++;
    }
}
void strn_cpy(char *s, const char *t, int n) {
    char *const s_begin = s;
    while ((*s = *t) != '\0' && s - s_begin <= n) {
        s++;
        t++;
    }
}
int strn_cmp(const char *s, const char *t, int n) {
    const char *const s_begin = s;
    while (s - s_begin <= n) {
        if (*s != *t) {
            return (int)(*s - *t) > 0 ? 1 : -1;
        }
        s++;
        t++;
    }
    return 0;
}
