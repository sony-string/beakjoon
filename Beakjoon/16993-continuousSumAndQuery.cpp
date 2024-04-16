#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct Node {
	int l, r;
	int lsum, rsum, wsum, sum;
	bool islsnull, isrsnull;
	Node() : l(0), r(0), lsum(0), rsum(0), wsum(0), sum(0), islsnull(false), isrsnull(false) {}
};

vector<Node> segtree;
vi arr;

void makeSegtree(int v, int l, int r) {
	Node& node = segtree[v];
	node.l = l; node.r = r;
	if (l == r) {
		node.lsum = max(0, arr[l]);
		node.rsum = node.lsum;
		if (arr[l] < 0) {
			node.islsnull = node.isrsnull = true;
		}
		node.sum = arr[l];
		node.wsum = node.sum;
		return;
	}
	Node& ln = segtree[v * 2], &rn = segtree[v * 2 + 1];
	makeSegtree(v * 2, l, (l + r) / 2);
	makeSegtree(v * 2 + 1, (l + r) / 2 + 1, r);
	node.sum = ln.sum + rn.sum;
	node.lsum = max(ln.lsum, ln.sum + rn.lsum);
	if (ln.islsnull && ln.lsum > ln.sum + rn.lsum) node.islsnull = true;
	node.rsum = max(rn.rsum, rn.sum + ln.rsum);
	if (rn.isrsnull && rn.rsum > rn.sum + ln.rsum) node.isrsnull = true;
	node.wsum = max({ ln.wsum, rn.wsum, ln.rsum + rn.lsum });
	if ((ln.isrsnull && rn.islsnull) && (ln.wsum < 0 && rn.wsum < 0)) node.wsum = max(ln.wsum, rn.wsum);
}

void initSegtree() {
	int _size = pow(2, log2(arr.size()) + 2);
	segtree.assign(_size + 1, Node());
	makeSegtree(1, 0, arr.size() - 1);
}

Node query(int v, int l, int r) {
	const Node& node = segtree[v];
	if (node.l == l && node.r == r) return node;
	Node ret;
	int m = (node.l + node.r) / 2;
	if (m < l) return query(v * 2 + 1, l, r);
	else if (m >= r) return query(v * 2, l, r);
	Node ln = query(v * 2, l, m), rn = query(v * 2 + 1, m + 1, r);
	ret.sum = ln.sum + rn.sum;
	ret.lsum = max(ln.lsum, ln.sum + rn.lsum);
	if (ln.islsnull && ln.lsum > ln.sum + rn.lsum) ret.islsnull = true;
	ret.rsum = max(rn.rsum, rn.sum + ln.rsum);
	if (rn.isrsnull && rn.rsum > rn.sum + ln.rsum) ret.isrsnull = true;
	ret.wsum = max({ ln.wsum, rn.wsum, ln.rsum + rn.lsum });
	if ((ln.isrsnull && rn.islsnull) && (ln.wsum < 0 && rn.wsum < 0)) ret.wsum = max(ln.wsum, rn.wsum);
	return ret;
}

int main() {
	int N, M;
	scanf("%d", &N);
	arr.assign(N, 0);
	for (auto& i : arr) {
		scanf("%d", &i);
	}
	initSegtree();
	scanf("%d", &M);
	for (int q = 0; q < M; q++) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--; r--;
		printf("%d\n", query(1, l, r).wsum);
	}
	return 0;
}