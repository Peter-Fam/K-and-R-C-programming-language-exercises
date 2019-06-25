#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise: 18
 * Page: 126
 * Make dcl recover from input errors
 * */
/*
 * Recover from input errors is interrupted here as continue to operate after
 * faulty declarator without affecting the next declarator,
 * it doesn't try to correct the error or even identify it.
 * */
#define MAXTOKEN 1000
#define MAXLEN 10000
enum { NAME, PARENS, BRACKETS };

static void dcl(void);
static void dirdcl(void);

static int gettoken(void);
static int tokentype;
static char token[MAXTOKEN];
static char name[MAXTOKEN];
static char datatype[MAXTOKEN];
static char out[MAXLEN];

int main(void) {
    while (gettoken() != EOF) {
        if (tokentype != (int)'\n') { /* handle empty lines*/
            strcpy(datatype, token);
            out[0] = '\0';
            dcl();
            if (tokentype != (int)'\n') {
                printf("Syntax Error\n");
            } else { /* handles not printing faulty results*/
                printf("%s: %s %s\n", name, out, datatype);
            }
        }
    }
    return 0;
}
/*dcl: parse a declarator */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == (int)'*';) {
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/*dirdcl: parse a direct delarator */
void dirdcl(void) {
    int type;

    if (tokentype == (int)'(') {
        dcl();
        if (tokentype != (int)')') {
            printf("error: missing )\n");
        }
    } else if (tokentype == (int)')') { /* handles non-empty function parans*/
        printf("error:missing ) \n");
    } else {
        if (tokentype == NAME) {
            strcpy(name, token);
        } else {
            printf("error: expected name or (dcl)\n");
        }
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of ");
        }
    }
}

#define BUFSIZE 10000
static int buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
static void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == (int)' ' || c == (int)'\t') {
        ;
    }
    if (c == (int)'(') {
        if ((c = getch()) == (int)')') {
            strcpy(token, "()");
            return (tokentype = PARENS);
        } else {
            ungetch(c);
            return (tokentype = (int)'(');
        }
    } else if (c == (int)'[') {
        for (*p++ = (char)c; (*p++ = (char)getch()) != ']';) {
            if (*(p - 1) == '\n') {
                /* handles unexpected end of the line, a better handling
                           would be allowing only numbers between brackets */
                printf("error: expected ] before end of line\n");
                return (tokentype = (int)('\0'));
            }
        }
        *p = '\0';
        return (tokentype = BRACKETS);
    } else if (isalpha(c) || c == (int)'_') {
        for (*p++ = (char)c; isalnum(c = getch()) || c == (int)'_';) {
            *p++ = (char)c;
        }
        *p = '\0';
        ungetch(c);
        return (tokentype = NAME);
    } else {
        return (tokentype = c);
    }
}
