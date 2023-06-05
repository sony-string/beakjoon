#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;


typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int dp[1001][1001];
ii backtrack[1001][1001];
vii arr;

int N, W;


void solve() {
	int i = 1, j = 0, d;
	for (; i < W; i++) {
		for (j = 0; j < i; j++) {
			d = abs(arr[i].first - arr[i + 1].first) + abs(arr[i].second - arr[i + 1].second);
			if (dp[i + 1][j] != 0) {
				if (dp[i + 1][j] > dp[i][j] + d) {
					backtrack[i + 1][j].first = i;
					backtrack[i + 1][j].second = j;
					dp[i + 1][j] = dp[i][j] + d;
				}
			}
			else {
				dp[i + 1][j] = dp[i][j] + d;
				backtrack[i + 1][j].first = i;
				backtrack[i + 1][j].second = j;
			}

			if (dp[j][i + 1] != 0) {
				if (dp[j][i + 1] > dp[j][i] + d) {
					backtrack[j][i + 1].first = j;
					backtrack[j][i + 1].second = i;
					dp[j][i + 1] = dp[j][i] + d;
				}
			}
			else {
				dp[j][i + 1] = dp[j][i] + d;
				backtrack[j][i + 1].first = j;
				backtrack[j][i + 1].second = i;
			}

			if (j != 0) {
				d = abs(arr[j].first - arr[i + 1].first) + abs(arr[j].second - arr[i + 1].second);
				if (dp[i][i + 1] != 0) {
					if (dp[i][i + 1] > dp[i][j] + d) {
						dp[i][i + 1] = dp[i][j] + d;
						backtrack[i][i + 1].first = i;
						backtrack[i][i + 1].second = j;
					}
				}
				else {
					dp[i][i + 1] = dp[i][j] + d;
					backtrack[i][i + 1].first = i;
					backtrack[i][i + 1].second = j;
				}

				if (dp[i + 1][i] != 0) {
					if (dp[i + 1][i] > dp[j][i] + d) {
						dp[i + 1][i] = dp[j][i] + d;
						backtrack[i + 1][i].first = j;
						backtrack[i + 1][i].second = i;
					}
				}
				else {
					dp[i + 1][i] = dp[j][i] + d;
					backtrack[i + 1][i].first = j;
					backtrack[i + 1][i].second = i;
				}
			}
		}

		d = abs(arr[i + 1].first - 1) + abs(arr[i + 1].second - 1);
		if (dp[i + 1][i] > dp[0][i] + d || dp[i + 1][i] == 0) {
			dp[i + 1][i] = dp[0][i] + d;
			backtrack[i + 1][i].first = 0;
			backtrack[i + 1][i].second = i;
		}

		d = abs(arr[i + 1].first - N) + abs(arr[i + 1].second - N);
		if (dp[i][i + 1] > dp[i][0] + d || dp[i][i + 1] == 0) {
			dp[i][i + 1] = dp[i][0] + d;
			backtrack[i][i + 1].first = i;
			backtrack[i][i + 1].second = 0;
		}
	}
}


int main() {
	int r, c;
	int min = 2000000000;
	scanf("%d %d", &N, &W);

	arr.push_back(make_pair(0, 0));
	for (int i = 0; i < W; i++) {
		scanf("%d %d", &r, &c);
		arr.push_back(make_pair(r, c));
	}
	
	dp[1][0] = abs(arr[1].first - 1) + abs(arr[1].second - 1);
	dp[0][1] = abs(arr[1].first - N) + abs(arr[1].second - N);
	backtrack[1][0] = make_pair(0, 0);
	backtrack[0][1] = make_pair(0, 0);
	solve();

	for (int i = 0; i < W; i++) {
		if (min > dp[W][i]) {
			min = dp[W][i];
			r = W;
			c = i;
		}
		if (min > dp[i][W]) {
			min = dp[i][W];
			r = i;
			c = W;
		}
	}

	ii befo;
	ii cur;
	vi route;

	cur.first = r;
	cur.second = c;
	while (cur.first != 0 || cur.second != 0) {
		befo = backtrack[cur.first][cur.second];
		if (befo.first == cur.first) {
			route.push_back(2);
		}
		else {
			route.push_back(1);
		}
		cur = befo;
	}

	printf("%d\n", min);
	while (!route.empty()) {
		printf("%d\n", route.back());
		route.pop_back();
	}
	return 0;
}