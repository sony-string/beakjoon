#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	deque<int> pd, nd;
	priority_queue<int, vector<int>, greater<int>> nq;
	priority_queue<int> pq;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		if (n < 0) nq.emplace(n);
		else pq.emplace(n);
	}
	bool pback = true;
	while (!pq.empty()) {
		int n = pq.top();
		pq.pop();
		if (pback) pd.push_back(n);
		else pd.push_front(n);
		pback = !pback;
	}
	pback = true;
	while (!nq.empty()) {
		int n = nq.top();
		nq.pop();
		if (pback) nd.push_back(n);
		else nd.push_front(n);
		pback = !pback;
	}
	if (!nd.empty() && nd.back() < nd.front()) {
		reverse(nd.begin(), nd.end());
	}
	if (!pd.empty() && pd.front() > pd.back()) {
		reverse(pd.begin(), pd.end());
	}
	for (auto& i : nd) {
		printf("%d ", i);
	}
	for (auto& i : pd) {
		printf("%d ", i);
	}
	return 0;
}