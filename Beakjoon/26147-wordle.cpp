#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	vector<char*> str;
	str.assign(N, 0);
	for (int i = 0; i < N; i++) {
		str[i] = new char[6];
		scanf("%s", str[i]);
		int gcnt = 0, ycnt = 0;
		for (int j = 0; j < 5; j++) {
			if (str[i][j] == 'G') gcnt++;
			if (str[i][j] == 'Y') ycnt++;
		}
		if (gcnt == 4 && ycnt == 1) {
			printf("IMPOSSIBLE"); return 0;
		}
	}
	char ans[6] = { 'A', 'B', 'C', 'D', 'E', 0 };
	printf("%s\n", ans);
	for (int i = 0; i < N; i++) {
		char s[6] = { 'A', 'B', 'C', 'D', 'E', 0 };
		vector<int> v;
		for (int j = 0; j < 5; j++) {
			if (str[i][j] != 'G') v.push_back(j);
		}
		if (!v.empty()) v.push_back(v[0]);
		for (int j = 1; j < v.size(); j++) {
			if (str[i][v[j]] == 'Y')
				s[v[j]] = ans[v[j - 1]];
			else
				s[v[j]] = 'Z';
		}
		printf("%s\n", s);
	}
	return 0;
}