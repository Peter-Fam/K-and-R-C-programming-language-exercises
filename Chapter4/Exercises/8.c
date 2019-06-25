#include <stdio.h>
/*
 * Exercise 8
 * Page: 79
 * Suppose that there will never be
 * more than one character of pushback.
 * Modify getch and ungetch accordingly.
 * */

static int buf = EOF - 1;
int getch(void) {
    if (buf != (EOF - 1)) {
        int return_t = buf;
        buf          = EOF - 1;
        return return_t;
    } else {
        return getchar();
    }
}
void ungetch(int c) {
    buf = (int)c;
}
int main(void) {
    return 0;
}
