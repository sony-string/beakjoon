#include <stdio.h>
#include <stdlib.h>

int divide(const int** arr, int length, int x, int y, int* white, int* blue) {
	if (length != 1) {
		int flag[4];
		flag[0] = divide(arr, length/2, x, y, white, blue);
		flag[1] = divide(arr, length/2, x + length/2, y, white, blue);
		flag[2] = divide(arr, length/2, x, y + length/2, white, blue);
		flag[3] = divide(arr, length/2, x + length/2, y + length/2, white, blue);

		int i, mixed = 0, numWhite = 0, numBlue = 0;
		for (i = 0; i < 4; i++) {
			if (flag[i] == -1) {
				mixed++;
				continue;
			}
			if (flag[i] == 0) {
				numWhite++;
				continue;
			}
			numBlue++;
		}
		if (numBlue == 4) {
			return 1;
		}
		if (numWhite == 4) {
			return 0;
		}
		*blue += numBlue;
		*white += numWhite;
		return -1;
	}
	return arr[y][x];
}

int main() {
	int length, white = 0, blue = 0, temp;
	scanf("%d", &length);
	int** arr = (int**)malloc(length * sizeof(int*));
	int i, j;
	for (i = 0; i < length; i++) {
		arr[i] = (int*)malloc(length * sizeof(int));
		for (j = 0; j < length; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	temp = divide(arr, length, 0, 0, &white, &blue);
	if (temp == 0) {
		white++;
	}
	else if (temp == 1) {
		blue++;
	}
	printf("%d\n%d", white, blue);

	for (i = 0; i < length; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}