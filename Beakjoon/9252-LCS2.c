#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MIN
#define INT_MIN -2147483647
#endif

int main()
{
    enum {
        dia, ver, hor
    };
    int*** scoreTable;
    char* str1, * str2;
    char result[1001];
    str1 = (char*)malloc(1001);
    str2 = (char*)malloc(1001);
    int len1, len2, score;
    scanf("%s %s", str1, str2);
    len1 = strlen(str1);
    len2 = strlen(str2);
    scoreTable = (int***)calloc(len1 + 1, sizeof(int**));
    int i, k;
    for (i = 0; i <= len1; i++) {
        scoreTable[i] = (int**)calloc(len2 + 1, sizeof(int*));
        for (k = 0; k <= len2; k++) {
            scoreTable[i][k] = (int*)calloc(2, sizeof(int));
        }
    }
    for (i = 1; i <= len1; i++) {
        for (k = 1; k <= len2; k++) {
            score = 0;
            if (str1[i - 1] == str2[k - 1]) {
                score = 1;
            }
            if (score == 0) {
                score = INT_MIN;
            }
            scoreTable[i][k][0] = score + scoreTable[i - 1][k - 1][0];
            scoreTable[i][k][1] = dia;
            if (scoreTable[i][k][0] < scoreTable[i - 1][k][0]) {
                scoreTable[i][k][0] = scoreTable[i - 1][k][0];
                scoreTable[i][k][1] = ver;
            }
            if (scoreTable[i][k][0] < scoreTable[i][k - 1][0]) {
                scoreTable[i][k][0] = scoreTable[i][k - 1][0];
                scoreTable[i][k][1] = hor;
            }
        }
    }
    /*
    for (i = 1; i <= len1; i++) {
        for (k = 1; k <= len2; k++) {
            if (scoreTable[i][k][1] == hor) {
                printf("hor ");
            }
            if (scoreTable[i][k][1] == ver) {
                printf("ver ");
            } 
            if (scoreTable[i][k][1] == dia) {
                printf("dia ");
            }
        }
        printf("\n");
    }
    for (i = 1; i <= len1; i++) {
        for (k = 1; k <= len2; k++) {
            printf("%d ", scoreTable[i][k][0]);
        }
        printf("\n");
    }
    */
    score = scoreTable[len1][len2][0];
    i = len1; k = len2;
    result[score] = 0;
    while (i >= 1 && k >= 1) {
        if (scoreTable[i][k][1] == dia) {
            result[scoreTable[i][k][0] - 1] = str1[i - 1];
            i--; k--;
            continue;
        }
        if (scoreTable[i][k][1] == hor) {
            k--;
            continue;
        }
        i--;
    }
    printf("%d\n", score);
    if (score > 0) {
        printf("%s", result);
    }
    free(str1);
    free(str2);
    return 0;
}