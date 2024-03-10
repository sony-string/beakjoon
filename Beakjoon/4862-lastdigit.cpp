#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<li> vi;

void print(int ans, int n) {
	int p = 1;
	for (int i = 0; i < n - 1; i++)
		p *= 10;
	for (int i = 0; i < n; i++) {
		printf("%d", (ans / p) % 10);
		p /= 10;
	}
	printf("\n");
}

const int E = 31;
const int MOD = 10'000'000;
void getpows(vi& pows, int b) {
	pows.assign(E, b);
	for (int i = 1; i < E; i++) {
		pows[i] = pows[i - 1] * pows[i - 1] % MOD;
	}
}

int main() {
	int b, e, n;
	vi pows;	
	li ans = 1;
	scanf("%d", &b);
	while (b != 0) {

		scanf("%d %d", &e, &n);
		ans = 1;
		getpows(pows, b);
		for (int k = 0; k < e; k++) {
			ans %= 4'000'000;
			li temp = 1;
			int i = 0;
			while (ans != 0) {
				if (ans % 2) {
					temp *= pows[i];
					temp %= MOD;
				}
				i++;
				ans >>= 1;
			}
			ans = temp;
			if (ans == 0) break;
		}
		print(ans, n);
		scanf("%d", &b);
	}
	return 0;
}