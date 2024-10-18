#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long li;

class union_find {
private:
	vi r;
	vi p;
	int size;
	int merge_cnt;
public:
	union_find(int n): size(n), merge_cnt(0) {
		p.assign(n + 1, 0);
		for (int i = 0; i <= n; i++) {
			p[i] = i;
		}
		r.assign(n + 1, 0);
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
		if (r[pa] > r[pb]) {
			p[a] = p[b];
			p[pa] = p[pb];			
		} else {
			p[b] = p[a];
			p[pb] = p[pa];
			if (r[pa] == r[pb]) {
				r[pa] += 1;
			}
		}
		merge_cnt++;
		return true;
	}
	
	bool is_connected() {
		return (merge_cnt == size -1);
	}
};

int main() {
#ifdef TEST
	freopen("input.txt", "r", stdin);
#endif
	int ans_cnt = 0;
	li ans_sum = 0;

	int N, M;
	scanf("%d %d", &N, &M);

	vector<array<int, 3>> E;
	E.assign(M, {});

	for (auto& e : E) {
		int s, d, c;
		scanf("%d %d %d", &s, &d, &c);
		e[0] = c; e[1] = s; e[2] = d;
	}

	sort(E.begin(), E.end());
	

	li optimal = 0;
	vector<bool> pass(M, false);
	int test_last;
	do {
		auto uf = union_find(N);
		for (int i = 0; i < M; i++) {			
			if (uf.merge(E[i][1], E[i][2])) {
				optimal += E[i][0];
				if (uf.is_connected()) {
					test_last = i + 1;
					break;
				}
			}
			else {
				pass[i] = true;
			}
		}
	} while (0);


	for (int ex = 0; ex < test_last; ex++) {
		if (pass[ex]) continue;
		auto uf = union_find(N);
		li csum = 0;
		for (int i = 0; i < M; i++) {
			if (i == ex) continue;
			if (uf.merge(E[i][1], E[i][2])) {
				csum += E[i][0];
				if (uf.is_connected()) break;				
			}
		}

		if (!uf.is_connected() || csum != optimal) {
			ans_cnt++;
			ans_sum += E[ex][0];
		}
	}

	printf("%d %lld", ans_cnt, ans_sum);

	return 0;
}