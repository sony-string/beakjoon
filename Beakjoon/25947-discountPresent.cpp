#include <bits/stdc++.h>
using namespace std;


int main() {
	int N, b, a;
	int ans = 0, l = 0, r = 0, sum = 0;
	vector<int> arr;
	scanf("%d %d %d", &N, &b, &a);
	arr.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr.begin(), arr.end());
	for (int i = 0; i < a; i++) {
		sum += arr[i] / 2;
		if (sum <= b) ans++;
		else break;
	}
	if (ans < a) {
		printf("%d", ans);
		return 0;
	}
	for (int i = ans; i < N; i++) {
		sum += arr[i] / 2;
		sum += arr[l++] / 2;
		if (sum <= b) ans++;
		else break;
	}
	printf("%d", ans);
	return 0;
}