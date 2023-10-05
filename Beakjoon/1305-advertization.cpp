#include <bits/stdc++.h>
using namespace std;

vector<int> fail;
void prekmp(char* pat) {
	int len = strlen(pat);
	fail.assign(len + 1, 0);
	fail[0] = -1;
	int j = -1;
	for (int i = 0; i < len; i++) {
		while (j != -1 && pat[j] != pat[i]) j = fail[j];
		j++;
		fail[i + 1] = j;
	}
}

int main() {
	int N;
	scanf("%d", &N);
	char* str = new char[N + 1];
	scanf("%s", str);
	prekmp(str);
	int len = fail[N];
	int overlap = len * 2 - N;
	int ans;
	if (overlap < 0) {
		ans = len - overlap;
	}
	else {
		ans = fail[N - overlap];
	}
	printf("%d", ans);
	return 0;
}