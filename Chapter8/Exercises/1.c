#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 * Exercise: 1
 * Page: 174
 * Rewrite the program cat from chapter 7 using read,write, open and close
 * instead of their standard library equivalents. Preform experiments to
 * determine the relative speeds of the two versions.
 * */
static void filecopy(int src, int dist);

int main(int argc, char *argv[]) {
    int fp;
    char *prog = argv[0];

    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fp = open(*++argv, O_RDONLY, NULL)) < 0) {
                fprintf(stderr, "%s:can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, 1);
                (void)close(fp);
            }
        }
    }
    exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int ifp, int ofp) {
    int c;

    while (read(ifp, &c, 1) == 1) {
        write(ofp, &c, 1);
    }
}
