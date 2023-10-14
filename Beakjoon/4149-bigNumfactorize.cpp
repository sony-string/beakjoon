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
		for (auto& i : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
			if (x == i) return 1;
			if (x > 40 && !miller(x, i)) return 0;
		}
		if (x <= 40) return 0;
		return 1;
	}
	
	li f(li x, li n, li c) {
		return (c + mul(x, x, n)) % n;
	}
	void rec(li n, vector<li>& v) {
		if (n == 1) return;
		if (n % 2 == 0) {
			v.push_back(2);
			rec(n / 2, v);
			return;
		}
		if (isprime(n)) {
			v.push_back(n);
			return;
		}
		li a, b, c;
		while (1) {
			a = rand() % (n - 2) + 2;
			b = a;
			c = rand() % 20 + 1;
			do {
				a = f(a, n, c);
				b = f(f(b, n, c), n, c);
			} while (gcd(abs(a - b), n) == 1);
			if (a != b) break;
		}
		li x = gcd(abs(a - b), n);
		rec(x, v);
		rec(n / x, v);
	}
	vector<li> factorize(li n) {
		vector<li> ret;
		rec(n, ret);
		sort(ret.begin(), ret.end());
		return ret;
	}

int main() {
	li N;
	scanf("%lld", &N);
	vector<li> f = factorize(N);
	for (auto i : f) {
		printf("%lld\n", i);
	}
	return 0;
}