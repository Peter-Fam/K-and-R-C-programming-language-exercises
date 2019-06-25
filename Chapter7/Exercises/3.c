#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

/* minprintf: minimal printf with variable arguement list */
static void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    unsigned int uval;
    void *pval;

    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            (void)putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'c':
            ival = va_arg(ap, int);
            (void)putchar(ival);
            break;
        case 'u':
            uval = va_arg(ap, unsigned int);
            printf("%u", uval);
            break;
        case 'o':
            uval = va_arg(ap, unsigned int);
            printf("%o", uval);
            break;
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned int);
            printf("%x", uval);
            break;
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'i':
            ival = va_arg(ap, int);
            printf("%i", ival);
            break;
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'e':
        case 'E':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval != '\0'; sval++) {
                (void)putchar(*sval);
            }
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        default:
            (void)putchar(*p);
            break;
        }
    }
    va_end(ap);
}
int main(void) {
    minprintf("%s %d %f %s\n %p %e %g %x", "this is a test", 34, 23.4, "434",
              minprintf, 2.3, .23, 34u);
    return 0;
}
