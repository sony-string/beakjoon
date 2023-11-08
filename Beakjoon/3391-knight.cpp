#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int N, M;
int grid[200][200];
vii nopos;
vector<vi> adj;
int matched[40000];
bool chk[40000];

int dir[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };


bool isadj(ii& pos) {
	return (pos.x >= 0 && pos.y >= 0 && pos.x < N && pos.y < N && !binary_search(nopos.begin(), nopos.end(), pos));
}

void makegraph() {
	bool white = true;
	ii pos = { 0, 0 };
	for (int i = 0; i < N; i++) {
		white = i % 2 != 0;
		for (int j = 0; j < N; j++) {
			white = !white;
			if (!white) continue;
			pos = { i, j };
			if (binary_search(nopos.begin(), nopos.end(), pos)) continue;
			for (int k = 0; k < 8; k++) {
				ii dpos = { pos.x + dir[k][0], pos.y + dir[k][1] };
				if (isadj(dpos)) {
					adj[grid[i][j]].push_back(grid[dpos.x][dpos.y]);
				}
			}
		}
	}
}

void makeboard() {
	bool white = true;
	int bcnt = 0, wcnt = 0;
	for (int i = 0; i < N; i++) {
		white = i % 2 != 0;
		for (int j = 0; j < N; j++) {
			white = !white;
			if (white) {
				grid[i][j] = wcnt++;
			}
			else {
				grid[i][j] = bcnt++;
			}
		}
	}
	adj.assign(wcnt, {});
	makegraph();
}

bool dfs(int v) {
	chk[v] = true;
	int match = -1;
	for (auto& i : adj[v]) {
		if (matched[i] == -1) {
			match = i;
			break;
		}
		else if (!chk[matched[i]] && dfs(matched[i])) {
			match = i;
			break;
		}
	}
	if (match == -1) return false;
	matched[match] = v;
	return true;
}

int main() {
	scanf("%d %d", &N, &M);
	nopos.assign(M, {});
	for (auto& i : nopos) {
		scanf("%d %d", &i.x, &i.y);
		i.x--;
		i.y--;
	}
	sort(nopos.begin(), nopos.end());
	makeboard();
	int f = 0;
	fill(matched, matched + 40000, -1);
	for (int i = 0; i < adj.size(); i++) {
		fill(chk, chk + 40000, false);
		if (dfs(i)) f++;
	}
	printf("%d", N * N - nopos.size() - f);
	return 0;
}