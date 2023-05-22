#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define fore(a, b, c) for(int i = (a); i < (b); i += c)

int main() {
	int budget;
	int numCom;
	int dp[21][301][2];
	int table[21][301];
	int result[21];
	int num;

	scanf("%d %d", &budget, &numCom);

	fore(1, numCom + 1, 1) {
		for (int j = 1; j < budget + 1; j += 1) {
			dp[i][j][0] = -1;
			dp[i][j][1] = 0;
		}
	}


	fore(1, budget + 1, 1) {
		scanf("%d", &num);
		for (int j = 1; j <= numCom; j++) {
			scanf("%d", &table[j][num]);
		}
	}

	fore(1, 301, 1) {
		dp[2][budget - i][0] = table[1][i];
		dp[2][budget - i][1] = i;
	}
	dp[2][budget][0] = 0;
	dp[2][budget][1] = 0;

	fore(2, numCom, 1) {
		for (int k = 0; k <= budget; k++) {
			if (dp[i][k][0] > dp[i + 1][k][0] && dp[i][k][0] >= 0) {
				dp[i + 1][k][0] = dp[i][k][0];
				dp[i + 1][k][1] = 0;
			}
			for (int j = 1; j <= k; j++) {
				if (dp[i][k][0] < 0) {
					continue;
				}
				if (dp[i][k][0] + table[i][j] > dp[i + 1][k - j][0]) {
					dp[i + 1][k - j][0] = dp[i][k][0] + table[i][j];
					dp[i + 1][k - j][1] = j;
				}
			}
		}
	}
	int max = 0;
	int last = 0;
	int sum;
	fore(1, budget + 1, 1) {
		if (dp[numCom][i][0] + table[numCom][i] > max) {
			max = dp[numCom][i][0] + table[numCom][i];
			last = i;
		}
	}
	result[numCom] = last;
	sum = last;
	printf("%d\n", max);
	for (int i = numCom - 1; i > 0; i--) {
		result[i] = dp[i + 1][sum][1];
		sum += result[i];
	}
	fore(1, numCom + 1, 1) {
		printf("%d ", result[i]);
	}
	return 0;
}