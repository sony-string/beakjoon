//#include <bits/stdc++.h>
//using namespace std;
//
//typedef long long li;
//typedef vector<int> vi;
//typedef pair<int, int> ii;
//typedef vector<ii> vii;
//
//constexpr li MOD = 1e9 + 7;
//struct segnode {
//	int s, e;
//	li v;
//	segnode(int start, int end, li value) : s(start), e(end), v(value) {}
//	segnode() : segnode(0, 0, 0) {}
//};
//
//struct segtree {
//	int size;
//	vector<segnode> tree;
//	segtree(int maxsize) : tree(maxsize), size(maxsize) {}
//	li init(vi& arr, int s, int e, int id = 1) {
//		segnode& node = tree[id];
//		if (s + 1 == e) node = segnode(s, e, arr[s]);
//		else node = segnode(s, e, init(arr, s, (s + e) / 2, id * 2) * init(arr, (s + e) / 2, e, id * 2 + 1) % MOD);
//		return node.v;
//	}
//	li update(int c, li v, int id = 1) {
//		segnode& node = tree[id];
//		if (node.s + 1 == node.e) return node.v = v;
//		else if (c < (node.s + node.e) / 2) return node.v = update(c, v, id * 2) * tree[id * 2 + 1].v % MOD;
//		else return node.v = update(c, v, id * 2 + 1) * tree[id * 2].v % MOD;
//	}
//	li query(int s, int e, int id = 1) {
//		segnode& node = tree[id];
//		if (node.s == s && node.e == e) return node.v;
//		else if ((node.s + node.e) / 2 >= e) return query(s, e, id * 2);
//		else if ((node.s + node.e) / 2 <= s) return query(s, e, id * 2 + 1);
//		else return query(s, (node.s + node.e) / 2, id * 2) * query((node.s + node.e) / 2, e, id * 2 + 1) % MOD;
//	}
//};
//
//int main() {
//	int N, M, K;
//	scanf("%d %d %d", &N, &M, &K);
//	int Q = M + K;
//	vi arr(N + 1, 1);
//	for (int i = 1; i <= N; i++) {
//		scanf("%d", &arr[i]);
//	}
//	segtree sg(pow(2, (int)log2(N) + 2) + 1);
//	sg.init(arr, 1, N + 1);
//	for (int i = 0; i < Q; i++) {
//		int a, b, c;
//		scanf("%d %d %d", &a, &b, &c);
//		if (a == 1) {
//			sg.update(b, c);
//		}
//		else {
//			printf("%lld\n", sg.query(b, c + 1));
//		}
//	}
//	return 0;
//}