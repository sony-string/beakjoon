#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int dir[4][2] = { {0, 1}, {0,-1}, {1, 0}, {-1, 0} };

int main() {
	int N, M;
	char** grid;
	int** dist;
	int** chk;
	scanf("%d %d", &N, &M);
	grid = new char* [N + 2];
	chk = new int* [N + 2];
	for (int i = 1; i < N + 1; i++) {
		grid[i] = new char[M + 3];
		chk[i] = new int[M + 3];
		scanf("%s", grid[i] + 1);
		grid[i][0] = 'X';
		grid[i][M + 1] = 'X';
		grid[i][M + 2] = 0;
	}
	grid[0] = new char[M + 3];
	chk[0] = new int[M + 3];
	grid[N + 1] = new char[M + 3];
	chk[N + 1] = new int[M + 3];
	memset(grid[0], 'X', M + 3);
	memset(grid[N + 1], 'X', M + 3);

	vii poss;
	vii outdoors;
	poss.push_back({ 0, 0 });

	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < M + 1; j++) {
			if (grid[i][j] == 'P') {
				poss.emplace_back(i, j);
			}
			else if (grid[i][j] == 'H') {
				poss[0] = { i, j };
			}
			else if (grid[i][j] == '#') {
				outdoors.emplace_back(i, j);
			}
		}
	}
	dist = new int* [outdoors.size()];
	for (int i = 0; i < outdoors.size(); i++) {
		dist[i] = new int[poss.size()];
		memset(dist[i], 0, poss.size());
	}
	int pcnt = -1;
	for (auto& start : outdoors) {
		pcnt++;
		for (int i = 0; i < N + 2; i++) {
			memset(chk[i], -1, sizeof(int) * (M + 3));
		}

		queue<ii> q;
		chk[start.first][start.second] = 0;
		q.emplace(start);
		while (!q.empty()) {
			ii pos = q.front();
			q.pop();
			for (int d = 0; d < 4; d++) {
				int r = pos.x + dir[d][0], c = pos.y + dir[d][1];
				if (chk[r][c] != -1 || grid[r][c] == 'X') continue;
				chk[r][c] = chk[pos.x][pos.y] + 1;
				q.emplace(r, c);
			}
		}
		
		for (int i = 0; i < poss.size(); i++) {
			dist[pcnt][i] = chk[poss[i].x][poss[i].y];
		}
	}
	int ans = 0;
	for (int i = 0; i < outdoors.size(); i++) {
		int cnt = 0;
		if (dist[i][0] == -1) continue;
		for (int j = 1; j < poss.size(); j++) {
			if (dist[i][j] == -1) continue;
			if (dist[i][j] <= dist[i][0]) cnt++;
		}
		ans = max(ans, cnt);
	}
	printf("%d", ans);
	return 0;
}