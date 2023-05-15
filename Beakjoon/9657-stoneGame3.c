#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choice[3] = { 1, 3, 4 };

int solve(int dp[], int now, int goal) {
	int next = now;
	int opponent;
	int count;
	for (int i = 0; i < 3; i++) {
		next = now + choice[i];
		if (next == goal) {
			dp[now] = 1;
			return 1;
		}
		if (next > goal) {
			continue;
		}
		count = 0;
		for (int k = 0; k < 3; k++) {
			opponent = next + choice[k];
			if (opponent == goal) {
				break;
			}
			if (opponent > goal) {
				count++;
				continue;
			}
			if (dp[opponent] == 1) {
				count++;
				continue;
			}
			else if (dp[opponent] == 0) {
				break;
			}
			if (solve(dp, opponent, goal) != 1) {
				break;
			}
			count++;
		}
		if (count == 3) {
			dp[now] = 1;
			return 1;
		}
	}
	dp[now] = 0;
	return 0;
}

int main() {
	int goal;
	int dp[1001];
	memset(dp, -1, 1001 * sizeof(int));
	int isWin;

	scanf("%d", &goal);
	isWin = solve(dp, 0, goal);
	if (isWin == 1) {
		printf("SK");
	}
	else {
		printf("CY");
	}
	return 0;
}