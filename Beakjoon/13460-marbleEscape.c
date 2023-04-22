#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	red = 0, blue = 1, up, right, left, down
};

void swap(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void freeBoard(char** board, int rows) {
	int i;
	for (i = 0; i < rows; i++) {
		free(board[i]);
	}
	free(board);
}

int tiltBoard(const char** board, const int posRow[2], const int posCol[2], int dir, int depth, int rows, int cols) {
	char** newBoard = (char**)calloc(rows, sizeof(char*));
	int flag = 0;
	int i, newPosRow[2], newPosCol[2], row, col, result, temp;
	for (i = 0; i < rows; i++) {
		newBoard[i] = (char*)calloc(cols + 1, sizeof(char));
		memcpy(newBoard[i], board[i], (cols + 1) * sizeof(char));
	}
	if (dir == up) {
		if (posRow[red] <= posRow[blue]) {
			row = posRow[red]; col = posCol[red];
			row--;
			while (newBoard[row][col] == '.') {
				row--;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row + 1][col]);
				newPosCol[red] = col;
				newPosRow[red] = row + 1;
			}
			else {
				newBoard[posRow[red]][posCol[red]] = '.';
				flag = 1;
			}

			row = posRow[blue]; col = posCol[blue];
			row--;
			while (newBoard[row][col] == '.') {
				row--;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return 0;
			}
			if (flag == 1) {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row + 1][col]);
			newPosCol[blue] = col;
			newPosRow[blue] = row + 1;
		}
		else {
			row = posRow[blue]; col = posCol[blue];
			row--;
			while (newBoard[row][col] == '.') {
				row--;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row + 1][col]);
				newPosCol[blue] = col;
				newPosRow[blue] = row + 1;
			}
			else {
				freeBoard(newBoard, rows);
				return 0;
			}

			row = posRow[red]; col = posCol[red];
			row--;
			while (newBoard[row][col] == '.') {
				row--;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row + 1][col]);
			newPosCol[red] = col;
			newPosRow[red] = row + 1;
		}
	}

	if (dir == down) {
		if (posRow[red] >= posRow[blue]) {
			row = posRow[red]; col = posCol[red];
			row++;
			while (newBoard[row][col] == '.') {
				row++;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row - 1][col]);
				newPosCol[red] = col;
				newPosRow[red] = row - 1;
			}
			else {
				newBoard[posRow[red]][posCol[red]] = '.';
				flag = 1;
			}

			row = posRow[blue]; col = posCol[blue];
			row++;
			while (newBoard[row][col] == '.') {
				row++;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return 0;
			}
			if (flag == 1) {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row - 1][col]);
			newPosCol[blue] = col;
			newPosRow[blue] = row - 1;
		}
		else {
			row = posRow[blue]; col = posCol[blue];
			row++;
			while (newBoard[row][col] == '.') {
				row++;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row - 1][col]);
				newPosCol[blue] = col;
				newPosRow[blue] = row - 1;
			}
			else {
				freeBoard(newBoard, rows);
				return 0;
			}

			row = posRow[red]; col = posCol[red];
			row++;
			while (newBoard[row][col] == '.') {
				row++;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row - 1][col]);
			newPosCol[red] = col;
			newPosRow[red] = row - 1;
		}
	}

	if (dir == left) {
		if (posCol[red] <= posCol[blue]) {
			row = posRow[red]; col = posCol[red];
			col--;
			while (newBoard[row][col] == '.') {
				col--;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row][col + 1]);
				newPosCol[red] = col + 1;
				newPosRow[red] = row;
			}
			else {
				newBoard[posRow[red]][posCol[red]] = '.';
				flag = 1;
			}

			row = posRow[blue]; col = posCol[blue];
			col--;
			while (newBoard[row][col] == '.') {
				col--;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return 0;
			}
			if (flag == 1) {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row][col + 1]);
			newPosCol[blue] = col + 1;
			newPosRow[blue] = row;
		}
		else {
			row = posRow[blue]; col = posCol[blue];
			col--;
			while (newBoard[row][col] == '.') {
				col--;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row][col + 1]);
				newPosCol[blue] = col + 1;
				newPosRow[blue] = row;
			}
			else {
				freeBoard(newBoard, rows);
				return 0;
			}

			row = posRow[red]; col = posCol[red];
			col--;
			while (newBoard[row][col] == '.') {
				col--;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row][col + 1]);
			newPosCol[red] = col + 1;
			newPosRow[red] = row;
		}
	}

	if (dir == right) {
		if (posCol[red] >= posCol[blue]) {
			row = posRow[red]; col = posCol[red];
			col++;
			while (newBoard[row][col] == '.') {
				col++;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row][col - 1]);
				newPosCol[red] = col - 1;
				newPosRow[red] = row;
			}
			else {
				newBoard[posRow[red]][posCol[red]] = '.';
				flag = 1;
			}

			row = posRow[blue]; col = posCol[blue];
			col++;
			while (newBoard[row][col] == '.') {
				col++;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return 0;
			}
			if (flag == 1) {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row][col - 1]);
			newPosCol[blue] = col - 1;
			newPosRow[blue] = row;
		}
		else {
			row = posRow[blue]; col = posCol[blue];
			col++;
			while (newBoard[row][col] == '.') {
				col++;
			}
			if (newBoard[row][col] == '#') {
				swap(&newBoard[posRow[blue]][posCol[blue]], &newBoard[row][col - 1]);
				newPosCol[blue] = col - 1;
				newPosRow[blue] = row;
			}
			else {
				freeBoard(newBoard, rows);
				return 0;
			}

			row = posRow[red]; col = posCol[red];
			col++;
			while (newBoard[row][col] == '.') {
				col++;
			}
			if (newBoard[row][col] == 'O') {
				freeBoard(newBoard, rows);
				return depth;
			}
			swap(&newBoard[posRow[red]][posCol[red]], &newBoard[row][col - 1]);
			newPosCol[red] = col - 1;
			newPosRow[red] = row;
		}
	}
	/*
	system("cls");
	for (i = 0; i < rows; i++) {
		printf("%s\n", newBoard[i]);
	}
	*/
	if (depth == 10) {
		freeBoard(newBoard, rows);
		return 0;
	}
	result = 0;
	int directions[4] = { up, down, left, right };
	for (i = 0; i < 4; i++) {
		if (directions[i] == up || directions[i] == down) {
			if (dir == up || dir == down) {
				continue;
			}
		}
		if (directions[i] == right || directions[i] == left) {
			if (dir == left || dir == right) {
				continue;
			}
		}
		temp = tiltBoard(newBoard, newPosRow, newPosCol, directions[i], depth + 1, rows, cols);
		if (temp == 0) {
			continue;
		}
		if (result == 0) {
			result = temp;
			continue;
		}
		if (temp < result) {
			result = temp;
		}
	}
	freeBoard(newBoard, rows);
	return result;
}

int main() {
	int rows, cols, temp, result = 999, count = 0;
	int posRow[2], posCol[2], directions[4] = { up, down, left, right };
	char** board;
	scanf("%d %d", &rows, &cols);
	int i, k;
	board = (char**)calloc(rows, sizeof(char*));
	for (i = 0; i < rows; i++) {
		board[i] = (char*)calloc(cols + 1, sizeof(char));
		scanf("%s", board[i]);
	}

	for (i = 0; i < rows; i++) {
		for (k = 0; k < cols; k++) {
			if (board[i][k] == 'R') {
				posRow[red] = i;
				posCol[red] = k;
				count++;
			}
			if (board[i][k] == 'B') {
				posRow[blue] = i;
				posCol[blue] = k;
				count++;
			}
		}
		if (count == 2) {
			break;
		}
	}
	for (i = 0; i < 4; i++) {
		temp = tiltBoard(board, posRow, posCol, directions[i], 1, rows, cols);
		if (temp == 0) {
			continue;
		}
		if (temp < result) {
			result = temp;
		}
	}
	if (result != 999) {
		printf("%d", result);
	}
	else {
		printf("-1");
	}

	freeBoard(board, rows);
	return 0;
}