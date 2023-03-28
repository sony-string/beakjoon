#include <stdio.h>
#include <stdlib.h>

int main() {
	int pushIndex = 0, count = 0, nextInt = 1;
	char* result;
	int* goal, *stack;
	int i, num;

	scanf("%d", &num);
	goal = (int*)malloc(num * sizeof(int));
	stack = (int*)malloc(num * sizeof(int));
	result = (char*)malloc(num * 2 + 10);

	for (i = 0; i < num; i++) {
		scanf("%d", &goal[i]);
	}
	stack[pushIndex] = nextInt; pushIndex++; nextInt++; result[count] = '+'; count++; //PUSH
	for (i = 0; i < num;) {
		if (goal[i] >= nextInt) {
			do {
				stack[pushIndex] = nextInt; pushIndex++; nextInt++; result[count] = '+'; count++; //PUSH
			} while (nextInt <= goal[i]);
			continue;
		}
		else {
			if (goal[i] == stack[pushIndex - 1]) {
				pushIndex--; result[count] = '-'; count++; //POP
				i++;
				continue;
			}
			else {
				printf("NO");
				break;
			}
		}
	}
	if (i == num) {
		for (i = 0; i < count; i++) {
			printf("%c\n", result[i]);
		}
	}
	free(result); free(goal); free(stack);
	return 0;
}