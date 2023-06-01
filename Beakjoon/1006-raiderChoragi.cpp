#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

int cases;
int W, N;
int* arr[2];
int** dp;

enum {
	up = 0, down = 1, both = 2, none = 3
};


int solve(int flag) {
	int i;
	int best = 2 * N + 1;

	for (i = 0; i < N - 1; i++) {
		for (int j = 0; j < 3; j++) {
			if (dp[i][j] == -1) {
				continue;
			}
			else if (j == up) {
				if (arr[0][i] + arr[0][i + 1] <= W) {
					if (dp[i + 1][down] == -1 || dp[i + 1][down] > dp[i][j] + 1) {
						dp[i + 1][down] = dp[i][j] + 1;
					}
				}
				
				if (dp[i + 1][both] == -1 || dp[i + 1][both] > dp[i][j] + 1) {
					dp[i + 1][both] = dp[i][j] + 1;
				}
			}
			else if (j == down) {
				if (arr[1][i] + arr[1][i + 1] <= W) {
					if (dp[i + 1][up] == -1 || dp[i + 1][up] > dp[i][j] + 1) {
						dp[i + 1][up] = dp[i][j] + 1;
					}
				}
				
				if (dp[i + 1][both] == -1 || dp[i + 1][both] > dp[i][j] + 1) {
					dp[i + 1][both] = dp[i][j] + 1;
				}
			}
			else if (j == both) {
				if (arr[0][i] + arr[1][i] <= W) {
					if (dp[i + 1][both] > dp[i][both] + 1 || dp[i + 1][both] == -1) {
						dp[i + 1][both] = dp[i][both] + 1;
					}
				}
				if (arr[0][i] + arr[0][i + 1] <= W) {
					if (arr[1][i] + arr[1][i + 1] <= W) {
						if (i == N - 2) {
							best = dp[i][j] + 2;
						}
						else {
							dp[i + 2][both] = dp[i][j] + 2;
						}
					}
					if (dp[i + 1][down] == -1 || dp[i + 1][down] > dp[i][j] + 2) {
						dp[i + 1][down] = dp[i][j] + 2;
					}
				}

				if (arr[1][i] + arr[1][i + 1] <= W) {
					if (dp[i + 1][up] == -1 || dp[i + 1][up] > dp[i][j] + 2) {
						dp[i + 1][up] = dp[i][j] + 2;
					}
				}

				if (dp[i + 1][both] == -1 || dp[i + 1][both] > dp[i][j] + 2) {
					dp[i + 1][both] = dp[i][j] + 2;
				}
			}
		}
	}

	if (flag == both) {
		if (dp[N - 1][both] != -1) {
			best = MIN(best, dp[N - 1][both]);
		}
		if (dp[N - 1][up] != -1) {
			best = MIN(best, dp[N - 1][up]);
		}
		if (dp[N - 1][down] != -1) {
			best = MIN(best, dp[N - 1][down]);
		}
	}
	else if (flag == up) {
		if (dp[N - 1][down] != -1) {
			best = MIN(best, dp[N - 1][down] + 1);
		}
		if (dp[N - 1][both] != -1) {
			best = MIN(best, dp[N - 1][both] + 1);
		}
		if (dp[N - 1][up] != -1) {
			best = MIN(best, dp[N - 1][up]);
		}
	}
	else if (flag == down) {
		if (dp[N - 1][down] != -1) {
			best = MIN(best, dp[N - 1][down]);
		}
		if (dp[N - 1][both] != -1) {
			best = MIN(best, dp[N - 1][both] + 1);
		}
		if (dp[N - 1][up] != -1) {
			best = MIN(best, dp[N - 1][up] + 1);
		}
	}
	else {
		if (dp[N - 1][down] != -1) {
			best = MIN(best, dp[N - 1][down] + 1);
		}
		if (dp[N - 1][both] != -1) {
			if (arr[0][N - 1] + arr[1][N - 1] > W) {
				best = MIN(best, dp[N - 1][both] + 2);
			}
			else {
				best = MIN(best, dp[N - 1][both] + 1);
			}
		}
		if (dp[N - 1][up] != -1) {
			best = MIN(best, dp[N - 1][up] + 1);
		}
	}

	return best;
}


int main() {

	arr[0] = new int[10000];
	arr[1] = new int[10000];

	dp = new int* [10000];
	for (int i = 0; i < 10000; i++) {
		dp[i] = new int[3];
	}
	int temp, best;

	scanf("%d", &cases);
	for (int T = 0; T < cases; T++) {
		scanf("%d %d", &N, &W);
		for (int i = 0; i < N; i++) {
			scanf("%d", arr[0] + i);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", arr[1] + i);
		}
		best = 2 * N + 1;
		if (N > 1) {
			if (arr[0][0] + arr[0][N - 1] <= W) {
				for (int i = 0; i < N; i++) {
					memset(dp[i], -1, sizeof(int) * 3);
				}
				dp[0][down] = 1;
				temp = solve(up);
				best = MIN(best, temp);
			}

			if (arr[1][0] + arr[1][N - 1] <= W) {
				for (int i = 0; i < N; i++) {
					memset(dp[i], -1, sizeof(int) * 3);
				}
				dp[0][up] = 1;
				temp = solve(down);
				best = MIN(best, temp);
			}

			if (arr[1][0] + arr[1][N - 1] <= W && arr[0][0] + arr[0][N - 1] <= W) {
				for (int i = 0; i < N; i++) {
					memset(dp[i], -1, sizeof(int) * 3);
				}
				dp[1][both] = 2;
				temp = solve(both);
				best = MIN(best, temp);
			}

			for (int i = 0; i < N; i++) {
				memset(dp[i], -1, sizeof(int) * 3);
			}
			dp[0][both] = 0;
			temp = solve(none);
			best = MIN(best, temp);
		}
		else {
			if (arr[0][0] + arr[1][0] <= W) {
				best = 1;
			}
			else {
				best = 2;
			}
		}

		printf("%d\n", best);
	}

	return 0;
}