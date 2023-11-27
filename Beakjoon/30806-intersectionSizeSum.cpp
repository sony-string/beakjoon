#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

li x, y;
const li MOD = 998244353;
li uclid(li a, li b) {
	x = 1; y = -a / b;
	if (a % b == 0) {
		x = 0; y = 1; return b;
	}
	li d = uclid(b, a % b);
	li xx, yy;
	xx = y;
	yy = x + y * (-a / b);
	x = xx; y = yy;
	return d;
}


li invs[1000001];
void precom(int maxcnt) {
	invs[1] = 1;
	for (int i = 2; i <= maxcnt; i++) {
		uclid(MOD, i);
		while (y < 0) y += MOD;
		invs[i] = y;
	}
}

int main() {
	int N;
	li ans = 0;
	unordered_map<int, int> cnt;
	scanf("%d", &N);
	int k = 0;
	int maxcnt = 1;
	for (int i = 0; i < N; i++) {
		int M;
		scanf("%d", &M);
		for (int j = 0; j < M; j++) {
			int n;
			scanf("%d", &n);
			auto it = cnt.find(n);
			if (it == cnt.end()) {
				cnt.emplace(n, 1);
			}
			else {
				maxcnt = max(maxcnt, (*it).second += 1);
			}
		}
	}
	precom(maxcnt);
	vector<pair<const int, li>> arr;
	for (auto& it : cnt) {
		arr.emplace_back(it.second, 1);
	}
	for (k = 0;;) {
		ans = 0;
		for (auto& p : arr) {
			if (p.first <= k) {
				continue;
			}
			else {
				li temp = (p.second * (p.first - k)) % MOD;
				temp = (temp * invs[k + 1]) % MOD;
				p.second = temp;
				ans += temp;
			}
		}
		if (ans == 0) break;
		else {
			printf("%lld\n", ans % MOD);
		}
		k++;
	}
	for (; k < N; k++) {
		printf("0\n");
	}
	return 0;
}