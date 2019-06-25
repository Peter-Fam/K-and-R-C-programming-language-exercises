#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise 17
 * Page: 121
 * Add a field-handling capability, so sorting may be done on fields within
 * lines ,each field sorted according to an independent set of options. (The
 * index for this book was sorted with -df for the index category and -n for the
 * page numbers.)
 * */

/*
 * each line would have several fields, each will be sorted among itself,
 * so we will need a field delimiter and a delimiter for the members of a field
 * for the sake of simplicity,the field delimiter is the '\t' character and the
 * member delimiter is the ',' character.
 *
 * arguments:
 * * each argument should start with a '-'
 * * number of arguments will determine the number of expected fields - 1
 * * last argument will be the options for the line sorting options
 * * fields with no sorting options will not be sorted
 * * the max number of fields will be MAXFIELDS , all fields after that number
 *   will be ignored
 * * in lines with incomplete number of fields, the existing fields will be
 *   sorted and missing fields are assumed to be missing from the end of the
 *   line.
 * * number of arguments larger than MAXFIELDS+1 will result in the program
 *   exiting with an error msg.
 * */

/* all valid arguments:
 *      -       normal sorting
 *      -r      reversed
 *      -n      numeric
 *      -d      directory
 *      -f      folded
 *      -nr     numeric reversed
 *      -rn     numeric reversed
 *      -fr     folded reversed
 *      -rf     folded reversed
 *      -df     directory folded
 *      -fd     directory folded
 *      -dr     directory reversed
 *      -rd     directory reversed
 *      -rfd    directory folded reversed
 *      -rdf    directory folded reversed
 *      -dfr    directory folded reversed
 *      -drf    directory folded reversed
 *      -fdr    directory folded reversed
 *      -frd    directory folded reversed
 *
 * we have two options here, either to create an function
 * that search and match each letter in the argument string to its option
 * and make sure that selected options are a valid combination.
 * or  to create a lookup table with all the valid combinations,
 * and compare the argument strings against it.
 *
 * for the sake of simplicity, we will go with second option, it's easier to
 * implement and maintain.
 **/

#define MAXLINES 5000

#define MAXFIELDS 12
#define MAXMEMBERS 128
#define OPTIONSNUM 19
#define MAXLEN 1000
#define FIELDDELIM "\t"
#define MEMBERDELIM ","
static char *lineptr[MAXLINES];

#define FOLDED (1 << 3)
#define DIR (1 << 2)
#define NUMERIC (1 << 1)
#define REVERSED (1 << 0)
static unsigned int fields_options[MAXFIELDS];
static int options_lookup[OPTIONSNUM] = {
    0,                       /* normal sorting           */
    REVERSED,                /* reversed                 */
    NUMERIC,                 /* numeric                  */
    DIR,                     /* directory                */
    FOLDED,                  /* folded                   */
    NUMERIC | REVERSED,      /* numeric reversed         */
    NUMERIC | REVERSED,      /* numeric reversed         */
    FOLDED | REVERSED,       /* folded reversed          */
    FOLDED | REVERSED,       /* folded reversed          */
    FOLDED | DIR,            /* folded directory         */
    FOLDED | DIR,            /* folded directory         */
    DIR | REVERSED,          /* directory reversed       */
    DIR | REVERSED,          /* directory reversed       */
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
    FOLDED | DIR | REVERSED, /* folded directory reversed*/
};

static int field_c;
static char *options[OPTIONSNUM] = {
    "-",    /* normal sorting           */
    "-r",   /* reversed                 */
    "-n",   /* numeric                  */
    "-d",   /* directory                */
    "-f",   /* folded                   */
    "-nr",  /* numeric reversed         */
    "-rn",  /* numeric reversed         */
    "-fr",  /* folded reversed          */
    "-rf",  /* folded reversed          */
    "-df",  /* folded directory         */
    "-fd",  /* folded directory         */
    "-dr",  /* directory reversed       */
    "-rd",  /* directory reversed       */
    "-rfd", /* folded directory reversed*/
    "-rdf", /* folded directory reversed*/
    "-dfr", /* folded directory reversed*/
    "-drf", /* folded directory reversed*/
    "-fdr", /* folded directory reversed*/
    "-frd"  /* folded directory reversed*/
};
static int argscmp(char *options[], int options_size, char *arg);
static int readlines(char *lineptr[], int nlines);
static void writelines(/*@in@*/ char *const lineptr[], int nlines);
static int numcmp(const char *s1, const char *s2);
static int f_strcmp(const char *s1, const char *s2);
static int d_strcmp(const char *s1, const char *s2);
static int fd_strcmp(const char *s1, const char *s2);
static void q_sort(void *lineptr[], int left, int right,
                   int (*comp)(void *, void *), int reverse);
static void sortFields(char *line);

static int (*compareFuncs[7])(const char *, const char *) = {
    strcmp, numcmp, d_strcmp, f_strcmp, f_strcmp, fd_strcmp, fd_strcmp};
int main(int argc, char *argv[]) {
    int nlines;
    int arg_c = argc;
    field_c   = argc - 1;
    while (--arg_c > 0) {
        int arg_option = argscmp(options, OPTIONSNUM, argv[arg_c]);
        if (arg_option == -1) {
            printf("Error: invalid Argument\n");
            return 1;
        } else {
            if (arg_c == argc - 1) {
                fields_options[0] = (unsigned int)arg_option;
            } else if (arg_c < MAXFIELDS) {
                fields_options[arg_c] = (unsigned int)arg_option;
            } else {
                printf("Error: Number of fields argument is bigger than"
                       "MAXFIELDS: %d, Argument no. %d %s will be ignored\n",
                       MAXFIELDS, arg_c, argv[arg_c]);
            }
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        q_sort(
            (void **)lineptr, 0, nlines - 1,
            ((int (*)(void *, void *))(compareFuncs[fields_options[0] >> 1])),
            (int)fields_options[0] & REVERSED);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

static void sortFields(char line[]) {
    char *fieldptr, field_buffer[MAXLEN];
    char *members[MAXMEMBERS];
    char line_buffer[MAXLEN] = "";
    int field_num            = 1;
    fieldptr                 = line;
    while (fieldptr != NULL) {
        strcpy(field_buffer, "");
        if (!(line == fieldptr)) { /* handling empty fields*/
            fieldptr++;
        } else {
            if (strncmp(fieldptr, FIELDDELIM, strlen(FIELDDELIM)) == 0) {
                fieldptr++;
            }
        }
        char *field_end = strstr(fieldptr, FIELDDELIM);
        if (field_end != NULL) { /* copying field to field buffer*/
            strncat(field_buffer, fieldptr, (size_t)(field_end - fieldptr));
        } else {
            strcat(field_buffer, fieldptr);
        }
        int i;
        char *tokenptr = strtok(field_buffer, MEMBERDELIM);
        for (i = 0; (tokenptr != NULL) && (i < MAXMEMBERS);
             i++) { /* tokenizing members */
            members[i] = tokenptr;
            tokenptr   = strtok(NULL, MEMBERDELIM);
        }
        members[i] = tokenptr; /* NULL trailling */
        if (field_num < field_c) {
            /* sort members if field options in provided*/
            q_sort((void **)members, 0, i - 1,
                   ((int (*)(void *, void *))(
                       compareFuncs[fields_options[field_num] >> 1])),
                   (int)fields_options[field_num] & REVERSED);
        }
        for (i = 0; members[i] != NULL; i++) {
            strcat(line_buffer, members[i]);
            members[i] = NULL;
            if (members[i + 1] != NULL) {
                strcat(line_buffer, MEMBERDELIM);
            }
        }
        if (field_end != NULL) {
            strcat(line_buffer, FIELDDELIM);
        }
        field_num++;
        fieldptr = strstr(fieldptr, FIELDDELIM);
    }
    strcpy(line, line_buffer);
}
static int argscmp(char *options[], int options_size, char *arg) {
    int result = -1;

    int i = 0;
    for (i = 0; i < options_size; i++) {
        if (strcmp(options[i], arg) == 0) {
            result = i;
            break;
        }
    }
    if (result == -1) {
        return result;
    } else {
        return options_lookup[result];
    }
}
static int get_line(/*@out@*/ char *s, int lim);

static /*@null@*/ char *allocc(int n);

/* readlines: read input lines*/
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    p      = NULL;
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = allocc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            sortFields(line);
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    p = NULL;
    return nlines;
}

/*writelines: line output lines */
void writelines(char *const lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

static void swap(void *v[], int i, int j);
/* q_sort: sort v[left] ... v[right] into increasing order */
void q_sort(void *v[], int left, int right, int (*comp)(void *, void *),
            int reverse) {
    int i, last;

    if (left >= right) {
        return;
    } else {
        swap(v, left, (left + right) / 2);
        last = left;
        for (i = left + 1; i <= right; i++) {
            if (reverse == 1 ? (*comp)(v[i], v[left]) > 0
                             : (*comp)(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        q_sort(v, left, last - 1, comp, reverse);
        q_sort(v, last + 1, right, comp, reverse);
    }
}

static int numcmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}
static int f_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (tolower(*s1) != tolower(*s2)) {
            return tolower(*s1) - tolower(*s2);
        }
        s2++;
        s1++;
    }
    if (*s1 != *s2) {
        return tolower(*s1) - tolower(*s2);
    }
    return 0;
}
static int fd_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if ((isalnum(*s1) || isspace(*s1)) && (isalnum(*s2) || isspace(*s2))) {
            if (tolower(*s1) != tolower(*s2)) {
                return tolower(*s1) - tolower(*s2);
            }
        }
        s2++;
        s1++;
    }
    if (*s1 != *s2) {
        return tolower(*s1) - tolower(*s2);
    }
    return 0;
}
static int d_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if ((isalnum(*s1) || isspace(*s1)) && (isalnum(*s2) || isspace(*s2))) {
            if (*s1 != *s2) {
                return (int)(*s1 - *s2);
            }
        }
        s2++;
        s1++;
    }
    if (*s1 != *s2) {
        return (int)(*s1 - *s2);
    }
    return 0;
}
/* getline: get line into s, return length*/
int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != (int)'\n') {
        s[i++] = (char)c;
    }
    if (c == (int)'\n') {
        s[i++] = (char)c;
    }
    s[i] = '\0';
    return i;
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *allocc(int n) { /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return (allocp - n);
    } else {
        return NULL;
    }
}
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}
