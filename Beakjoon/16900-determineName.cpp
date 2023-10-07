#include <bits/stdc++.h>
using namespace std;

vector<int> fail;
char* str;
int K;

void prekmp() {
	int j = -1;
	fail.push_back(-1);
	for (int i = 0; str[i]; i++) {
		while (j != -1 && str[j] != str[i]) j = fail[j];
		j++;
		fail.push_back(j);
	}
}

int main() {
	str = new char[500'001];
	scanf("%s %d", str, &K);
	prekmp();
	int len = fail.size() - 1;
	printf("%lld", (long long)(len - fail.back()) * (K - 1) + len);
	return 0;
}