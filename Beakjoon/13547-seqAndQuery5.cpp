#include <bits/stdc++.h>
using namespace std;

int N, M, sq;
int cnt[1'000'001];
int ans = 0;

typedef struct Q {
	int L, R, k;
	bool operator< (const Q& rhs) {
		if (L / sq != rhs.L / sq) {
			return L / sq < rhs.L / sq;
		}
		else {
			if (L / sq % 2) {
				return R > rhs.R;
			}
			else {
				return R < rhs.R;
			}
		}
	}
} Q;

void ins(int& num) {
	if (++cnt[num] == 1) ans++;
}

void del(int& num) {
	if (--cnt[num] == 0) ans--;
}

int main() {
	scanf("%d", &N);
	sq = sqrt(N + 1);
	vector<Q> que;
	vector<int> arr;
	vector<int> out;

	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &M);
	que.assign(M, Q());
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &que[i].L, &que[i].R);
		que[i].k = i;
	}
	out.assign(M, 0);
	sort(que.begin(), que.end());
	int l = que[0].L, r = que[0].R;
	for (int i = l; i <= r; i++) {
		ins(arr[i]);
	}
	out[que[0].k] = ans;
	for (int i = 1; i < M; i++) {
		while (l < que[i].L) del(arr[l++]);
		while (r > que[i].R) del(arr[r--]);
		while (l > que[i].L) ins(arr[--l]);
		while (r < que[i].R) ins(arr[++r]);
		out[que[i].k] = ans;
	}
	for (const int& i : out) {
		printf("%d\n", i);
	}
	return 0;
}