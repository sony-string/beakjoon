#include <stdio.h>
#include <stdlib.h>

enum {
	up, down, left, right
};

int solve(const int **arr, int dir, int depth, int size) {
	int** myArr, * stack, directions[4] = { up, down, left, right };
	int i, k, merged = -1, top = 0, max = 0, temp;
	myArr = (int**)calloc(size, sizeof(int*));
	stack = (int*)calloc(size, sizeof(int));
	for (i = 0; i < size; i++) {
		myArr[i] = (int*)calloc(size, sizeof(int));
	}
	/*
	system("cls");
	for (i = 0; i < size; i++) {
		for (k = 0; k < size; k++) {
			printf("%d ", arr[i][k]);
		}
		printf("\n");
	}
	printf("\ndir = %d / depth = %d\n\n", dir, depth);
	*/
	if (dir == up) {
		for (i = 0; i < size; i++) {
			merged = -1;
			top = 0;
			for (k = 0; k < size; k++) {
				if (arr[k][i] == 0) {
					continue;
				}
				if (merged == top - 1) {
					stack[top] = arr[k][i];
					top++;
					continue;
				}
				else {
					if (stack[top - 1] == arr[k][i]) {
						stack[top - 1] *= 2;
						merged = top - 1;
						continue;
					}
					stack[top] = arr[k][i];
					top++;
					continue;
				}
			}
			for (k = 0; k < top; k++) {
				myArr[k][i] = stack[k];
				//printf("%d ", stack[k]);
			}
			for (; k < size; k++) {
				myArr[k][i] = 0;
			}
			//printf("\n");
		}
	}

	if (dir == down) {
		for (i = 0; i < size; i++) {
			merged = -1;
			top = 0;
			for (k = size - 1; k >= 0; k--) {
				if (arr[k][i] == 0) {
					continue;
				}
				if (merged == top - 1) {
					stack[top] = arr[k][i];
					top++;
					continue;
				}
				else {
					if (stack[top - 1] == arr[k][i]) {
						stack[top - 1] *= 2;
						merged = top - 1;
						continue;
					}
					stack[top] = arr[k][i];
					top++;
					continue;
				}
			}
			for (k = 0; k < top; k++) {
				myArr[size - 1 - k][i] = stack[k];
				//printf("%d ", stack[k]);
			}
			for (; k < size; k++) {
				myArr[size - 1 - k][i] = 0;
			}
			//printf("\n");
		}
	}

	if (dir == left) {
		for (i = 0; i < size; i++) {
			merged = -1;
			top = 0;
			for (k = 0; k < size; k++) {
				if (arr[i][k] == 0) {
					continue;
				}
				if (merged == top - 1) {
					stack[top] = arr[i][k];
					top++;
					continue;
				}
				else {
					if (stack[top - 1] == arr[i][k]) {
						stack[top - 1] *= 2;
						merged = top - 1;
						continue;
					}
					stack[top] = arr[i][k];
					top++;
					continue;
				}
			}
			for (k = 0; k < top; k++) {
				myArr[i][k] = stack[k];
				//printf("%d ", stack[k]);
			}
			for (; k < size; k++) {
				myArr[i][k] = 0;
			}
			//printf("\n");
		}
	}

	if (dir == right) {
		for (i = 0; i < size; i++) {
			merged = -1;
			top = 0;
			for (k = size - 1; k >= 0; k--) {
				if (arr[i][k] == 0) {
					continue;
				}
				if (merged == top - 1) {
					stack[top] = arr[i][k];
					top++;
					continue;
				}
				else {
					if (stack[top - 1] == arr[i][k]) {
						stack[top - 1] *= 2;
						merged = top - 1;
						continue;
					}
					stack[top] = arr[i][k];
					top++;
					continue;
				}
			}
			for (k = 0; k < top; k++) {
				myArr[i][size - 1 - k] = stack[k];
				//printf("%d ", stack[k]);
			}
			for (; k < size; k++) {
				myArr[i][size - 1 - k] = 0;
			}
			//printf("\n");
		}
	}

	max = 0;
	if (depth == 5) {
		for (i = 0; i < size; i++) {
			for (k = 0; k < size; k++) {
				if (myArr[i][k] > max) {
					max = myArr[i][k];
				}
			}
		}
		for (i = 0; i < size; i++) {
			free(myArr[i]);
		}
		free(myArr);
		return max;
	}
	
	for (i = 0; i < 4; i++) {
		temp = solve(myArr, directions[i], depth + 1, size);
		if (temp > max) {
			max = temp;
		}
	}
	for (i = 0; i < size; i++) {
		free(myArr[i]);
	}
	free(myArr);
	return max;
}

int main() {
	int** board;
	int size, i, k, max, temp, directions[4] = {up, down, left, right};
	scanf("%d", &size);
	board = (int**)calloc(size, sizeof(int*));
	for (i = 0; i < size; i++) {
		board[i] = (int*)calloc(size, sizeof(int));
		for (k = 0; k < size; k++) {
			scanf("%d", &board[i][k]);
		}
	}
	max = 0;
	for (i = 0; i < 4; i++) {
		temp = solve(board, directions[i], 1, size);
		if (temp > max) {
			max = temp;
		}
	}
	printf("%d", max);

	for (i = 0; i < size; i++) {
		free(board[i]);
	}
	free(board);
	return 0;
}