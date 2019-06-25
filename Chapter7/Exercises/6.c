#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exersice: 6
 * Page: 165
 * Write a program to compare two files, printing the first line where they
 * differ
 * */
#define MAXLEN 1000
int main(int argc, char *argv[]) {
    FILE *file1;
    FILE *file2;
    char line1[MAXLEN] = "";
    char line2[MAXLEN] = "";
    if (argc != 3) {
        fprintf(stderr,
                "Error: invalid number of arguments\n"
                "Useage: %s file1 file2 \n",
                argv[0]);
        exit(1);
    }
    if ((file1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: can not open %s", argv[1]);
        exit(2);
    }
    if ((file2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Error: can not open %s", argv[2]);
        exit(2);
    }
    long int nline = 1;
    while ((fgets(line1, MAXLEN, file1) != NULL) &&
           (fgets(line2, MAXLEN, file2) != NULL)) {
        if (strcmp(line1, line2) != 0) {
            printf("%ld:%s\n", nline, line1);
            exit(0);
        }
        nline++;
    }
    if (strcmp(line1, line2) != 0) {
        printf("%ld:%s\n", nline, line1);
        exit(0);
    }
    printf("No difference between %s and %s", argv[1], argv[2]);
    return 0;
}
