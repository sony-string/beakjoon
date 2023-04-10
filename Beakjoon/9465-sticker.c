#include <stdio.h>
#include <stdlib.h>

int main() {
	int** stickers;
	int** scoreTable;
	int numTestCases, numLinesOfSticker, max;
	scanf("%d", &numTestCases);
	int i, k, T;

	for (T = 0; T < numTestCases; T++) {
		scanf("%d", &numLinesOfSticker);
		stickers = (int**)malloc(2 * sizeof(int*));
		scoreTable = (int**)malloc(2 * sizeof(int*));
		stickers[0] = (int*)malloc(numLinesOfSticker * sizeof(int));
		stickers[1] = (int*)malloc(numLinesOfSticker * sizeof(int));
		scoreTable[0] = (int*)calloc(numLinesOfSticker + 1, sizeof(int));
		scoreTable[1] = (int*)calloc(numLinesOfSticker + 1, sizeof(int));
		for (k = 0; k < 2; k++) {
			for (i = 0; i < numLinesOfSticker; i++) {
				scanf("%d", &stickers[k][i]);
			}
		}
		for (i = 0; i < numLinesOfSticker; i++) {
			for (k = 0; k < 2; k++) {
				if (scoreTable[k][i] + stickers[k][i] > scoreTable[(k + 1) % 2][i + 1]) {
					scoreTable[(k + 1) % 2][i + 1] = scoreTable[k][i] + stickers[k][i];
				}
				if (scoreTable[k][i] > scoreTable[k][i + 1]) {
					scoreTable[k][i + 1] = scoreTable[k][i];
				}
			}
		}
		max = scoreTable[0][numLinesOfSticker];
		if (scoreTable[1][numLinesOfSticker] > max) {
			max = scoreTable[1][numLinesOfSticker];
		}
		printf("%d", max);
		if (T + 1 != numTestCases) {
			printf("\n");
		}
		free(stickers[0]);
		free(stickers[1]);
		free(scoreTable[0]);
		free(scoreTable[1]);
		free(stickers);
		free(scoreTable);
	}

	return 0;
}