#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int numStickers;
	int size[2];
	int longside, shortside;
	int big, small;
	int best = 0;
	int sum;
	int** stickers;

	scanf("%d %d %d", size, size + 1, &numStickers);
	if (size[0] < size[1]) {
		swap(size, size + 1);
	}
	stickers = (int**)malloc(numStickers * sizeof(int**));
	for (int i = 0; i < numStickers; i++) {
		stickers[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d %d", stickers[i], stickers[i] + 1);
		if (stickers[i][0] < stickers[i][1]) {
			swap(&stickers[i][0], &stickers[i][1]);
		}
	}

	for (int i = 0; i < numStickers - 1; i++) {
		for (int k = i + 1; k < numStickers; k++) {
			sum = stickers[i][0] * stickers[i][1] + stickers[k][0] * stickers[k][1];
			if (best > sum) {
				continue;
			}
			big = stickers[i][0] > stickers[k][0] ? i : k;
			small = big == i ? k : i;
			longside = stickers[big][0];
			shortside = stickers[i][1] + stickers[k][1];
			if ((size[0] >= longside && size[1] >= shortside) || (size[0] >= shortside && size[1] >= longside)) {
				best = sum;
				continue;
			}
			if (longside > size[0]) {
				continue;
			}
			
			longside = stickers[big][0] + stickers[small][0];
			shortside = stickers[small][1] > stickers[big][1] ? stickers[small][1] : stickers[big][1];
			if ((size[0] >= longside && size[1] >= shortside) || (size[0] >= shortside && size[1] >= longside)) {
				best = sum;
				continue;
			}
			longside = stickers[big][0] + stickers[small][1];
			shortside = stickers[small][0] > stickers[big][1] ? stickers[small][0] : stickers[big][1];
			if ((size[0] >= longside && size[1] >= shortside) || (size[0] >= shortside && size[1] >= longside)) {
				best = sum;
				continue;
			}
		}
	}
	printf("%d", best);
	return 0;
}