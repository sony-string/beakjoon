#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int l = 0, r = 0;

int pop(int* queue) {
	int item = queue[l];
	l++;
	return item;
}

void push(int* queue, int item) {
	queue[r] = item;
	r++;
}

int isEmpty() {
	if (l == r)
		return 1;
	else
		return 0;
}

int main() {
	char cmd[10];
	const char PUSH[5] = "push";
	const char POP[4] = "pop";
	const char SIZE[5] = "size";
	const char EMPTY[6] = "empty";
	const char FRONT[6] = "front";
	const char BACK[5] = "back";
	int numCommand, item;
	int* queue = (int*)malloc(50000 * sizeof(int));
	scanf("%d", &numCommand);
	int i;
	for (i = 0; i < numCommand; i++) {
		scanf("%s", &cmd);
		if (strcmp(cmd, PUSH) == 0) {
			scanf("%d", &item);
			push(queue,item);
		}
		else if (strcmp(cmd, POP) == 0) {
			if (isEmpty() == 1) {
				printf("-1\n");
				continue;
			}
			else {
				item = pop(queue);
				printf("%d\n", item);
			}
		}
		else if (strcmp(cmd, SIZE) == 0) {
			printf("%d\n", r - l);
		}
		else if (strcmp(cmd, EMPTY) == 0) {
			printf("%d\n", isEmpty());
		}
		else if (strcmp(cmd, FRONT) == 0) {
			if (isEmpty() == 1) {
				printf("-1\n");
				continue;
			}
			else {
				printf("%d\n", queue[l]);
			}
		}
		else if (strcmp(cmd, BACK) == 0) {
			if (isEmpty() == 1) {
				printf("-1\n");
				continue;
			}
			else {
				printf("%d\n", queue[r-1]);
			}
		}
		else {
			printf("wrong input");
			break;
		}
	}
	free(queue);
	return 0;
}