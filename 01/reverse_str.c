//
// Created by LUIBROS on 10.05.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXITEMS 10000 // mit 10000 Funktioniert es nicht :/

void reverseArray(char arr[][255], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        char temp[255];
        strcpy(temp, arr[start]);
        strcpy(arr[start], arr[end]);
        strcpy(arr[end], temp);
        start++;
        end--;
    }
}
char inputs[MAXITEMS][255];

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

    char input[255];
    int input_count = 0;

    while (fgets(input, sizeof(input), in) != NULL) {
        strcpy(inputs[input_count], input);
        input_count++;
    }

    reverseArray(inputs, input_count);

    for (int i = 0; i < input_count; i++) {
        printf("%s\n", inputs[i]);
    }

    if (in != stdin) {
        fclose(in);
    }

    exit(0);
}

