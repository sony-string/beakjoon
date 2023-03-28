#include <stdio.h>

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	a = a / 100 + 10 * ((a / 10) % 10) + 100 * (a % 10);
	b = b / 100 + 10 * ((b / 10) % 10) + 100 * (b % 10);
	a > b ? printf("%d", a) : printf("%d", b);
	return 0;
}