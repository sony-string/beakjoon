#include <xkeycheck.h>
#define private public
#define protected public
#include <cstdio>
#include <queue>
using namespace std;

int main() {
	priority_queue<int, vector<int>, greater<int>> pq;
	int N;
	int ans = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		pq.push(n);
	}
	while (pq.size() > 2) {		
		int n;
		ans += n = pq.c[0] + min(pq.c[1], pq.c[2]);
		pq.pop(); pq.pop();
		pq.push(n);
	}
	if (N > 1) ans += pq.c[0] + pq.c[1];
	printf("%d", ans);
	return 0;
}