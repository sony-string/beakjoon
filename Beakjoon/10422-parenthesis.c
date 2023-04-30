#include <stdio.h>
#include <stdlib.h>

#define MAX 2500

int extendedEuclid(int* x, int* y, int a, int b) {
	int d;
	if (b == 0) {
		*x = 1; *y = 0; return a;
	}
	d = extendedEuclid(x, y, b, a % b);
	int x1 = *y;
	int y1 = *x - (int)(a / b) * (*y);
	*x = x1;
	*y = y1;
	return d;
}

int main() {
	long long* cat;
	int inverse;
	cat = (long long*)malloc((MAX + 1) * sizeof(long long));
	int cases, len, num, temp;
	const int M = 1000000007;
	scanf("%d", &cases);

	long long i;
	cat[0] = 1; cat[1] = 1;
	for (i = 2; i <= MAX; i++) {
		if (i == MAX) {
			printf("");
		}
		temp = extendedEuclid(&inverse, &temp, (i + 1), M);
		while (inverse < 0) {
			inverse += M;
		}
		inverse %= M;
		cat[i] = (((inverse * cat[i -1]) % M) * (4 * i - 2)) % M;
	}

	for (i = 0; i < cases; i++) {
		scanf("%d", &len);
		if (len % 2 == 1) {
			printf("0\n");
		}
		else {
			printf("%llu\n", cat[(len / 2)]);
		}
	}

	return 0;
}