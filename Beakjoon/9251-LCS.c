#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MIN
#define INT_MIN -2147483600
#endif

int main() {
	int** scores;
	int comparedScores[3];
	int len1, len2, max;
	char* str1, * str2;
	str1 = (char*)calloc(1001, sizeof(char));
	str2 = (char*)calloc(1001, sizeof(char));
	scanf("%s", str1);
	scanf("%s", str2);
	len1 = strlen(str1);
	len2 = strlen(str2);
	scores = (int**)malloc((len1 + 1) * sizeof(int*));

	int i, k;
	for (i = 0; i <= len1; i++) {
		scores[i] = (int*)calloc(len2 + 1, sizeof(int));
	}
	for (i = 1; i <= len1; i++) {
		for (k = 1; k <= len2; k++) {
			comparedScores[0] = scores[i][k - 1];
			comparedScores[1] = scores[i - 1][k];
			if (str1[i - 1] == str2[k - 1]) {
				comparedScores[2] = scores[i - 1][k - 1] + 1;
			}
			else {
				comparedScores[2] = INT_MIN;
			}
			max = comparedScores[0];
			if (comparedScores[1] > max) {
				max = comparedScores[1];
			}
			if (comparedScores[2] > max) {
				max = comparedScores[2];
			}
			scores[i][k] = max;
		}
	}

	printf("%d", scores[len1][len2]);

	free(str1);
	free(str2);
	for (i = 0; i <= len1; i++) {
		free(scores[i]);
	}
	return 0;
}