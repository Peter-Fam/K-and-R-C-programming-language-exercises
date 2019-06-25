#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise 3
 * Page: 79
 * Given the basic framework, it's straightforward
 * to extend the calculator. Add the modulus ( % )
 * operator and provisions for negative numbers.
 * */
#define NUMBER '0'
#define MAXOP 100

static int getop(/*@out@*/ char s[]);
static void push(double num);
static double pop(void);

int main(void) {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 > 0 || op2 < 0) {
                push(pop() / op2);
            } else {
                printf("error: Zero Divisor\n");
            }
            break;
        case '%':
            op2 = pop();
            if (op2 > 0 || op2 < 0) {
                push((double)((int)pop() % (int)op2));
            } else {
                printf("error: Zero ModDivisor\n");
            }
            break;
        case '\n':
            printf("\t%.7g\n", pop());
            break;
        default:
            printf("error: Unknown Command\n");
            break;
        }
    }

    return 0;
}

#define MAXVAL 100
static int sp = 0;
static double val[MAXVAL];
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %f\n", f);
}
double pop(void) {
    if (sp >= 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
static void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char)c;
}

#include <ctype.h>
/*@ignore@*/
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    i    = 0;
    if (!isdigit(c) && c != '.') {
        if (c != '-') {
            return c;
        } else {
            int last = c;
            if (isspace(c = getch())) {
                ungetch(c);
                return '-';
            }
            ungetch(c);
            s[i] = last;
        }
    }
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    if (c == (int)'.') {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}
/*@endignore@*/

