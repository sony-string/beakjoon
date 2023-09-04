#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

typedef long long li;
typedef pair<pair<int, int>, pair<int, int>> SumQuery;
typedef vector<SumQuery> SumQueries;
typedef pair<int, int> Query;
typedef vector<Query> vq;
typedef vector<li> vi;


bool cmp(const SumQuery& lhs, const SumQuery& rhs) {
	return (lhs.first.first > rhs.first.first);
}


typedef struct SegTreeNode {
	int lbound, rbound;
	li sum;
} Node;

typedef struct SegTree {
	int size;
	int nodeCount;
	Node* tree;

	void initSegTree(const vi& arr) {
		size = arr.size();
		int logSize = (int)log2(size) + 1;
		nodeCount = (int)pow(2, logSize) * 2 + 1;
		tree = new Node[nodeCount];

		makeSegTree(arr, 1, 0, size - 1);
	}

	void makeSegTree(const vi& arr, int index, int lbound, int rbound) {
		int lindex = index * 2;
		int rindex = lindex + 1;
		int m = lbound + rbound;
		m /= 2;

		tree[index].lbound = lbound;
		tree[index].rbound = rbound;


		if (lbound == rbound) {
			tree[index].sum = arr[lbound];
			return;
		}
		assert(rindex < nodeCount);
		makeSegTree(arr, lindex, lbound, m);
		makeSegTree(arr, rindex, m + 1, rbound);
		tree[index].sum = tree[lindex].sum + tree[rindex].sum;
	}

	void updateSegTree(vi& arr, const Query& q) {
		int index = 1;
		int m;
		const li d = q.second - arr[q.first];
		arr[q.first] = q.second;

		while (!(tree[index].lbound == tree[index].rbound && tree[index].lbound == q.first)) {
			m = tree[index].lbound + tree[index].rbound;
			m /= 2;
			if (q.first <= m) {
				index *= 2;
			}
			else {
				index = index * 2 + 1;
			}
		}

		while (index > 0) {
			tree[index].sum += d;
			index /= 2;
		}
	}

	li query(const Query& q) {
		return querySegTree(1, q.first, q.second);
	}

	li querySegTree(int index, int lbound, int rbound) {
		int lindex = index * 2;
		int rindex = lindex + 1;
		int m = tree[index].lbound + tree[index].rbound;
		m /= 2;

		if (lbound == tree[index].lbound && rbound == tree[index].rbound) {
			return tree[index].sum;
		}
		else if (rbound <= m) {
			return querySegTree(lindex, lbound, rbound);
		}
		else if (lbound > m) {
			return querySegTree(rindex, lbound, rbound);
		}
		else {
			return querySegTree(lindex, lbound, m) + querySegTree(rindex, m + 1, rbound);
		}
	}

} SegTree;


int main() {
	vq mutateQueries;
	SumQueries sumQueries;
	SegTree segtree;
	vi arr;
	vi answers;
	li num;
	int N, M;
	int i, v, k, j, q;
	int mutateCount;

	scanf("%d", &N);
	arr.assign(N, 0);
	for (int n = 0; n < N; n++) {
		scanf("%lld", &num);
		arr[n] = num;
	}

	scanf("%d", &M);
	for (int m = 0; m < M; m++) {
		scanf("%d", &q);
		if (q == 1) {
			scanf("%d %d", &i, &v);
			mutateQueries.emplace_back(i - 1, v);
		}
		else {
			scanf("%d %d %d", &k, &i, &j);
			sumQueries.emplace_back(make_pair(k, sumQueries.size()),make_pair(i - 1, j - 1));
		}
	}

	sort(sumQueries.begin(), sumQueries.end(), cmp);
	segtree.initSegTree(arr);
	answers.assign(sumQueries.size(), 0);

	mutateCount = 0;
	while (!sumQueries.empty()) {
		while (sumQueries.back().first.first > mutateCount) {
			segtree.updateSegTree(arr, mutateQueries[mutateCount]);
			mutateCount++;
		}
		
		answers[sumQueries.back().first.second] = segtree.query(sumQueries.back().second);
		sumQueries.pop_back();
	}

	for (i = 0; i < answers.size(); i++) {
		printf("%lld\n", answers[i]);
	}

	return 0;
}