#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
using namespace std;

typedef long long li;

void solve(li* result, li n) {
	if (result[n - 2] == -1 && n - 2 > 0) {
		solve(result, n - 2);
	}
	if (result[n - 1] == -1 && n - 1 > 0) {
		solve(result, n - 1);
	}

	result[n] = (n - 1) * (result[n - 1] + result[n - 2]);
	result[n] %= 1000000007;
}

int main() {
	int N;
	int remainder, pool;
	li coef;

	scanf("%d", &N);
	remainder = N % 4;
	pool = N - remainder;

	li* completePermutations = new li[pool + 1];
	memset(completePermutations, -1, sizeof(li) * (pool + 1));
	completePermutations[1] = 0;
	completePermutations[2] = 1;
	solve(completePermutations, pool);

	coef = 1;
	for (int i = N; i > N - remainder; i--) {
		coef *= i;
	}
	for (int i = remainder; i > 0; i--) {
		coef /= i;
	}

	printf("%lld", (completePermutations[pool] * coef) % 1000000007);

	return 0;
}