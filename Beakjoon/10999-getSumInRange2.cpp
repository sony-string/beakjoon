#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

typedef long long li;
typedef pair<int, int> Query;
typedef vector<li> vi;


typedef struct SegTreeNode {
	int lbound, rbound;
	li sum;
	li lazy;

	SegTreeNode() {
		lbound = 0;
		rbound = 0;
		sum = 0;
		lazy = 0;
	}
} Node;

typedef struct SegTree {
	int size;
	int nodeCount;
	Node* tree;

	void initSegTree(const vi& arr) {
		size = arr.size();
		int logsize = (int)log2(size) + 1;
		nodeCount = (int)pow(2, logsize) * 2 + 1;
		tree = new Node[nodeCount];
		makeSegTree(arr, 1, 0, size - 1);
	}

	void makeSegTree(const vi& arr, int index, int lbound, int rbound) {
		int m = lbound + rbound;
		m /= 2;
		int lindex = index * 2;
		int rindex = lindex + 1;

		tree[index].lbound = lbound;
		tree[index].rbound = rbound;

		if (lbound != rbound) {
			makeSegTree(arr, lindex, lbound, m);
			makeSegTree(arr, rindex, m + 1, rbound);
			tree[index].sum = tree[lindex].sum + tree[rindex].sum;
			return;
		}

		tree[index].sum = arr[lbound];
	}

	void updateSegTree(const Query& q, li v) {
		query(1, q.first, q.second, v);
	}

	void applyLazy(int index) {
		tree[index].sum += tree[index].lazy * ((li)tree[index].rbound - tree[index].lbound + 1);
		if (tree[index].lbound != tree[index].rbound) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy;
		}
		tree[index].lazy = 0;
	}

	li query(int index, int lbound, int rbound, li v = 0) {
		int lindex = index * 2;
		int rindex = lindex + 1;
		int m = tree[index].lbound + tree[index].rbound;
		m /= 2;

		if (v != 0) {
			if (lbound == tree[index].lbound && rbound == tree[index].rbound) {
				tree[index].lazy += v;
				applyLazy(index);
			}
			else {
				if (tree[index].lazy > 0) {
					applyLazy(index);
				}
				tree[index].sum += v * ((li)rbound - lbound + 1);
			}
		}
		else if (tree[index].lazy != 0) {
			applyLazy(index);
		}


		if (lbound == tree[index].lbound && rbound == tree[index].rbound) {
			return tree[index].sum;
		}
		else if (rbound <= m) {
			return query(lindex, lbound, rbound, v);
		}
		else if (m < lbound) {
			return query(rindex, lbound, rbound, v);
		}
		else {
			return query(lindex, lbound, m, v) + query(rindex, m + 1, rbound, v);
		}
	}
} SegTree;

int main() {
	int N, M, K;
	int q;
	li v;
	int l, r;
	vi arr;
	SegTree segtree;

	scanf("%d %d %d", &N, &M, &K);
	arr.assign(N, 0);

	for (int n = 0; n < N; n++) {
		scanf("%lld", &v);
		arr[n] = v;
	}

	segtree.initSegTree(arr);

	for (int n = 0; n < M + K; n++) {
		scanf("%d", &q);
		if (q == 1) {
			scanf("%d %d %lld", &l, &r, &v);
			l--; r--;
			segtree.updateSegTree(make_pair(l, r), v);
		}
		else {
			scanf("%d %d", &l, &r);
			l--; r--;
			printf("%lld\n", segtree.query(1, l, r));
		}
	}

	return 0;
}