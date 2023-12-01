#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<li> vi;

int main() {
	int N, M, sqrtn;
	vi arr;
	vi buk;
	scanf("%d", &N);
	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &arr[i]);
	}
	scanf("%d", &M);
	sqrtn = sqrt(N);
	buk.assign(N / sqrtn + 1, 0);
	for (int q = 0; q < M; q++) {
		int x;
		scanf("%d", &x);
		if (x == 1) {
			int i, j, k;
			scanf("%d %d %d", &i, &j, &k);
			if (i / sqrtn != j / sqrtn) {
				for (int s = (i + sqrtn - 1) / sqrtn; s < (j + 1) / sqrtn; s++) {
					buk[s] += k;
				}
				for (int s = i; s < ((i + sqrtn - 1) / sqrtn) * sqrtn; s++) {
					arr[s] += k;
				}
				for (int s = ((j + 1) / sqrtn) * sqrtn; s <= j; s++) {
					arr[s] += k;
				}
			}
			else {
				for (; i <= j; i++) {
					arr[i] += k;
				}
			}
		}
		else {
			int i;
			scanf("%d", &i);
			printf("%lld\n", arr[i] + buk[i / sqrtn]);
		}
	}
	return 0;
}