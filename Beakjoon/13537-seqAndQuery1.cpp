#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
	int start, end;
	vector<int> arr;
} Node;

void init(vector<Node>& tree, const vector<int>& arr, int node, int start, int end) {
	tree[node].start = start;
	tree[node].end = end;
	if (start == end) {
		tree[node].arr.assign(1, arr[start]);
	}
	else {
		init(tree, arr, node * 2, start, (start + end) / 2);
		init(tree, arr, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node].arr.assign(end - start + 1, 0);
		merge(tree[node * 2].arr.begin(), tree[node * 2].arr.end(),
			tree[node * 2 + 1].arr.begin(), tree[node * 2 + 1].arr.end(),
			tree[node].arr.begin());
	}
}

int query(const vector<Node>& tree, int node, int i, int j, int k) {
	int m = (tree[node].start + tree[node].end) / 2;
	if (i == tree[node].start && j == tree[node].end) {
		return (tree[node].arr.end() - upper_bound(tree[node].arr.begin(), tree[node].arr.end(), k));
	}
	else if (j <= m) {
		return query(tree, node * 2, i, j, k);
	}
	else if (m < i) {
		return query(tree, node * 2 + 1, i, j, k);
	}
	else {
		return query(tree, node * 2, i, m, k) + query(tree, node * 2 + 1, m + 1, j, k);
	}
}

void solve(int N, int M, vector<int>& A) {
	int i, j, k;
	vector<Node> tree;
	tree.assign(2 * (int)pow(2, log2(N) + 1) + 1, Node());
	init(tree, A, 1, 0, N - 1);

	for (int m = 0; m < M; m++) {
		scanf("%d %d %d", &i, &j, &k);
		i--; j--;
		printf("%d\n", query(tree, 1, i, j, k));
	}
}

int main() {
	int N, M;
	vector<int> A;
	scanf("%d", &N);
	A.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}
	scanf("%d", &M);
	solve(N, M, A);
	return 0;
}