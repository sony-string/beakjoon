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
vi arr1, arr2;
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

bool solve(vi& text, vi& pat) {
	int i = 0, j = 0;
	while (i < text.size()) {
		while (j != -1 && text[i] != pat[j]) {
			j = d[j];
		}
		i++; j++;
		if (j == pat.size()) {
			return true;
		}
	}
	return false;
}

int main() {
	bool isTrue;
	scanf("%d", &N);
	c1.assign(N, 0);
	c2.assign(N, 0);

	for (int i = 0; i < N; i++) {
		scanf("%d", &c1[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &c2[i]);
	}

	sort(c1.begin(), c1.end());
	sort(c2.begin(), c2.end());
	for (int i = 0; i < N - 1; i++) {
		arr1.push_back(c1[i + 1] - c1[i]);
	}
	arr1.push_back(c1[0] + 360000 - c1[N - 1]);
	for (int i = 0; i < N - 1; i++) {
		arr2.push_back(c2[i + 1] - c2[i]);
	}
	arr2.push_back(c2[0] + 360000 - c2[N - 1]);

	for (int i = 0; i < N; i++) {
		arr1.push_back(arr1[i]);
	}

	preprocessKMP(arr2);
	isTrue = solve(arr1, arr2);

	if (isTrue) {
		printf("possible");
	}
	else {
		printf("impossible");
	}

	return 0;
}