#include <bits/stdc++.h>
using namespace std;

typedef long long li;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
	int N, M, K;
	vii arr;
	scanf("%d %d %d", &N, &M, &K);
	arr.assign(K, {});
	for (auto& i : arr) {
		scanf("%d %d", &i.second, &i.first);
	}
	sort(arr.begin(), arr.end());
	priority_queue<int, vi, greater<int>> pq;
	int prefersum = 0;
	int ans = -1;
	bool isfound = false;
	for (auto& i : arr) {
		ans++;
		pq.emplace(i.second);
		prefersum += i.second;
		if (pq.size() >= N) {
			if (pq.size() > N) {
				prefersum -= pq.top();
				pq.pop();
			}
			if (prefersum >= M) {
				isfound = true;
				break;
			}
		}
	}
	if (isfound) {
		printf("%d", arr[ans].first);
	}
	else {
		printf("-1");
	}
	return 0;
}