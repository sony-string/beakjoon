#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long li;

li solve(vi& arr, int l, int r, int e) {
	vi sub(e - l, 0);
	li ret = 0;

	if (e - l == 1) return 0;
	else {
		ret += solve(arr, l, (l + r + 1) / 2, r);
		ret += solve(arr, r, (r + e + 1) / 2, e);
	}

	int ll = l, rr = r; 
	int i = 0;
	while (ll < r && rr < e) {
		sub[i++] = min(arr[ll], arr[rr]);
		if (arr[ll] <= arr[rr]) ll++;
		else {
			rr++;
			ret += r - ll;
		}
	}
	while (ll < r) {
		sub[i++] = arr[ll++];
	}
	while (rr < e)
		sub[i++] = arr[rr++];

	for (auto& e : sub) {
		arr[l++] = e;
	}
	return ret;
}


int main() {
	int N;
	scanf("%d", &N);
	vi arr(N, 0);
	for (auto& i : arr) scanf("%d", &i);
	li ans = solve(arr, 0, (N + 1) / 2, N);
	printf("%lld", ans);
	return 0;
}