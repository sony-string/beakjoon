#include <bits/stdc++.h>
using namespace std;

typedef long long li;

li comb(int n, int r) {
	li ret = 1;
	for (int i = 0; i < r; i++) {
		ret *= n--;
	}
	for (int i = 1; i <= r; i++) {
		ret /= i;
	}
	return ret;
}

li fact(int n) {
	li ret = 1;
	for (int i = n; i >= 1; i--) {
		ret *= i;
	}
	return ret;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, k;
		scanf("%d %d %d", &t, &n, &k);
		li ret = 0;
		for (int r = 1; r <= k; r++) {
			li sign = 1;
			for (int i = 0; i < r; i++) {
				ret += sign * fact(n - 1 - i) * comb(r - 1, i);
				sign = -sign;
			}
		}
		ret = fact(n) - ret;
		printf("%d %lld\n", t, ret);
	}
	return 0;
}