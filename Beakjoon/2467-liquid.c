#include <stdio.h>

#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int main() {
    int numLiquids, l, r, temp;
    int result[3];
    result[0] = INT_MAX;
    int* liquids;
    scanf("%d", &numLiquids);
    int i;
    l = 0; r = numLiquids - 1;
    liquids = (int*)malloc(numLiquids * sizeof(int));

    for (i = 0; i < numLiquids; i++) {
        scanf("%d", &liquids[i]);
    }
    while (l != r) {
        temp = liquids[r] + liquids[l];
        if (temp < 0) {
            temp *= -1;
        }

        if (result[0] - temp > 0) {
            result[0] = temp;
            result[1] = liquids[l];
            result[2] = liquids[r];
        }

        if (liquids[r] + liquids[l] < 0) {
            l++;
        }
        else {
            r--;
        }
    }

    printf("%d %d", result[1], result[2]);
    free(liquids);
    return 0;
}