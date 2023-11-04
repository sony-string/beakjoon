#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const li MOD = 1'000'000'007;
const li MAX = 2'000'000;

li xx, yy;
vector<li> facts;
vector<li> invs;
vi route;
vii bombs;
vector<vi> nextbombs;
li ans;
int N, M, K;

li extendedEuclid(li a, li b) {
	li d;
	if (b == 0) {
		xx = 1; yy = 0; return a;
	}
	d = extendedEuclid(b, a % b);
	li x1 = yy;
	li y1 = xx - (li)(a / b) * (yy);
	xx = x1;
	yy = y1;
	return d;
}

// 1~200만까지의 팩토리얼을 MOD 로 나눈 값을 미리 구함
// 마찬가지로 1~200만까지의 팩토리얼의 MOD 에 대한 역원을 구함 (invs 에 저장)
// 10!/(4! * 6!) mod p = (10! mod p) * (4!^1 mod p) * (6!^1 mod p) 로 구하기 위함
void precom() {
	facts.assign(MAX + 1, 1);
	invs.assign(MAX + 1, 1);
	for (li i = 2; i <= MAX; i++) {
		facts[i] = (facts[i - 1] * i) % MOD;
		extendedEuclid(MOD, i);
		while (yy < 0) yy += MOD;
		invs[i] = (invs[i - 1] * yy) % MOD;
	}
}


li dfs(int v, int depth = 1, li ret = 1) {
	route.push_back(v);
	ii src;
	ii& dest = bombs[route.back()];
	if (route.size() == 1) {
		src = { 0, 0 };
	}
	else {
		src = bombs[route[route.size() - 2]];
	}
	ii delta = { dest.x - src.x, dest.y - src.y };
	ret *= (((facts[delta.x + delta.y] * invs[delta.x]) % MOD) * invs[delta.y]) % MOD;
	ret %= MOD;
	delta = { N - dest.x, M - dest.y };
	li cnt = ret * ((((facts[delta.x + delta.y] * invs[delta.x]) % MOD) * invs[delta.y]) % MOD);
	cnt %= MOD;
	if (depth % 2) {
		ans -= cnt;
		if (ans < 0) ans += MOD;
	}
	else {
		ans += cnt;
		ans %= MOD;
	}
	for (auto& next : nextbombs[v]) {
		dfs(next, depth + 1, ret);
	}
	route.pop_back();
	return ret;
}


int main() {
	precom();
	scanf("%d %d %d", &N, &M, &K);
	bombs.assign(K, {});
	for (auto& i : bombs) {
		scanf("%d %d", &i.x, &i.y);
	}
	nextbombs.assign(K, {});
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			if (i == j) continue;
			if (bombs[i].x <= bombs[j].x && bombs[i].y <= bombs[j].y) nextbombs[i].push_back(j);
		}
	}
	ans = (((facts[N + M] * invs[N]) % MOD) * invs[M]) % MOD;
	li sign = -1;
	for (int i = 0; i < K; i++) {
		dfs(i);
	}
	printf("%lld", ans);
	return 0;
}