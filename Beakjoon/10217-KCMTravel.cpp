#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;


int main() {
	freopen("input.txt", "r", stdin);
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	iii node;
	vi* dpCut;
	vector<iii>* adjList;
	int** dp;
	
	int N, M, K, T;
	int u, v, c, d;
	int costSum, timeSum, nextNode;
	int bestTime;

	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &N, &M, &K);
		dp = new int * [N + 1];
		adjList = new vector<iii>[N + 1];
		dpCut = new vi[N + 1];
		for (int i = 0; i <= N; i++) {
			dp[i] = new int[M + 1];
			memset(dp[i], -1, sizeof(int) * (M + 1));
			dpCut[i].assign(M + 1, (int)1e9);
		}
		dpCut[1].assign(M + 1, 0);
		dp[1][0] = 0;
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &u, &v, &c, &d);
			adjList[u].emplace_back(v, make_pair(c, d));
		}

		pq.emplace(0, make_pair(1, 0));
		while (!pq.empty()) {
			node = pq.top();
			pq.pop();
			
			d = node.first;
			u = node.second.first;
			c = node.second.second;


			if (dp[u][c] < d || u == N) {
				continue;
			}

			for (const auto& edge : adjList[u]) {
				costSum = edge.second.first + c;
				timeSum = edge.second.second + d;
				nextNode = edge.first;
				if (costSum > M) {
					continue;
				}
				else if (dp[nextNode][costSum] < 0 || timeSum < dp[nextNode][costSum]) {
					if (dpCut[nextNode][costSum - 1] <= timeSum) {
						continue;
					}
					else {
						for (int i = costSum; i <= M; i++) {
							if (dpCut[nextNode][i] > timeSum) {
								dpCut[nextNode][i] = timeSum;
							}
							else {
								break;
							}
						}
					}
					dp[nextNode][costSum] = timeSum;
					pq.emplace(timeSum, make_pair(nextNode, costSum));
				}
			}
		}

		bestTime = 1e9;
		for (int i = 1; i < M; i++) {
			if (dp[N][i] < 0) {
				continue;
			}
			else {
				bestTime = min(bestTime, dp[N][i]);
			}
		}

		if (bestTime != 1e9) {
			printf("%d\n", bestTime);
		}
		else {
			printf("Poor KCM\n");
		}

		pq = priority_queue<iii, vector<iii>, greater<iii>>();
		for (int i = 0; i <= N; i++) {
			delete[](dp[i]);
		}
		delete[](dp);
		delete[](adjList);
		delete[](dpCut);
	}

	return 0;
}
