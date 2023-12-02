#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct segnode {
	int s, e, v, k;
	bool ischange;
	segnode() : s(0), e(0), k(0), ischange(false) {
	}
	void set(int n) {
		v = n;
	}
};

vi arr;
struct segtree {
private:
	vector<segnode> tree;
	int size;
	void init(int s, int e, int v = 1) {
		auto& node = tree[v];
		node.s = s;
		node.e = e;
		if (s == e) {
			node.set(arr[s]);
		}
		else {
			init(s, (s + e) / 2, v * 2); init((s + e) / 2 + 1, e, v * 2 + 1);
			auto& l = tree[v * 2];
			auto& r = tree[v * 2 + 1];
			node.v = (l.v ^ r.v);
		}
	}
	void apply(int v) {
		auto& node = tree[v];
		if ((node.e - node.s + 1) % 2) {
			node.v ^= node.k;
		}
		if (node.s != node.e) {
			auto& l = tree[v * 2];
			auto& r = tree[v * 2 + 1];
			l.ischange = true;
			r.ischange = true;
			l.k ^= node.k;
			r.k ^= node.k;
		}
		node.ischange = false;
		node.k = 0;
	}
	void q(int& ret, int s, int e, int v = 1) {
		auto& node = tree[v];
		if (node.ischange) apply(v);
		int m = (node.s + node.e) / 2;
		if (node.s == s && node.e == e) {
			ret ^= node.v;
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
		init(0, N - 1);
	}
	int query(int s, int e) {
		int ret = 0;
		q(ret, s, e);
		return ret;
	}
	void update(int s, int e, int k, int v = 1) {
		auto& node = tree[v];
		int m = (node.s + node.e) / 2;
		if (node.ischange) apply(v);
		if (node.s == s && node.e == e) {
			node.k = k;
			node.ischange = true;
		}
		else {
			if ((e - s + 1) % 2 != 0)
				node.v ^= k;
			if (e <= m) {
				update(s, e, k, v * 2);
			}
			else if (s > m) {
				update(s, e, k, v * 2 + 1);
			}
			else {
				update(s, m, k, v * 2);
				update(m + 1, e, k, v * 2 + 1);
			}
		}
	}
};

int main() {
	int N, M;
	scanf("%d", &N);
	arr.assign(N, 0);
	for (auto& i : arr) {
		scanf("%d", &i);
	}
	segtree tree(N);
	scanf("%d", &M);
	for (int q = 0; q < M; q++) {
		int x, i, j, k;
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d %d %d", &i, &j, &k);
			tree.update(i, j, k);
		}
		else {
			scanf("%d %d", &i, &j);
			printf("%d\n", tree.query(i, j));
		}
	}
	return 0;
}