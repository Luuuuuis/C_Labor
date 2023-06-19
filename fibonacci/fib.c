//
// Created by LUIBROS on 01.06.2023.
//


#include <stdio.h>

long fib(long n) {
    long a = 0;
    long b = 1;
    long c;

    for (long i = 0; i < n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }

    return a;
}



int main() {
    printf("%ld\n", fib(10));
    return 0;
}