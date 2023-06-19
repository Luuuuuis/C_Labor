//
// Created by LUIBROS on 10.05.2023.
//

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *in = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    // zahlen aus stdin
    char temp[10000];
    while ((fgets(temp, 10000, in)) != NULL) {
        int count = strtol(temp, NULL, 10);
        printf("%d\n", count * 2);
    }

    if (in != stdin) {
        fclose(in);
    }
    exit(EXIT_SUCCESS);

}