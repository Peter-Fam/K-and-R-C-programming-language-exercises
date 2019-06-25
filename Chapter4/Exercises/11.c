#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise 11
 * Page: 83
 * Modify getop so that it doesn't need to use ungetch.
 * Hint: use an internal static variable.
 * */
#define NUMBER '0'
#define MAXOP 100
#define COMPLEX '1'
#define ANS 27

static int getop(/*@out@*/ char s[]);
static void push(double num);
static double pop(void);
static double peek(void);
static void duplicate(void);
static void swap_stack();
static void clear_stack();
static double complex_op(char s[]);
static unsigned int variables_check[28];
static double variables_val[28];
int main(void) {
    int type, lastop;
    double op2;
    char s[MAXOP];
    lastop = (int)'0';
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case COMPLEX:
            push(complex_op(s));
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
        case '?':
            printf("top of stack: %.7g\n", peek());
            break;
        case '\\':
            printf("saving answer\n");
            duplicate();
            break;
        case ',':
            printf("swaping stack top\n");
            swap_stack();
            break;
        case '!':
            clear_stack();
            break;
        case '\n':
            if (lastop != (int)'?' && lastop != (int)',') {
                variables_val[ANS] = pop();
                printf("\t%.7g\n", variables_val[ANS]);
            }
            break;
        default:
            if (islower(type)) {
                if (variables_check[type - (int)'a'] == 1) {
                    push(variables_val[type - (int)'a']);
                } else {
                    push((double)type);
                }
            } else {
                printf("error: Unknown Command\n");
            }
            break;
        }
        lastop = type;
    }

    return 0;
}
static double complex_op(char s[]) {
    if (strcmp(s, "sqrt") == 0) {
        return sqrt(pop());
    }
    if (strcmp(s, "sin") == 0) {
        return sin(pop());
    }
    if (strcmp(s, "cos") == 0) {
        return cos(pop());
    }
    if (strcmp(s, "asin") == 0) {
        return asin(pop());
    }
    if (strcmp(s, "ans") == 0) {
        return variables_val[ANS];
    }
    if (strcmp(s, "set") == 0) {
        double x = pop();
        char var = (char)pop();
        if (islower(var)) {
            variables_check[(int)var - (int)'a'] = 1;
            variables_val[(int)var - (int)'a']   = x;
            return x;
        } else {
            printf("Not Valid Variable Name\n");
        }
    }
    printf("Unknown complex command\n");
    return pop();
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
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
double peek(void) {
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
void clear_stack(void) {
    sp = 0;
}
void duplicate(void) {
    if (sp < MAXVAL) {
        val[sp] = val[sp - 1];
        sp++;
    } else {
        printf("error: stack full, can't duplicate");
    }
}
void swap_stack(void) {
    if (sp > 1) {
        double temp;
        temp        = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("stack too small to swap");
    }
}

#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}

#include <ctype.h>
/*@ignore@*/
int getop(char s[]) {
    int i, c;

    static int buf = EOF;
    while ((s[0] = c = (buf != EOF) ? buf : getch()) == ' ' || c == '\t') {
        buf = EOF;
    }
    buf  = EOF;
    s[1] = '\0';
    i    = 0;
    if (!isdigit(c) && c != '.') {
        int last = c;
        if (c != '-') {
            if (isalpha(c)) {
                if (isspace(c = getch())) {
                    return last;
                }
                buf = c;
            } else {
                return last;
            }
        } else {
            if (isspace(c = getch())) {
                return last;
            }
            buf  = c;
            s[i] = last;
        }
    }
    int return_type = NUMBER;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = (buf != EOF) ? buf : getch())) {
            buf = EOF;
        }
        if (c == (int)'.') {
            while (isdigit(s[++i] = c = getch())) {
                ;
            }
        }
    } else if (isalpha(c)) {
        while (isalpha(s[++i] = c = (buf != EOF) ? buf : getch())) {
            buf = EOF;
        }
        return_type = COMPLEX;
    }
    s[i] = '\0';
    if (c != EOF) {
        buf = c;
    }
    return return_type;
}
/*@endignore@*/
