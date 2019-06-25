#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise: 5
 * Page: 145
 * Write a function undef that will remove a name and definition
 * from the table  maintained by lookup and install
 * */
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};
#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE] = {0}; /* pointer table */

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

int main(void) {
    char *defn         = "Hello";
    char *name         = "HELLO";
    struct nlist *list = NULL;
    list               = install(name, defn);
    printf("%s\n", lookup("HELLO")->defn);
    undef("HELLO");
    printf("%s\n", lookup("HELLO") != NULL ? lookup("HELLO")->defn : "null");
    return 0;
}
