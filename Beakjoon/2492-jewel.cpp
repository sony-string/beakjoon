#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<int, int> ii;
typedef vector<ii> vii;
int main() {
	int N, M, T, K;
	vii arr;
	scanf("%d %d %d %d", &N, &M, &T, &K);
	arr.resize(T);
	for (auto& i : arr) {
		scanf("%d %d", &i.x, &i.y);
	}
	int ans = 0;
	int ansx, ansy;
	for (int i = 0; i < T; i++) {
		for (int j = 0; j < T; j++) {
			int xx, yy;
			xx = arr[i].x;
			yy = arr[j].y;
			if (arr[i].x + K > N) xx = N - K;
			if (arr[j].y + K > M) yy = M - K;
			int cnt = 0;
			for (auto& p : arr) {
				if (p.x >= xx && p.x <= xx + K && p.y >= yy && p.y <= yy + K)
					cnt++;
			}
			if (ans < cnt) {
				ans = cnt;
				ansx = xx;
				ansy = yy;
			}
		}
	}
	printf("%d %d\n", ansx, ansy + K);
	printf("%d", ans);
	return 0;
}