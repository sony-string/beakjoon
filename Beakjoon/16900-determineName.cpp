#include <bits/stdc++.h>
using namespace std;
int fail[500'001];
char str[500'001];
int main() {
	int K, len = 0, j = -1;
	scanf("%s %d", str, &K);
	fail[0] = -1;
	for (len = 0; str[len]; len++) {
		while (j != -1 && str[j] != str[len]) j = fail[j];
		fail[len + 1] = ++j;
	}
	printf("%lld", (long long)(len - fail[len]) * (K - 1) + len);
	return 0;
}