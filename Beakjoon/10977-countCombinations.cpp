#include <bits/stdc++.h>
using namespace std;

vector<int> fail;
vector<int> str;
vector<int> pat;

void prekmp() {
	fail.assign(pat.size() + 1, 0);
	fail[0] = -1;
	int j = -1;
	for (int i = 0; i < pat.size(); i++) {
		while (j != -1 && pat[j] != pat[i]) j = fail[j];
		j++;
		fail[i + 1] = j;
	}
}

int lastMatch() {
	int last = 0;
	int j = 0;
	for (int i = 0; i < str.size(); i++) {
		while (j != -1 && str[i] != pat[j]) j = fail[j];
		j++;
		if (j == pat.size()) {
			last = i - j + 1;
			j = fail[j];
		}
	}
	return last;
}

void solve(vector<int>& input, int M, int N) {
	str.assign(N * 2 - 1, 0);
	pat.assign(N, 0);
	for (int i = 0; i < N - 1; i++) {
		str[i] = input[i + 1] - input[i];
		pat[i] = str[i];
	}
	str[N - 1] = (M - input[N - 1]) + input[0];
	pat[N - 1] = str[N - 1];
	for (int i = N; i < N * 2 - 1; i++) {
		str[i] = str[i - N];
	}
	prekmp();
	int idx = lastMatch();
	int sum = 0;
	for (int i = idx; i < pat.size(); i++) {
		sum += pat[i];
	}
	printf("%d\n", sum);
}


int main() {
	int T;
	vector<int> ls;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int M, N;
		scanf("%d %d", &M, &N);
		ls.assign(N, 0);
		for (int i = 0; i < N; i++) {
			scanf("%d", &ls[i]);
		}
		solve(ls, M, N);
	}
	return 0;
}