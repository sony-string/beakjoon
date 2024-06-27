#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef array<int, 2> ii;
typedef vector<ii> vii;
typedef long long li;


struct node {
	int min, max, val;
	int l, r;
};


class segtree {
private:
	int N;
	vector<node> tree;
	void init(int l, int r, int v, vi& arr) {
		node& n = tree[v];
		n.l = l; n.r = r;

		if (l == r) {
			n.min = n.max = arr[l];
			n.val = 0;
		}
		else {
			int m = (l + r) / 2;
			init(l, m, v * 2, arr);
			init(m + 1, r, v * 2 + 1, arr);
			node& ln = tree[v * 2];
			node& rn = tree[v * 2 + 1];

			n.max = max(ln.max, rn.max);
			n.min = min(ln.min, rn.min);
			n.val = max(max(ln.val, rn.val), rn.max - ln.min);
		}
	}

	node _query(int l, int r, int v = 1) {
		node& n = tree[v];
		if (n.l == l && n.r == r) {
			return n;
		}
		else {
			int m = (n.l + n.r) / 2;
			if (r <= m) {
				return _query(l, r, v * 2);
			}
			else if (l > m) {
				return _query(l, r, v * 2 + 1);
			}
			else {
				node ret;
				node&& ln = _query(l, m, v * 2);
				node&& rn = _query(m + 1, r, v * 2 + 1);

				ret.max = max(ln.max, rn.max);
				ret.min = min(ln.min, rn.min);
				ret.val = max(max(ln.val, rn.val), rn.max - ln.min);
				return ret;
			}
		}
	}

	void _update(int k, int x, int v = 1) {
		node& n = tree[v];

		if (n.l == n.r) {
			n.min = n.max = x;
			n.val = 0;
		}
		else {
			int m = (n.l + n.r) / 2;

			if (k <= m) _update(k, x, v * 2);
			else _update(k, x, v * 2 + 1);

			node& ln = tree[v * 2];
			node& rn = tree[v * 2 + 1];

			n.max = max(ln.max, rn.max);
			n.min = min(ln.min, rn.min);
			n.val = max(max(ln.val, rn.val), rn.max - ln.min);
		}
	}
public:
	segtree(vi& arr) {
		N = arr.size();
		int size = (int)pow(2, (int)(log2(N) + 2));
		tree.assign(size, {});
		init(0, N - 1, 1, arr);
	}

	int query(int l, int r) {
		return _query(l, r).val;
	}

	void update(int k, int x) {
		_update(k, x);
	}
};


void Main() {
	int N, Q;
	vi arr;
	scanf("%d", &N);
	arr.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	segtree tree(arr);
	scanf("%d", &Q);

	for (int q = 0; q < Q; q++) {
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
		if (op == 1) {
			tree.update(l - 1, r);
		}
		else {
			printf("%d\n", tree.query(l - 1, r - 1));
		}
	}
}


int main() {
#ifndef BOJ
	freopen("input.txt", "r", stdin);
#endif
	Main();
	return 0;
}