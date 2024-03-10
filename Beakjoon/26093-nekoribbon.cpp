#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;


int dp[102][10001];

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	vi arr;
	arr.assign(K, 0);
	priority_queue<int, vi, greater<int>> pq;
	int f = 0, s = 0;	
	for (int i = 1; i <= N; i++) {		
		for (int k = 0; k < K; k++) {
			int e;
			scanf("%d", &e);
			if (dp[i - 1][k] == f) {
				dp[i][k] = s + e;				
			}
			else {
				dp[i][k] = f + e;
			}
			pq.push(dp[i][k]);
			if (pq.size() > 2) pq.pop();
		}
		s = pq.top(); pq.pop();
		f = pq.top(); pq.pop();
	}
	printf("%d", f);
	return 0;
}