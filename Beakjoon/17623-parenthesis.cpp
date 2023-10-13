#include <bits/stdc++.h>
using namespace std;

char d[7][5] = { {0}, { 1, 2, 0}, {3, 4, 0}, { 5, 6, 0}, { 1, 2, 5, 6, 0}, {3, 4, 5, 6, 0}, {1, 5 ,6, 2, 0} };
char* dp[1001];
int lendp[1001] = { 0, 2, 2, 2, 4, 4, 4 };
char newstr[2001];
const int mul[3] = { 2, 3, 5 };
char* solve(int n) {
	if (n < 7) return dp[n];
	int mlen = 2000;
	for (int i = 0; i < 3; i++) {
		if (n % mul[i] != 0) continue;
		mlen = min(mlen, lendp[n / mul[i]] + 2);
	}
	for (int i = 1; i <= n / 2; i++) {
		mlen = min(mlen, lendp[n - i] + lendp[i]);
	}
	char* str = new char[mlen + 1];
	str[0] = 127;
	str[1] = 0;

	for (int i = 1; i <= n / 2; i++) {
		if (lendp[n - i] + lendp[i] != mlen) continue;
		int cmp = strcmp(dp[i], dp[n - i]);
		if (cmp <= 0) {
			strcpy(newstr, dp[i]);
			strcat(newstr, dp[n - i]);
		}
		else {
			strcpy(newstr, dp[n - i]);
			strcat(newstr, dp[i]);
		}
		if (strcmp(str, newstr) > 0)
			strcpy(str, newstr);
	}

	for (int i = 0; i < 3; i++) {
		if (n % mul[i] != 0 || lendp[n / mul[i]] + 2 != mlen) continue;
		int l = lendp[n / mul[i]];
		strcpy(newstr + 1, dp[n / mul[i]]);
		newstr[0] = 1 + (i * 2);
		newstr[l + 1] = 2 + (i * 2);
		newstr[l + 2] = 0;
		int cmp = strcmp(str, newstr);
		if (cmp > 0)
			strcpy(str, newstr);
	}
	lendp[n] = mlen;
	return str;
}

int main() {
	int N = 1000;
	for (int i = 1; i < 7; i++) {
		dp[i] = d[i];
	}
	for (int i = 7; i <= N; i++) {
		dp[i] = solve(i);
	}
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < lendp[N]; i++) {
			switch (dp[N][i]) {
			case 1:
				printf("(");
				break;
			case 2:
				printf(")");
				break;
			case 3:
				printf("{");
				break;
			case 4:
				printf("}");
				break;
			case 5:
				printf("[");
				break;
			default:
				printf("]");
			}
		}
		printf("\n");
	}
	return 0;
}