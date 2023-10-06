#include <bits/stdc++.h>
using namespace std;

vector<int> fail;
void prekmp(int* pat, int L) {
	fail.assign(L, 0);
	fail[0] = -1;
	int j = -1;
	for (int i = 0; i < L - 1; i++) {
		while (j != -1 && pat[j] != pat[i]) j = fail[j];
		j++;
		fail[i + 1] = j;
	}
}

bool match(int* t, int* pat) {
	int del;
	int j = 0;
	for (int i = 1; t[i]; i++) {
		del = t[i] - t[i - 1];
		while (j != -1 && pat[j] != del) j = fail[j];
		j++;
		if (pat[j] > 10000) return true;
	}
	return false;
}

int main() {
	int N;
	vector<int*> strs;
	int K, del, befo, next;
	int L;
	int* melody;
	
	scanf("%d", &N);
	strs.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &K);
		strs[i] = new int[K + 1];
		for (int j = 0; j < K; j++) {
			scanf("%d", strs[i] + j);
		}
		strs[i][K] = 0;
	}
	scanf("%d", &L);
	melody = new int[L + 1];
	scanf("%d", &befo);
	for (int i = 0; i < L - 1; i++) {
		scanf("%d", &next);
		del = next - befo;
		melody[i] = del;
		befo = next;
	}
	melody[L - 1] = (int)1e9;
	prekmp(melody, L);

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (match(strs[i], melody)) { printf("%d ", i + 1); cnt++; }
	}
	if (cnt == 0) printf("-1");

	return 0;
}