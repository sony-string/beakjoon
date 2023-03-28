#include <stdio.h>

int isRightangle(int a, int b, int c) {
	int max = a;
	if (b >= a)
		max = b;
	if (c >= max)
		max = c;
	if (a * a + b * b + c * c == max * max * 2)
		return 1;
	else
		return 0;
}

int main() {
	int a, b, c;
	do {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 0)
			break;
		if (isRightangle(a, b, c) == 1)
			printf("right\n");
		else
			printf("wrong\n");
	} while (1);

	return 0;
}