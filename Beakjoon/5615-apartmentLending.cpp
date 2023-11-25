#include <bits/stdc++.h>
using namespace std;

typedef long long li;

li mul(li x, li y, li mod) { return (__int128)x * y % mod; }
li power(li x, li y, li mod) {
	li ret = 1;
	x %= mod;
	while (y) {
		if (y % 2) ret = mul(ret, x, mod);
		y >>= 1;
		x = mul(x, x, mod);
	}
	return ret;
}

//if n is prime, return true
bool miller(li n, li a) {
	if (a % n == 0) return false;
	li k = n - 1;
	while (1) {
		li temp = power(a, k, n);
		if (temp == n - 1) return true; //a^k = -1 (mod n)
		if (k % 2) return (temp == 1 || temp == n - 1);
		k /= 2;
	}
}

bool isprime(li x) {
	for (auto& i : { 2, 7, 61 }) {
		if (x == i) return 1;
		if (!miller(x, i)) return 0;
	}
	return 1;
}

int main() {
	int N;
	int ans = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		li n;
		scanf("%lld", &n);
		if (isprime(2 * n + 1)) ans++;
	}
	printf("%d", ans);
	return 0;
}
