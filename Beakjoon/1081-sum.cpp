#include <bits/stdc++.h>
using namespace std;

typedef long long li;


li solve(li N) {
	if (N <= 0) return 0;
	li ret = 0;
	li l, r, n, d;
	d = 1;
	while (N / d != 0) {
		d *= 10;
	}
	d /= 10;
	for (; d >= 1; d /= 10) {
		n = (N / d) % 10;
		l = N / (d * 10);
		r = N % d;
		li sum = (n * (n - 1)) / 2;
		ret += n * (r + 1);
		ret += sum * d;		
		ret += l * 45 * d;
	}
	return ret;
}

int main() {
	int L, U;
	scanf("%d %d", &L, &U);
	li cntU, cntL;
	cntU = solve(U);
	cntL = solve(L - 1);
	printf("%lld", cntU - cntL);
	return 0;
}