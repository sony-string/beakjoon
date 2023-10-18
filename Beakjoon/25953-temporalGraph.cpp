#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<int> dist[2];
	int n, t, m;
	int S, T;
	scanf("%d %d %d", &n, &t, &m);
	scanf("%d %d", &S, &T);
	dist[0].assign(n, 1e9);
	dist[1].assign(n, 1e9);
	dist[0][S] = 0;
	dist[1][S] = 0;
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < m; j++) {
			int s, e, c;
			scanf("%d %d %d", &s, &e, &c);
			dist[1][e] = min(dist[1][e], dist[0][s] + c);
			dist[1][s] = min(dist[1][s], dist[0][e] + c);
		}
		dist[0] = dist[1];
	}
	if (dist[0][T] == (int)1e9) dist[0][T] = -1;
	printf("%d", dist[0][T]);
	return 0;
}