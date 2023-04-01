#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long** productor(unsigned long long** a, unsigned long long** b) {
    unsigned long long** result = (unsigned long long**)malloc(2 * sizeof(unsigned long long*));
    result[0] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));
    result[1] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));

    result[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % 1000000007;
    result[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % 1000000007;
    result[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % 1000000007;
    result[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % 1000000007;

    return result;
}

int main() {
    unsigned long long*** matrixPowOfM = (unsigned long long***)malloc(61 * sizeof(unsigned long long**));
    unsigned long long* numPowOf2 = (unsigned long long*)malloc(61 * sizeof(unsigned long long));
    unsigned long long** M = (unsigned long long**)malloc(2 * sizeof(unsigned long long*));
    unsigned long long** fiboM = (unsigned long long**)malloc(2 * sizeof(unsigned long long*));
    unsigned long long num;
    M[0] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));
    M[1] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));
    fiboM[0] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));
    fiboM[1] = (unsigned long long*)malloc(2 * sizeof(unsigned long long));
    M[0][0] = 1; M[0][1] = 1;
    M[1][0] = 1; M[1][1] = 0;
    fiboM[0][0] = 1; fiboM[0][1] = 0;
    fiboM[1][0] = 0; fiboM[1][1] = 1;
    int i;
    matrixPowOfM[0] = M;
    numPowOf2[0] = 1;
    numPowOf2[1] = 2;
    for (i = 1; i < 61; i++) {
        matrixPowOfM[i] = productor(matrixPowOfM[i - 1], matrixPowOfM[i - 1]);
    }
    for (i = 2; i < 61; i++) {
        numPowOf2[i] = numPowOf2[i - 1] * 2;
    }
    scanf("%llu", &num);
    for (i = 60; i >= 0; i--) {
        if (num >= numPowOf2[i]) {
            num -= numPowOf2[i];
            fiboM = productor(fiboM, matrixPowOfM[i]);
        }
    }
    printf("%llu", fiboM[0][1]);

    return 0;
}