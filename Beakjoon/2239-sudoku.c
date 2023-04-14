#include <stdio.h>

typedef struct sudokuTable {
	char sudoku[9][10];
	int rowTable[9][10];
	int colTable[9][10];
	int blockTable[9][10];
	/*
		[row][col][0] = 테이블의 0 갯수
		나머지는[row][col][i] = rowTable[row][i] || colTable[9][i] || blockTable[(row / 3) * 3 + col / 3][i]
	*/
	int resultTable[9][9][10];
	int numLeft;
} Sudoku;


int determine(Sudoku*, int, int);

int update(Sudoku* state, int row, int col, int num) {
	int i, k;

	state->rowTable[row][num] = 1;
	state->colTable[col][num] = 1;
	state->blockTable[(row / 3) * 3 + col / 3][num] = 1;
	for (k = 0; k < 9; k++) {
		if (state->sudoku[row][k] != '0') {
			continue;
		}
		if (state->resultTable[row][k][num] == 0) {
			state->resultTable[row][k][num] = 1;
			state->resultTable[row][k][0]--;
		}
	}
	for (i = 0; i < 9; i++) {
		if (state->sudoku[i][col] != '0') {
			continue;
		}
		if (state->resultTable[i][col][num] == 0) {
			state->resultTable[i][col][num] = 1;
			state->resultTable[i][col][0]--;
		}
	}
	for (i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++) {
		for (k = 3 * (col / 3); k < 3 * (col / 3) + 3; k++) {
			if (state->sudoku[i][k] != '0') {
				continue;
			}
			if (state->resultTable[i][k][num] == 0) {
				state->resultTable[i][k][num] = 1;
				state->resultTable[i][k][0]--;
			}
		}
	}

	return 1;
}

// 칸 채우고 다른 칸 업데이트 함수 호출
int determine(Sudoku* state, int row, int col) {
	int r, num;
	for (r = 1; r < 10; r++) {
		if (state->resultTable[row][col][r] == 0) {
			state->sudoku[row][col] = '0' + r;
			num = r;
			break;
		}
	}
	if (r == 10) {
		return 0;
	}
	state->numLeft -= 1;
	return update(state, row, col, num);
}

int solve(Sudoku state, int row, int col) {
	int i, k, r;
	if (determine(&state, row, col) == 0) {
		return 0;
	}

	if (state.numLeft == 0) {
		for (i = 0; i < 9; i++) {
			printf("%s\n", state.sudoku[i]);
		}
		return 1;
	}
	i = row; k = col + 1;
	for (; i < 9; i++) {
		if (i == row) {
			k = col + 1;
		}
		else {
			k = 0;
		}
		for (; k < 9; k++) {
			if (state.sudoku[i][k] == '0') {
				break;
			}
		}
		if (k != 9) {
			break;
		}
	}
	if (i > 8 || k > 8) {
		return 1;
	}
	r = 1;
	while (1) {
		if (solve(state, i, k) == 1) {
			break;
		}
		while (state.resultTable[i][k][r] != 0) {
			r++;
			if (r == 10) {
				return 0;
			}
		}
		state.resultTable[i][k][r] = 1;
	}

	return 1;
}

int main() {
	Sudoku state;
	state.numLeft = 0;
	int i, k, r, num, row, col;
	for (i = 0; i < 9; i++) {
		for (k = 0; k < 10; k++) {
			state.rowTable[i][k] = 0;
			state.colTable[i][k] = 0;
			state.blockTable[i][k] = 0;
			for (r = 0; r < 9; r++) {
				state.resultTable[i][r][k] = 0;
			}
		}
	}
	for (i = 0; i < 9; i++) {
		scanf("%s", state.sudoku[i]);
		for (k = 0; k < 9; k++) {
			num = state.sudoku[i][k] - '0';
			state.rowTable[i][num] = 1;
			state.colTable[k][num] = 1;
			state.blockTable[(i / 3) * 3 + k / 3][num] = 1;
			if (state.sudoku[i][k] == '0') {
				state.numLeft++;
			}
		}
	}
	if (state.numLeft == 0) {
		for (i = 0; i < 9; i++) {
			printf("%s\n", state.sudoku[i]);
		}
		return 0;
	}
	for (i = 0; i < 9; i++) {
		for (k = 0; k < 9; k++) {
			if (state.sudoku[i][k] != '0') {
				continue;
			}
			for (r = 1; r < 10; r++) {
				state.resultTable[i][k][r] = state.rowTable[i][r] || state.colTable[k][r] || state.blockTable[(i / 3) * 3 + k / 3][r];
			}
		}
	}
	for (i = 0; i < 9; i++) {
		for (k = 0; k < 9; k++) {
			if (state.sudoku[i][k] == '0') {
				row = i; col = k;
				break;
			}
		}
		if (k != 9) {
			break;
		}
	}

	r = 1;
	while (1) {
		if (solve(state, row, col) == 1) {
			break;
		}
		while(state.resultTable[row][col][r] != 0) {
			r++;
			if (r == 10) {
				break;
			}
		}
		if (r == 10) {
			break;
		}
		state.resultTable[row][col][r] = 1;
	}

	return 0;
}