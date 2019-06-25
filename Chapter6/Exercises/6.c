#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise: 6
 * Page: 145
 * Implement a simple version of the #define processor (i.e., no arguments)
 * suitable for use with C Programs, based on the routines of this section,
 * you  may also find getch and ungetch helpful.
 * */
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};
#define HASHSIZE 101

#define ERROR "%s\n", "this is an error"
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: from hash value for string s */
unsigned int hash(char *s) {
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = (unsigned int)*s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

char *str_dup(char *s);

/* install : put (name,defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(struct nlist));
        if (np == NULL || (np->name = str_dup(name)) == NULL) {
            return NULL;
        }
        hashval          = hash(name);
        np->next         = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);
    }
    if ((np->defn = str_dup(defn)) == NULL) {
        return NULL;
    }

    return np;
}

/* undef: remove a defintioin and free the memory */
void undef(char *name) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) != NULL) {
        hashval          = hash(name);
        hashtab[hashval] = NULL;
        free((void *)np->name);
        free((void *)np->defn);
        free((void *)np);
    }
}
char *str_dup(char *s) {
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}
#define MAXWORD 101
enum STATE_DEFINE_E {
    IN_DEFINE,
    DEFINE_WORD,
    OUT_DEFINE,
};
static int getword(char *word, int lim);
int main(void) {
    char word[MAXWORD];
    int c;
    int state_define        = OUT_DEFINE;
    char name[MAXWORD]      = "";
    char defn[MAXWORD * 10] = "";
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (strcmp(word, "#define") == 0) {
            state_define = DEFINE_WORD;
        } else if (word[0] == '\n') {
            if (state_define == IN_DEFINE) {
                if (install(name, defn) == NULL) {
                    printf(ERROR);
                    return 1;
                }
                name[0] = '\0';
                defn[0] = '\0';
            }
            state_define = OUT_DEFINE;
        } else if (state_define == DEFINE_WORD) {
            strcpy(name, word + 1);
            state_define = IN_DEFINE;
        } else if (state_define == IN_DEFINE) {
            strcat(defn, word);
        }
        if (c != '/') {
            if (state_define == OUT_DEFINE) {
                char *lookup_p;
                if (isblank(word[0])) {
                    lookup_p = word + 1;
                } else {
                    lookup_p = word;
                }
                printf("%s", lookup(lookup_p) != NULL ? lookup(lookup_p)->defn
                                                      : word);
            } else {
                printf("%s", word);
            }
        }
    }
    return 0;
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
enum STATE_E { IN, OUT };
/* getword: get next word or character from auto auto auto input */
static int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isblank(c = getch())) {
        if (w == word) {
            *w++ = (char)c;
        }
    }
    if (c != EOF) {
        *w++ = (char)c;
    }
    int state = OUT;
    switch (c) {
    case '"':
        state = IN;
        while (state == IN) {
            c    = getch();
            *w++ = c;
            if (c == (int)'"') {
                state = OUT;
            } else if (c == (int)'\\') {
                c    = getch();
                *w++ = c;
            }
        }
        break;
    case '\'':
        state = IN;
        while (state == IN && c != EOF) {
            c    = getch();
            *w++ = c;
            if (c == (int)'\'') {
                state = OUT;
            } else if (c == (int)'\\') {
                c    = getch();
                *w++ = c;
            }
        }
        break;
    case '/':
        if ((c = getch()) == (int)'*') {
            state = IN;
        } else {
            ungetch(c);
        }
        while (state == IN && c != EOF) {
            c = getch();
            if (c == (int)'*') {
                if ((c = getch()) == (int)'/') {
                    state = OUT;
                } else {
                    ungetch(c);
                }
            }
        }
    default:
        break;
    }
    if (!isalpha(c) && c != (int)'_' && c != '#') {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = (char)getch()) && *w != '_') {
            ungetch((int)*w);
            break;
        }
    }
    *w = '\0';
    return (int)word[0];
}
