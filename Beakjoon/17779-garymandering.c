#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//d1 이 우하향, d2가 우상향

void counting(int count[5], int** map, int pos[], int d1, int d2, int size) {
	memset(count, 0, sizeof(int[5]));
	int r, c, i;
	int bound[2];
	int secBound;
	int flag;
	int rightArea = 2;
	bound[0] = pos[0];
	bound[1] = pos[1] + d2;
	for (r = 0; r < pos[0] - d2; r++) {
		for (c = 0; c <= bound[1]; c++) {
			count[1] += map[r][c];
		}
		for (; c < size; c ++) {
			count[2] += map[r][c];
		}
	}
	i = 0;
	secBound = bound[1];
	flag = 0;
	for (; r < bound[0]; r++) {
		for (c = 0; c < bound[1] - i; c++) {
			count[1] += map[r][c];
		}
		for (; c <= secBound; c++) {
			count[0] += map[r][c];
		}
		if (flag == 0 && secBound < pos[1] + d1 + d2) {
			secBound++;
		}
		else {
			flag = 1;
			if (secBound != pos[1] + d1 + d2) {
				rightArea = 4;
			}
			secBound--;
		}
		for (; c < size; c++) {
			count[rightArea] += map[r][c];
		}
		i++;
	}
	bound[0] = pos[0] + d1;
	bound[1] = pos[1] + d1;
	for (r = size - 1; r > bound[0]; r--) {
		for (c = 0; c < bound[1]; c++) {
			count[3] += map[r][c];
		}
		for (; c < size; c++) {
			count[4] += map[r][c];
		}
	}
	i = 0;
	secBound = bound[1];
	rightArea = 4;
	flag = 0;
	for (; r >= pos[0]; r--) {
		for (c = 0; c < bound[1] - i; c++) {
			count[3] += map[r][c];
		}
		for (; c <= secBound; c++) {
			count[0] += map[r][c];
		}
		if (flag == 0 && secBound < pos[1] + d1 + d2) {
			secBound++;
		}
		else {
			flag = 1;
			if (secBound == pos[1] + d1 + d2) {
				rightArea = 2;
			}
			secBound--;
		}
		for (; c < size; c++) {
			count[rightArea] += map[r][c];
		}
		i++;
	}
}

int main() {
	int** map, count[5], size;
	int best, max, min;
	int d1, d2;
	int pos[2];

	scanf("%d", &size);

	map = (int**)malloc(size * sizeof(int*));
	for (int r = 0; r < size; r++) {
		map[r] = (int*)malloc(size * sizeof(int));
		for (int c = 0; c < size; c++) {
			scanf("%d", map[r] + c);
		}
	}
	best = 100000;
	for (int r = 1; r < size - 1; r ++) {
		for (int c = 0; c < size - 1; c++) {
			pos[0] = r;
			pos[1] = c;
			for (d2 = 1; r - d2 >= 0; d2++) {
				for (d1 = 1; (c + d1 + d2 < size) && r + d1 < size; d1++) {
					counting(count, map, pos, d1, d2, size);
					min = count[0]; max = count[0];
					for (int i = 1; i < 5; i++) {
						if (count[i] < min) {
							min = count[i];
						}
						else if (count[i] > max){
							max = count[i];
						}
					}
					if (best > max - min) {
						best = max - min;
					}
				}
			}
		}
	}

	printf("%d", best);
	return 0;
}