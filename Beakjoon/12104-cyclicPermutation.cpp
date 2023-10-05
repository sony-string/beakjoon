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

int countMatch(char* t, char* pat) {
	int lent = strlen(t);
	int lenpat = fail.size() - 1;
	int j = 0;
	int cnt = 0;
	for (int i = 0; i < lent; i++) {
		if (j + lenpat > lent)
			break;
		while (j != -1 && pat[j] != t[i]) j = fail[j];
		j++;
		if (j == lenpat) {
			cnt++;
			j = fail[j];
		}
	}
	return cnt;
}

int main() {
	char* A, * B;
	A = new char[100'001];
	B = new char[200'001];
	scanf("%s %s", A, B);
	prekmp(A);
	int len = strlen(B);
	strncpy(B + len, B, len);
	B[len * 2 - 1] = 0;
	printf("%d", countMatch(B, A));
	return 0;
}