#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<vi> grid;
vector<vi> sums;
int getsum(int x1, int y1, int x2, int y2) {
	int ret = 0;
	ret += sums[x2][y2];
	ret -= sums[x2][y1];
	ret -= sums[x1][y2];
	ret += sums[x1][y1];
	return ret;
}

struct Tree {
	int size;
	vector<vi> tree;	
	void init(int s) {
		size = s;
		tree.assign(s + 1, {});
		for (int r = 0; r <= s; r++) {
			tree[r].assign(s + 1, 0);
		}
		for (int xx = 1; xx <= s; xx++) {
			for (int yy = 1; yy <= s; yy++) {
				int x = xx - (xx & -xx);
				int y = yy - (yy & -yy);
				tree[xx][yy] = getsum(x, y, xx, yy);
			}
		}
	}
	int sum(int x, int y) {
		int ret = 0;
		while (x > 0) {
			int yy = y;
			while (yy > 0) {
				ret += tree[x][yy];
				yy -= (yy & -yy);
			}
			x -= (x & -x);
		}
		return ret;
	}
	int query(int x1, int y1, int x2, int y2) {
		int ret = 0;
		ret += sum(x2, y2);
		ret -= sum(x2, y1 - 1);
		ret -= sum(x1 - 1, y2);
		ret += sum(x1 - 1, y1 - 1);
		return ret;
	}
	void update(int x, int y, int d) {
		while (x <= size) {
			int yy = y;
			while (yy <= size) {
				tree[x][yy] += d;
				yy += (yy & -yy);
			}
			x += (x & -x);
		}
	}
};

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	grid.assign(N + 1, {});
	sums.assign(N + 1, {});
	for (int i = 0; i <= N; i++) {
		grid[i].assign(N + 1, 0);
		sums[i].assign(N + 1, 0);
	}
	for (int r = 1; r <= N; r++) {
		int sum = 0;
		for (int c = 1; c <= N; c++) {
			int n;
			scanf("%d", &n);
			sum += n;
			grid[r][c] = n;
			sums[r][c] = sums[r - 1][c] + sum;
		}
	}
	Tree tree;
	tree.init(N);
	for (int i = 0; i < M; i++) {
		int w;
		scanf("%d", &w);
		if (w == 0) {
			int x, y, c, d;
			scanf("%d %d %d", &x, &y, &c);
			d = c - grid[x][y];
			grid[x][y] = c;
			tree.update(x, y, d);
		}
		else {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("%d\n", tree.query(x1, y1, x2, y2));
		}
	}
	return 0;
}