#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<pair<int, int>> vii;

int C, D, V;
vi chk;
vi paired;
vector<vector<int>> nodes;

bool match(int v) {
	for (auto i : nodes[v]) {
		if (chk[i]) continue;
		chk[i] = 1;
		assert(i < paired.size());
		if (paired[i] == -1 || match(paired[i])) return (paired[i] = v);
	}
	return false;
}

int solve() {
	int f = 0;
	paired.assign(D, -1);
	for (int i = 1; i <= C; i++) {
		chk.assign(D, 0);
		if (match(i)) f++;
	}
	return V - f;
}

int main() {
	int T = 0;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &C, &D, &V);
		char ch1, ch2;
		int idx1, idx2;
		vii cats, dogs;
		for (int i = 0; i < V; i++) {
			scanf(" %c%d %c%d", &ch1, &idx1, &ch2, &idx2);
			if (ch1 == 'C') {
				cats.emplace_back(idx1, idx2);
			}
			else {
				dogs.emplace_back(idx1, idx2);
			}
		}
		C = cats.size();
		D = dogs.size();
		nodes.assign(C + 1, {});
		int c = 0;
		for (const auto& p : cats) {
			c++;
			for (int i = 0; i < dogs.size(); i++) {
				if (dogs[i].first == p.second || dogs[i].second == p.first)
					nodes[c].push_back(i);
			}
		}

		printf("%d\n", solve());
	}
	return 0;
}