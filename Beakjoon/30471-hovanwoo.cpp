#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;


class union_find {
private:
	vi r;
	vi p;
	vi gsize;
	int merge_cnt;
	int size;
public:
	union_find(int n) : size(n), merge_cnt(0) {
		r.assign(n + 1, 0);
		p.assign(n + 1, 0);
		for (int i = 0; i <= n; i++) {
			p[i] = i;
		}
		gsize.assign(n + 1, 1);
	}

	int find(int a) {
		if (p[a] == a) return a;
		p[a] = find(p[a]);
		return p[a];
	}
	
	bool merge(int a, int b) {
		int pa = find(a);
		int pb = find(b);

		if (pa == pb) return false;
		if (r[pb] < r[pa]) {
			p[pb] = pa;
			p[b] = pa;
			gsize[pa] += gsize[pb];
		}
		else {
			p[pa] = pb;
			p[a] = pb;
			gsize[pb] += gsize[pa];
			if (r[pa] == r[pb]) r[pb]++;
		}
		return true;
	}

	int get_size(int a) {
		return gsize[find(a)];
	}
};


int main() {
	int N, M;
	vector<li> ans;	

	scanf("%d %d", &N, &M);
	ans.assign(M + 1, N);
	union_find uf(N);

	for (int n = 1; n <= M; n++) {
		int a, b;
		scanf("%d %d", &a, &b);
		
		li left = uf.get_size(a);
		li right = uf.get_size(b);
		if (uf.merge(a, b)) {
			li sum = left + right;
			li del = sum * (sum + 1) / 2;

			del -= (left * (left + 1) / 2) + (right * (right + 1) / 2);
			ans[n] = ans[n - 1] + del;
		}
		else {
			ans[n] = ans[n - 1];
		}
	}

	for (int i = 1; i <= M; i++) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}