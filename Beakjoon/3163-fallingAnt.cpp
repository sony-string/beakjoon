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

int solve() {
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

	if (isSametime) {
		int a = getId(kpos);
		int b;
		if (kpos < 0)
			b = getId(L + kpos);
		else
			b = getId(-L + kpos);
		return isAnsLater ? max(a, b) : min(a, b);
	}
	else {
		return getId(kpos);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		arr.clear();
		scanf("%d %d %d", &N, &L, &K);
		arr.assign(N, { 0, 0 });
		for (int i = 0; i < N; i++)
			scanf("%d %d", &arr[i].first, &arr[i].second);
		printf("%d\n", solve());
	}
	return 0;
}