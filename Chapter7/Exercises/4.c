#include <stdarg.h>
#include <stdio.h>
/*
 * Exercise: 4
 * Page: 159
 * Write a private version of scanf analogous to minprintf from the previous
 * section
 * */

static void minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int *ival;
    double *dval;

    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            continue;
        }
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int *);
            scanf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf("%lf", dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf("%s", sval);
            break;
        default:
            break;
        }
    }
    va_end(ap);
}
int main(void) {
    char test[100];
    int a;
    double b;
    minscanf("%s %d %f \n", test, &a, &b);
    printf("%s %d %f \n", test, a, b);
    return 0;
}
