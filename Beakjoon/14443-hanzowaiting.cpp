#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int matched[301];
vi adj[301];
bool chk[301];
int N, M;

bool dfs(int v) {
	int match = -1;
	chk[v] = true;
	for (auto& i : adj[v]) {
		if (matched[i] != -1) {
			if (!chk[matched[i]] && dfs(matched[i])) {
				match = i;
				break;
			}
		}
		else {
			match = i;
			break;
		}
	}
	if (match == -1) return false;
	matched[match] = v;
	return true;
}

int main() {
	int K[2];
	scanf("%d %d %d %d", &N, &M, &K[0], &K[1]);
	int ans[2] = { 0, 0 };
	for (int t = 0; t < 2; t++) {
		memset(matched, -1, sizeof(matched));
		for (int i = 0; i <= 300; i++) {
			adj[i].clear();
		}
		for (int i = 0; i < K[t]; i++) {
			int s, e;
			scanf("%d %d", &s, &e);
			adj[s].push_back(e);
		}
		for (int i = 1; i <= N; i++) {
			memset(chk, false, sizeof(chk));
			if (dfs(i)) ans[t]++;
		}
	}
	if (ans[0] >= ans[1]) {
		printf("그만 알아보자");
	}
	else {
		printf("네 다음 힐딱이");
	}
	return 0;
}