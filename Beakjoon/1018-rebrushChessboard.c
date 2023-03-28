#include <stdio.h>
#include <stdlib.h>

int countSquares(char**, int, int);

int main() {
	int best;
	int width, height;

	scanf("%d", &height);
	scanf("%d", &width);
	char** check = (char**)malloc(height * sizeof(char*));
	
	int i = 0, j = 0;
	for (i = 0; i < height; i++) {
		check[i] = (char*)malloc(width * sizeof(char));
		for (j = 0; j < width; j++) {
			do {
				scanf("%c", &check[i][j]);
			} 
			while (check[i][j] != 'B' && check[i][j] != 'W');
		}
	}

	best = 32;
	int temp;
	for (i = 0; i < height-7; i++) {
		for (j = 0; j < width-7; j++) {
			temp = countSquares(check, j, i);
			if (best > temp)
				best = temp;
		}
	}
	printf("%d", best);

	for (i = 0; i < height; i++) {
		free(check[i]);
	}
	free(check);
	return 0;
}

int countSquares(char** arr, int x, int y) {

	int i, j;
	int count = 0;
	char BW[2] = { 'B','W' };
	int colorFlag = 0;
	for (i = y; i < y + 8; i++) {
		for (j = x; j < x + 8; j++) {
			if (BW[colorFlag] != arr[i][j]) {
				count++;
			}
			if (colorFlag == 1)
				colorFlag = 0;
			else if (colorFlag == 0)
				colorFlag = 1;
		}
		if (colorFlag == 1)
			colorFlag = 0;
		else if (colorFlag == 0)
			colorFlag = 1;
	}
	if (count > 32)
		return (64 - count);
	else
		return count;
}