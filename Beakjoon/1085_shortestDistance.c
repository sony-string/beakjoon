#include <stdio.h>

int main() {
	int min_height, min_width;
	int x, y, width, height;

	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &width);
	scanf("%d", &height);

	min_width = x > width - x ? width - x : x;
	min_height = y > height - y ? height - y : y;
	int result = min_width > min_height ? min_height : min_width;

	printf("%d", result);
	return 0;
}