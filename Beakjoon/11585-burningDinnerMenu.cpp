#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

int N;
vi c1, c2;
vi d;

void preprocessKMP(vi& arr) {
	d.assign(arr.size() + 1, -1);
	int i, j;
	d[0] = -1;
	j = -1;
	i = 0;
	while (i < arr.size()) {
		while (j != -1 && arr[i] != arr[j]) {
			j = d[j];
		}
		i++; j++;
		d[i] = j;
	}
}

int solve(vi& text, vi& pat) {
	int count = 0;
	int i = 0, j = 0;
	while (i < text.size()) {
		while (j != -1 && text[i] != pat[j]) {
			j = d[j];
		}
		i++; j++;
		if (j == pat.size()) {
			count++;
			j = d[j];
		}
	}
	return count;
}

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	int answer;
	int GCD;
	char ch;
	scanf("%d", &N);
	c1.assign(2 * N - 1, 0);
	c2.assign(N, 0);

	for (int i = 0; i < N; i++) {
		scanf("%c", &ch);
		while ('A' > ch || 'Z' < ch) {
			scanf("%c", &ch);
		}
		c1[i] = ch;
	}
	for (int i = 0; i < N; i++) {
		scanf("%c", &ch);
		while ('A' > ch || 'Z' < ch) {
			scanf("%c", &ch);
		}
		c2[i] = ch;
	}

	for (int i = 0; i < N - 1; i++) {
		c1[i + N] = c1[i];
	}

	preprocessKMP(c2);
	answer = solve(c1, c2);
	
	GCD = gcd(N, answer);
	printf("%d/%d", answer / GCD, N / GCD);
	return 0;
}