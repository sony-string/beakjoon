#include <bits/stdc++.h>
using namespace std;

vector<int> arr;
vector<int> newarr;
void divide(int start, int end) {
	int m = ((start + end) / 2) + 1;
	int i = start, j = m;
	for (int k = start; k <= end; k += 2)
		newarr[i++] = arr[k];
	for (int k = start + 1; k <= end; k += 2)
		newarr[j++] = arr[k];
	for (int k = start; k <= end; k++)
		arr[k] = newarr[k];
	if (end - start + 1 > 2) {
		divide(start, m - 1);
		divide(m, end);
	}
}

int main() {
	int N;
	scanf("%d", &N);
	arr.assign(N, 0);
	newarr.assign(N, 0);
	for (int i = 1; i <= N; i++)
		arr[i - 1] = i;
	divide(0, N - 1);
	for (auto i : arr) {
		printf("%d ", i);
	}
	return 0;
}