//
// Created by LUIBROS on 10.05.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        exit(69);
    }

    int MAXINT = 1000;
    int count = strtol(argv[1], NULL, 10);

    srand(time(0));

    for (int i = 0; i < count; ++i) {
        printf("%d\n", rand() % MAXINT);
    }
}