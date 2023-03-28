#include <stdio.h>

int main() {
	int count[10];
	int number, a, b, c;
	scanf("%d\n%d\n%d", &a, &b, &c);
	number = a * b * c;
	int i;
	for (i = 0; i < 10; i++) {
		count[i] = 0;
	}
	i = 1;
	int tmp;
	while (i <= number) {
		tmp = (number / i) % 10;
		count[tmp]++;
		i *= 10;
	}
	for (i = 0; i < 10; i++) {
		printf("%d\n", count[i]);
	}
}