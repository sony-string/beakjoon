#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned long long squaredArr[62];
	unsigned long long result = 1;
	int bits[62];
	unsigned long long a, b, c;
	scanf("%llu %llu %llu", &a, &b, &c);
	squaredArr[0] = 1;
	squaredArr[1] = a % c;
	int i;
	for (i = 2; i < 62; i++) {
		squaredArr[i] = squaredArr[i - 1] * squaredArr[i - 1];
		if (squaredArr[i] < squaredArr[i - 1]) {
			printf("overflow\n");
		}
		squaredArr[i] %= c;
	}
	for (i = 0; i < 62; i++) {
		bits[i] = 0;
	}
	for (i = 0; i < 62; i++) {
		bits[i] = b % 2;
		b /= 2;
		if (b == 0) {
			break;
		}
	}
	
	for (; i >= 0; i--) {
		printf("%d", bits[i]);
	}
	printf("\n");
	
	for (i = 0; i < 62; i++) {
		if (bits[i] == 1) {
			result *= squaredArr[i + 1];
			if (result < squaredArr[i]) {
				printf("overflow\n");
			}
			result %= c;
			//printf("%llu\n", result);
		}
	}
	printf("%llu", result);

	return 0;
}