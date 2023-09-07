#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;


typedef struct Node {
	int l, r;
	vi arr;
} Node;

void merge(vi& dst, const vi& lhs, const vi& rhs) {
	int l = 0, r = 0, i = 0;

	while (l < lhs.size() && r < rhs.size()) {
		if (lhs[l] <= rhs[r]) {
			dst[i] = lhs[l];
			i++; l++;
		}
		else {
			dst[i] = rhs[r];
			i++; r++;
		}
	}

	while (l < lhs.size()) {
		dst[i] = lhs[l];
		i++; l++;
	}

	while (r < rhs.size()) {
		dst[i] = rhs[r];
		i++; r++;
	}
}

typedef struct SegTree {
	int size;
	Node* tree;

	void makeSegTree(const vi& arr, int v, int l, int r) {
		int lindex = v * 2;
		int rindex = lindex + 1;
		int m = l + r;
		m /= 2;
		tree[v].l = l;
		tree[v].r = r;

		if (l != r) {
			makeSegTree(arr, lindex, l, m);
			makeSegTree(arr, rindex, m + 1, r);
			tree[v].arr.assign(r - l + 1, 0);
			merge(tree[v].arr, tree[lindex].arr, tree[rindex].arr);
		}
		else {
			tree[v].arr.assign(1, 0);
			tree[v].arr[0] = arr[l];
		}
	}

	void initSegTree(const vi& arr) {
		int logSize = (int)log2(arr.size()) + 1;
		size = 2 * (int)pow(2, logSize) + 1;
		tree = new Node[size];
		makeSegTree(arr, 1, 0, arr.size() - 1);
	}

	int query(int v, int l, int r, const int& k) {
		int lindex = v * 2;
		int rindex = lindex + 1;
		int m = tree[v].l + tree[v].r;
		m /= 2;

		if (l == tree[v].l && r == tree[v].r) {
			return tree[v].arr.size() - 
				(upper_bound(tree[v].arr.begin(), tree[v].arr.end(), k) - tree[v].arr.begin());
		}
		else if (m >= r) {
			return query(lindex, l, r, k);
		}
		else if (m < l) {
			return query(rindex, l, r, k);
		}
		else {
			return query(lindex, l, m, k) + query(rindex, m + 1, r, k);
		}
	}
} St;

int main() {
	int N, M;
	vi arr;
	int i, j, k;
	St segtree;

	scanf("%d", &N);
	arr.assign(N, 0);
	for (int n = 0; n < N; n++) {
		scanf("%d", &arr[n]);
	}

	segtree.initSegTree(arr);
	scanf("%d", &M);
	for (int m = 0; m < M; m++) {
		scanf("%d %d %d", &i, &j, &k);
		i--; j--;
		printf("%d\n", segtree.query(1, i, j, k));
	}

	return 0;
}