#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int grid[52][52];
int t[52][52];
int N, M;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int bfs(vii& init_pos) {
	fill((int*)t, (int*)t + sizeof(t) / sizeof(int), -1);
	queue<ii> q;
	for (auto& p : init_pos) {
		q.push(p);
		t[p.x][p.y] = 0;
	}
	while (!q.empty()) {
		ii p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = dir[i][0], dy = dir[i][1];
			if (grid[p.x + dx][p.y + dy] != 1 && t[p.x + dx][p.y + dy] == -1) {
				t[p.x + dx][p.y + dy] = t[p.x][p.y] + 1;
				q.emplace(p.x + dx, p.y + dy);
			}
		}
	}
	int ret = -1;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (grid[i][j] == 2) t[i][j] = 0;
			if (grid[i][j] == 1) continue;
			ret = max(ret, t[i][j]);
			if (t[i][j] == -1) {
				ret = -1;
				goto retline;
			}
		}
	}
retline:
	return ret;
}

int main() {
	scanf("%d %d", &N, &M);
	fill((int*)grid, (int*)grid + sizeof(grid) / sizeof(int), 1);
	vii viruses;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &grid[i][j]);
			if (grid[i][j] == 2) {
				viruses.emplace_back(i, j);
			}
		}
	}
	unsigned int sel = 0;
	unsigned int exitnum = pow(2, viruses.size());
	int ans = -1;
	while (++sel < exitnum) {
		if (popcount(sel) != M) continue;
		vii init_pos;
		auto seled = sel;
		int k = 0;
		while (seled) {
			if (seled % 2)
				init_pos.push_back(viruses[k]);			
			seled /= 2; k++;			
		}
		int res = bfs(init_pos);
		if (res == -1) continue;
		else if (ans == -1) ans = res;
		else ans = min(ans, res);
	}
	printf("%d", ans);
	return 0;
}