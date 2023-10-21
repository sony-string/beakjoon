#include <bits/stdc++.h>
using namespace std;


long long comb(int n, int r) {
	long long ret = 1;
	vector<int> v(r);
	vector<int> d(r);
	for (int i = n; i > n - r; i--) {
		v[n - i] = i;
	}
	for (int i = 1; i <= r; i++) {
		d[i - 1] = i;
	}
	for (auto& i : v) {
		for (auto& j : d) {
			if (j == 1) continue;
			int div = gcd(i, j);
			i /= div; j /= div;
		}
	}
	for (auto& i : v) {
		ret *= i;		
	}
	return ret;
}

int main() {
	int T;
	char* str = new char[81];
	int num[80];
	int len;
	int low;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%s", str);
		bool istrue = true;
		long long ans = 0;
		len = strlen(str);
		for (int i = 0; i < len; i++) {
			num[i] = str[i] - '0';
		}
		low = 0;
		for (int i = 0; i < len; i++) {
			if (low > num[i]) {
				istrue = false; break;
			}
			for (int j = low; j < num[i]; j++) {
				ans += comb(10 - j + len - i - 2, 10 - j - 1);
			}
			low = num[i];
		}
		if (istrue) printf("%lld\n", ans);
		else printf("-1\n");
	}
	return 0;
}