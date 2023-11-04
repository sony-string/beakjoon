#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

typedef pair<int, int> ii;
typedef vector<int> vi;

char grid[51][51];
int N;
int off;
int vidx = 0;
int chk[50][50];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

bool isvalid(ii& pos) {
	return pos.x >= 0 && pos.y >= 0 && pos.x < N && pos.y < N;
}

struct Network {
	int S, T;
	int size;
	vector<vi> caps;
	vector<vi> flows;
	vector<list<int>> net;
	vector<int> route;
	vector<bool> visited;
	
	void addedge(int s, int e, int c) {
		net[s].push_back(e);
		net[e].push_back(s);
		caps[s][e] = c;
		caps[e][s] = 0;
	}

	void makenet(ii start) {
		off = N * N;
		S = 0;
		T = off * 2;
		size = off * 2 + 1;
		caps.assign(size, {});
		flows.assign(size, {});
		for (int i = 0; i < size; i++) {
			caps[i].assign(size, 0);
			flows[i].assign(size, 0);
		}

		net.assign(off * 2 + 1, {});
		memset(chk, -1, sizeof(int[50][50]));
		queue<ii> q;
		q.emplace(start);
		addedge(0, off, 1e5);
		chk[start.x][start.y] = vidx++;
		while (!q.empty()) {
			ii pos = q.front();
			ii dpos;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int r = dir[i][0], c = dir[i][1];
				dpos = { pos.x + r * 3, pos.y + c * 3 };
				if (!isvalid(dpos) || grid[dpos.x][dpos.y] == 'H') continue;				
				if (grid[pos.x + r][pos.y + c] == 'H' && grid[pos.x + r * 2][pos.y + c * 2] == 'H') continue;

				if (chk[dpos.x][dpos.y] == -1) {
					addedge(vidx, vidx + off, 1);
					if (grid[dpos.x][dpos.y] == 'b') {
						addedge(vidx, T, 1e4);
					}
					chk[dpos.x][dpos.y] = vidx++;
					q.emplace(dpos);
				}
				else if (caps[chk[pos.x][pos.y] + off][chk[dpos.x][dpos.y]] != 0) {
					continue;
				}
				int cap;
				if (grid[pos.x + r][pos.y + c] == 'b' || grid[pos.x + r * 2][pos.y + c * 2] == 'b') {
					cap = 1e4;
				}
				else if (grid[pos.x + r][pos.y + c] == 'H' || grid[pos.x + r * 2][pos.y + c * 2] == 'H') {
					cap = 1;
				}
				else {
					cap = 2;
				}
				addedge(chk[pos.x][pos.y] + off, chk[dpos.x][dpos.y], cap);
				addedge(chk[dpos.x][dpos.y] + off, chk[pos.x][pos.y], cap);
			}
		}
	}

	bool bfs() {
		route.assign(size, -1);
		visited.assign(size, false);
		queue<int> q;
		q.emplace(S);
		visited[S] = true;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto& i : net[v]) {
				if (caps[v][i] - flows[v][i] > 0 && !visited[i]) {
					route[i] = v;
					visited[i] = true;
					q.emplace(i);
					if (i == T) goto found;
				}
			}
		}
		return false;
	found:
		return true;
	}

	int augment(int v, int mflow = 1e9) {
		if (v == S) return mflow;
		int from = route[v];
		mflow = min(mflow, caps[from][v] - flows[from][v]);
		mflow = augment(from, mflow);
		flows[from][v] += mflow;
		flows[v][from] -= mflow;
		return mflow;
	}

	int doflow() {
		int totalflow = 0;
		while (bfs()) {
			totalflow += augment(T);
		}
		return totalflow;
	}
} net;


int main() {
	ii start = { -1, -1 };
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", grid[i]);
		if (start.x != -1) continue;
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == '$') {
				start = { i, j };
			}
		}
	}
	net.makenet(start);
	int ans = net.doflow();
	if (ans > 2500) {
		printf("-1");
	}
	else {
		printf("%d", ans);
	}
	return 0;
}