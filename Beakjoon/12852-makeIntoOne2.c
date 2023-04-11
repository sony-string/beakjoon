#include <stdio.h>
#include <stdlib.h>

int main() {
	int** table = (int**)malloc(1000001 * sizeof(int*));
	int* queue = (int*)malloc(1000001 * sizeof(int));
	int front = 0, rear = 0;
	int num, count, pos;
	int i;
	scanf("%d", &num);
	for (i = 0; i < 1000001; i++) {
		table[i] = (int*)calloc(2, sizeof(int));
	}
	queue[rear] = num;
	rear++;
	while (front != rear) {
		pos = queue[front];
		if (pos == 1) {
			break;
		}
		front++;
		if (pos % 3 == 0 && table[pos / 3][0] == 0) {
			queue[rear] = pos / 3;
			table[pos / 3][0] = table[pos][0] + 1;
			table[pos / 3][1] = pos;
			rear++;
		}
		if (pos % 2 == 0 && table[pos / 2][0] == 0) {
			queue[rear] = pos / 2;
			table[pos / 2][0] = table[pos][0] + 1;
			table[pos / 2][1] = pos;
			rear++;
		}
		if (table[pos - 1][0] == 0) {
			queue[rear] = pos - 1;
			table[pos - 1][0] = table[pos][0] + 1;
			table[pos - 1][1] = pos;
			rear++;
		}
	}
	count = table[1][0];
	int* answers = (int*)malloc(count * sizeof(int));
	answers[0] = 1;
	for (i = 1; i < count; i++) {
		answers[i] = table[answers[i - 1]][1];
	}
	printf("%d\n%d ", count, num);
	for (i = count - 1; i >= 0; i--) {
		printf("%d ", answers[i]);
	}

	for (i = 0; i < 1000001; i++) {
		free(table[i]);
	}
	free(table);
	free(answers);
	free(queue);
	return 0;
}