#include <stdio.h>
#include <string.h>
/*
 * Exercise 1
 * Page: 71
 * Write the function strrindex(s,t) ,
 * which returns the position of the
 * rightmost occurrence of t in s ,
 * or -1 if there is none.
 * */
static int strrindex(const char s[], const char t[]);

int main(void) {
    char s1[] = "iis a tesiti";
    char s2[] = "is";
    printf("%d\n", strrindex(s1, s2));
    return 0;
}

static int strrindex(const char s[], const char t[]) {
    int i, j;
    for (i = (int)(strlen(s) - strlen(t)); i >= 0; i--) {
        for (j = 0; j < (int)strlen(t); j++) {
            if (s[i + j] != t[j]) {
                break;
            }
        }
        if (j == (int)strlen(t)) {
            return i;
        }
    }
    return -1;
}
