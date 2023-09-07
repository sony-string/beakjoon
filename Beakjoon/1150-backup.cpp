#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#define _MAX 1000000001

int main() {
	int** dp;
	int cur, next, nnext;

	int numPoints;
	int* arr;
	int maxK;
	int s, e;
	int len;
	int best = _MAX;

	scanf("%d %d", &numPoints, &maxK);
	dp = new int* [3];
	for (int i = 0; i < 3; i++) {
		dp[i] = new int[maxK + 1];
		memset(dp[i], -1, (maxK + 1) * sizeof(int));
	}
	arr = new int[numPoints];
	for (int i = 0; i < numPoints; i++) {
		scanf("%d", arr + i);
	}
	cur = 0; next = 1; nnext = 2;
	dp[cur][0] = 0;
	dp[next][0] = 0;
	dp[nnext][1] = arr[1] - arr[0];
	dp[nnext][0] = 0;
	if (maxK == 1) {
		best = dp[nnext][1];
	}
	cur = (cur + 1) % 3;
	next = (next + 1) % 3;
	nnext = (nnext + 1) % 3;

	for (int i = 1; i < numPoints - 1; i++) {
		s = numPoints - i;
		s /= 2;

		if (maxK > s) {
			s = maxK - s;
		}
		else {
			s = 0;
		}

		e = i / 2;
		for (int k = s; k <= e && k < maxK; k++) {
			if (dp[cur][k] == -1 || dp[cur][k] + maxK - k + 1 >= best) {
				continue;
			}
			if (i < numPoints - 2) {
				len = dp[cur][k] + arr[i + 1] - arr[i];
				if (len + maxK - k < best) {
					if (dp[nnext][k + 1] > len || dp[nnext][k + 1] == -1) {
						dp[nnext][k + 1] = len;
						if (k + 1 == maxK && best > len) {
							best = len;
						}
					}
				}
			}
			else {
				len = dp[cur][maxK - 1] + arr[i + 1] - arr[i];
				if (best > len) {
					best = len;
				}
			}

			if (dp[next][k] > dp[cur][k] || dp[next][k] == -1) {
				dp[next][k] = dp[cur][k];
			}

			dp[cur][k] = -1;
		}

		cur = (cur + 1) % 3;
		next = (next + 1) % 3;
		nnext = (nnext + 1) % 3;
	}

	printf("%d", best);
	return 0;
}