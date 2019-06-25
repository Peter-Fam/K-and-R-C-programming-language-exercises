#include <stdio.h>
/*
 * Exercise 14
 * Page: 91
 * Define a macro swap(t,x,y) that interchanges
 * two arguments of type t.
 * (Block structure will help.)
 * */
#define swap(type, x, y)                                                       \
    {                                                                          \
        type temp_##type##_swap;                                               \
        temp_##type##_swap = y;                                                \
        y                  = x;                                                \
        x                  = temp_##type##_swap;                               \
    }
int main(void) {
    int x    = 4;
    int y    = 6;
    int temp = 9;
    int a[3] = {0, 3, 3};
    swap(int, a[2], a[1]);
    swap(int, x, y);
    printf("%d, %d", x, y);
    printf("%d, %d", temp, a[1]);
    return 0;
}
