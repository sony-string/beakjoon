#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
	int N, M;
	vi a, b;
	scanf("%d", &N);
	a.assign(N, 0);
	for (auto& i : a) {
		scanf("%d", &i);
	}
	scanf("%d", &M);
	b.assign(M, 0);
	for (auto& i : b) {
		scanf("%d", &i);
	}
	vi ans;
	int ai = 0, bi = 0;
	while (ai < N && bi < M) {
		int same = 0;
		int at, bt;
		for (int i = ai; i < N; i++) {
			for (int j = bi; j < M; j++) {
				if (a[i] == b[j]) {
					if (same < a[i]) {
						at = i;
						bt = j;
						same = a[i];
					}
				}
			}
		}
		if (same) {
			ans.push_back(same);
			ai = at + 1;
			bi = bt + 1;
		}
		else {
			break;
		}
	}
	int anssize = ans.size();
	if (anssize) {
		printf("%d\n", anssize);
		for (auto& i : ans) {
			printf("%d ", i);
		}
	}
	else {
		printf("0");
	}
	return 0;
}