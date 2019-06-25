#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise: 8
 * Page: 165
 * Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 * */
#define PAGEBREAK 30
#define MAXLEN 80
static void filecopy(FILE *src, FILE *dist, int page_break, char *title);

int main(int argc, char *argv[]) {
    FILE *fp;
    char *prog = argv[0];

    if (argc == 1) {
        filecopy(stdin, stdout, PAGEBREAK, "stdin");
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s:can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout, PAGEBREAK, *argv);
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

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp, int page_break, char *title) {
    int nlines = 0;
    char line[MAXLEN];
    int npages = 0;
    while (fgets(line, MAXLEN, ifp) != NULL) {
        if (nlines++ % PAGEBREAK == 0) {
            fprintf(ofp, "---------------------%s :%d---------------------\n",
                    title, ++npages);
        }
        (void)fputs(line, ofp);
    }
}
