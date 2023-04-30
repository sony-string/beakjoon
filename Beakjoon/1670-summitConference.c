#include <stdio.h>
#include <stdlib.h>

int main() {
	long long* table;
	int num, temp;
	const int M = 987654321;
	scanf("%d", &num);
	table = (long long*)malloc((num + 1) * sizeof(long long));
	temp = num / 2;
	table[0] = 1;
	table[1] = 1;
	int i, k;
	for (i = 2; i <= temp; i++) {
		table[i] = 0;
		for (k = 0; k < i; k++) {
			table[i] += table[k] * table[(i - 1) - k];
			table[i] %= M;
		}
	}
	printf("%llu", table[temp]);
	return 0;
}