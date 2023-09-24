#include <bits/stdc++.h>
using namespace std;

int N, M;
char** maps;
vector<vector<int>> d1, d2;

int dir[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

void bfs(int X, int Y, vector<vector<int>>& sd) {
	queue<pair<int, int>> q;
	sd.assign(N + 2, {});
	int x, y;
	for (int i = 0; i <= N + 1; i++) {
		sd[i].assign(M + 2, -1);
	}
	q.emplace(X, Y);
	sd[X][Y] = 0;

	while (!q.empty()) {
		x = q.front().first; y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			if (maps[x + dir[i][0]][y + dir[i][1]] == '1')
				continue;
			if (sd[x + dir[i][0]][y + dir[i][1]] == -1) {
				q.emplace(x + dir[i][0], y + dir[i][1]);
				sd[x + dir[i][0]][y + dir[i][1]] = sd[x][y] + 1;
			}
		}
	}
}

int solve() {
	bfs(1, 1, d1);
	bfs(N, M, d2);
	int ans = 2 * 1e9;
	int dist = 2 * 1e9;
	for (int x = 1; x <= N; x++) {
		dist = 2 * 1e9;
		for (int y = 1; y <= M; y++) {
			if (d1[x][y] != -1)
				dist = min(d1[x][y], dist);
			if (d2[x][y] != -1)
				ans = min(ans, dist + d2[x][y]);
			if (d2[x + 1][y] != -1)
				ans = min(ans, dist + d2[x + 1][y] + 1);
			dist++;
		}
		dist = 2 * 1e9;
		for (int y = M; y > 0; y--) {
			if (d1[x][y] != -1)
				dist = min(d1[x][y], dist);
			if (d2[x][y] != -1)
				ans = min(ans, dist + d2[x][y]);
			if (d2[x + 1][y] != -1)
				ans = min(ans, dist + d2[x + 1][y] + 1);
			dist++;
		}
	}

	for (int y = 1; y <= M; y++) {
		dist = 2 * 1e9;
		for (int x = 1; x <= N; x++) {
			if (d1[x][y] != -1)
				dist = min(d1[x][y], dist);
			if (d2[x][y] != -1)
				ans = min(ans, dist + d2[x][y]);
			if (d2[x][y + 1] != -1)
				ans = min(ans, dist + d2[x][y + 1] + 1);
			dist++;
		}
		dist = 2 * 1e9;
		for (int x = N; x > 0; x--) {
			if (d1[x][y] != -1)
				dist = min(d1[x][y], dist);
			if (d2[x][y] != -1)
				ans = min(ans, dist + d2[x][y]);
			if (d2[x][y + 1] != -1)
				ans = min(ans, dist + d2[x][y + 1] + 1);
			dist++;
		}
	}
	if (ans >= 1000 * 1000) {
		return -1;
	}
	return ans;
}

int main() {
	scanf("%d %d", &N, &M);
	maps = new char* [N + 2];
	for (int i = 0; i <= N + 1; i++) {
		maps[i] = new char[M + 3];
		if (i > 0 && i <= N) {
			scanf("%s", maps[i] + 1);
			maps[i][0] = '1';
			maps[i][M + 1] = '1';
		}
		else
			memset(maps[i], '1', M + 2);
	}
	printf("%d\n", solve());
	return 0;
}