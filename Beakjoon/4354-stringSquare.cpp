#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vi table;

void computePartialMatchTable(const char* pattern) {
	int m = strlen(pattern);
	table = vi(m + 1, 0);
	int j = -1, i = 0;
	table[0] = -1;
	while (i < m) {
		while (j >= 0 && pattern[i] != pattern[j]) {
			j = table[j];
		}
		i++;
		j++;
		table[i] = j;
	}
}

int solve(const char* text) {
	int n = strlen(text);
	if (n == 1) {
		return 1;
	}
	else if (n == 2 && text[0] == text[1]) {
		return 1;
	}
	else if (n == 2) {
		return 2;
	}

	computePartialMatchTable(text);

	int max_prefix_suffix_len = table[n];

	if (max_prefix_suffix_len > 0 && n % (n - max_prefix_suffix_len) == 0) {
		return n - max_prefix_suffix_len;
	}
	else {
		return n;
	}
}


int main() {
	char* str = new char[1000001];
	int ans;

	while (true) {
		scanf("%s", str);
		if (str[0] == '.') {
			break;
		}
		ans = strlen(str) / solve(str);
	
		printf("%d\n", ans);
	}

	return 0;
}