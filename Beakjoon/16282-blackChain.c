#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

int main() {
	ull len;
	ull bound[65];
	ull powOf2[65];
	bound[0] = 0;
	int result;
	ull bit = 1;

	for (int i = 0; i <= 64; i++) {
		powOf2[i] = bit;
		bit <<= 1;
	}
	
	for (int i = 1; i <= 64; i++) {
		bound[i] = 0;
		bound[i] += i;
		for (int k = 0; k <= i; k++) {
			bound[i] += (i + 1) * powOf2[k];
		}
	}
	
	scanf("%llu", &len);
	for (int i = 1; i <= 64; i++) {
		if (len <= bound[i]) {
			printf("%d", i);
			return 0;
		}
	}
}