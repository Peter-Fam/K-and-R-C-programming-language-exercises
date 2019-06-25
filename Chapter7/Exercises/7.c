#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise:7
 * Page:165
 * Modify the pattern finding program of Chapter 5 to take its input from a set
 * of name files or, if no files are name as arguemts, fron the standard input,
 * Should the file name be printed when a matching line is found?
 * */
#define MAXLEN 1000
int main(int argc, char *argv[]) {
    FILE *fp;
    char *prog = argv[0];
    char line[MAXLEN];
    if (argc < 2) {
        fprintf(stderr, "%s:invalid argmuments\n", prog);
        exit(3);
    }
    char *pattern = *++argv;

    if (--argc == 1) {
        while (fgets(line, MAXLEN, stdin) != NULL) {
            if (strstr(line, pattern) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s:can't open %s\n", prog, *argv);
                exit(1);
            } else {
                while (fgets(line, MAXLEN, fp) != NULL) {
                    if (strstr(line, pattern) != NULL) {
                        printf("%s", line);
                    }
                }
                (void)fclose(fp);
            }
        }
    }
    if (ferror(stdout) > 0) {
        fprintf(stderr, "%s,error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}
