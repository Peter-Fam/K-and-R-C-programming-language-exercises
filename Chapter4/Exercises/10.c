#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise 10
 * Page: 79
 * An alternate organization uses getline
 * to read an entire input line;
 * this makes getch and ungetch unnecessary.  * Revise the calculator to use this approach.
 * */
#define MAXLEN 1000
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
static int i_line = 0;
static char line[MAXLEN];
static int get_line(char line[], int lim);
int main(void) {
    int type, lastop;
    double op2;
    char s[MAXOP];
    lastop = (int)'0';
    while (get_line(line, MAXLEN) > 0) {
        while (i_line < (int)strlen(line)) {
            type = getop(s);
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
        }
        i_line = 0;
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
static int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != (int)'\n'; ++i) {
        if ((i < lim - 1))
            s[i] = (char)c;
    }

    if (c == (int)'\n' && (i < lim - 1)) {
        s[i] = (char)c;
        i++;
    }

    if ((i < lim - 1)) {
        s[i] = '\0';
    } else {
        s[lim - 1] = '\0';
        s[lim - 2] = '\n';
    }

    return i;
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

#include <ctype.h>
int getop(char s[]) {
    int i = 0;
    while (isspace(s[i] = line[i_line]) && line[i_line] != '\n') {
        i_line++;
    }
    s[i + 1] = '\0';
    if (!isdigit(line[i_line]) && line[i_line] != '.') {
        if (isalpha(line[i_line]) || line[i_line] == '-') {
            if (isspace(line[i_line + 1])) {
                return (int)line[i_line++];
            }
        } else {
            return(int) line[i_line++];
        }
    }
    int return_type = (int)NUMBER;
    if (isdigit(s[i])) {
        while (isdigit(s[i] = line[i_line])) {
            i++;
            i_line++;
        }
        if (s[i] == '.') {
            i++;
            i_line++;
            while (isdigit(s[i] = line[i_line])) {
                i++;
                i_line++;
            }
        }
    } else if (isalpha(s[i])) {
        while (isalpha(s[i] = line[i_line])) {
            i++;
            i_line++;
        }
        return_type =(int) COMPLEX;
    }

    s[i] = '\0';
    return return_type;
}

