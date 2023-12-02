#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct segnode {
	int s, e, v;
	bool ischange;
	segnode() : s(0), e(0), ischange(false) {
	}
};

struct segtree {
private:
	vector<segnode> tree;
	int size;
	void init(int s, int e, int v = 1) {
		auto& node = tree[v];
		node.s = s;
		node.e = e;
		if (s == e) {
			node.v = 0;
		}
		else {
			init(s, (s + e) / 2, v * 2); init((s + e) / 2 + 1, e, v * 2 + 1);
			node.v = 0;
		}
	}
	void apply(int v) {
		auto& node = tree[v];
		node.v = (node.e - node.s + 1) - node.v;
		if (node.s != node.e) {
			auto& l = tree[v * 2];
			auto& r = tree[v * 2 + 1];
			l.ischange = !l.ischange;
			r.ischange = !r.ischange;
		}
		node.ischange = false;
	}
	void q(int& ret, int s, int e, int v = 1) {
		auto& node = tree[v];
		if (node.ischange) apply(v);
		int m = (node.s + node.e) / 2;
		if (node.s == s && node.e == e) {
			ret += node.v;
		}
		else if (m >= e) {
			q(ret, s, e, v * 2);
		}
		else if (m < s) {
			q(ret, s, e, v * 2 + 1);
		}
		else {
			q(ret, s, m, v * 2);
			q(ret, m + 1, e, v * 2 + 1);
		}
	}
public:
	segtree(int N) {
		size = pow(2, (int)log2(N) + 2) + 1;
		tree.assign(size, segnode());
		init(1, N);
	}
	int query(int s, int e) {
		int ret = 0;
		q(ret, s, e);
		return ret;
	}
	int update(int s, int e, int v = 1) {
		auto& node = tree[v];
		int m = (node.s + node.e) / 2;
		if (node.ischange) apply(v);
		if (node.s == s && node.e == e) {
			node.ischange = true;
			return node.v;
		}
		else {
			int n;
			if (e <= m) {
				n = update(s, e, v * 2);
			}
			else if (s > m) {
				n = update(s, e, v * 2 + 1);
			}
			else {
				n = update(s, m, v * 2);
				n += update(m + 1, e, v * 2 + 1);
			}
			int ret = n;
			node.v += (e - s + 1 - n) - n;
			return ret;
		}
	}
};

int main() {
	int N, M;
	scanf("%d", &N);
	segtree tree(N);
	scanf("%d", &M);
	for (int q = 0; q < M; q++) {
		int x, i, j;
		scanf("%d", &x);
		if (x == 0) {
			scanf("%d %d", &i, &j);
			tree.update(i, j);
		}
		else {
			scanf("%d %d", &i, &j);
			printf("%d\n", tree.query(i, j));
		}
	}
	return 0;
}