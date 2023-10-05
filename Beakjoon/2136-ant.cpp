#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> arr;
int N, L, K;

int getId(int kpos) {
	queue<int> q;
	int i = 0;
	if (kpos < 0) {
		kpos = -kpos;
		i = N - 1;
		for (; i >= 0; i--) {
			if (arr[i].first == kpos)
				break;
		}
		q.push(arr[i].second);
		for (i = i - 1; i >= 0; i--) {
			if (arr[i].second > 0)
				q.pop();
			q.push(arr[i].second);
		}
	}
	else {
		i = 0;
		for (; i < N; i++) {
			if (arr[i].first == kpos)
				break;
		}
		q.push(arr[i].second);
		for (i = i + 1; i < N; i++) {
			if (arr[i].second < 0)
				q.pop();
			q.push(arr[i].second);
		}
	}
	return q.front();
}

pair<int, int> solve() {
	sort(arr.begin(), arr.end());
	vector<int> pos, neg;
	neg.reserve(N + 1);
	pos.reserve(N + 1);
	for (const auto& i : arr) {
		if (i.second < 0)
			neg.push_back(i.first);
		else
			pos.push_back(i.first);
	}
	reverse(neg.begin(), neg.end());
	int kpos;
	bool isSametime = false;
	bool isAnsLater;
	for (int k = 0; k < K; k++) {
		if (!pos.empty() && !neg.empty()) {
			if (L - pos.back() <= neg.back()) {
				if (L - pos.back() == neg.back() && k >= K - 2) {
					isSametime = true;
					if (k == K - 2)
						isAnsLater = true;
					else
						isAnsLater = false;
				}
				kpos = pos.back();
				pos.pop_back();
			}
			else {
				kpos = -neg.back();
				neg.pop_back();
			}
		}
		else {
			if (pos.empty()) {
				kpos = -neg.back();
				neg.pop_back();
			}
			else {
				kpos = pos.back();
				pos.pop_back();
			}
		}
	}

	int time = kpos < 0 ? -kpos : L - kpos;
	return { abs(getId(kpos)), time };
}

int main() {
	int T = 1;
	for (int t = 0; t < T; t++) {
		arr.clear();
		scanf("%d %d", &N, &L);
		K = N;
		arr.assign(N, { 0, 0 });
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i].first);
			arr[i].second = i + 1;
			if (arr[i].first < 0) {
				arr[i].second *= -1;
				arr[i].first *= -1;
			}
		}
		auto ans = solve();
		printf("%d %d", ans.first, ans.second);
	}
	return 0;
}