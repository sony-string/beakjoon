#include <bits/stdc++.h>
using namespace std;

char str[1'000'001];
int len;
vector<int> fail;
int maxlen = 0;

int solve() {
    int ans = 0;
    int j = -1;
    fail.assign(len + 1, 0);
    fail[0] = -1;
    for (int i = 0; i < len; i++) {
        maxlen = max(fail[i], maxlen);
        while (j != -1 && str[i] != str[j]) j = fail[j];
        fail[i + 1] = ++j;
    }
    j = fail.back();
    while (j != -1 && !ans) {
        if (j <= maxlen) {
            ans = j;
            break;
        }
        j = fail[j];
    }
    return ans;
}

int main() {
	scanf("%s", str);
	len = strlen(str);
	int ans = solve();
    for (int i = 0; i < ans; i++) {
        printf("%c", str[i]);
    }
    if (!ans) printf("-1");
	return 0;
}