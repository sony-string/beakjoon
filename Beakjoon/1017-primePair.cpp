#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int matched[50];
bool adj[50][50];
bool chk[50];
int N, rsize;

bool dfs(int v) {
	int match = -1;
	chk[v] = true;
	for (int i = 0; i < rsize; i++) {
		if (!adj[v][i] || matched[i] == 0) continue;
		if (matched[i] != -1) {
			if (!chk[matched[i]] && dfs(matched[i])) {
				match = i;
				break;
			}
		}
		else {
			match = i;
			break;
		}
	}
	if (match == -1) return false;
	matched[match] = v;
	return true;
}

bool isprime(int n) {
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

int main() {
	vi odds, evens;
	vi* firstarrp = &odds, * secondarrp = &evens;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		if (n % 2) odds.push_back(n);
		else evens.push_back(n);
		if (i == 0) {
			if (n % 2 == 0) {
				firstarrp = &evens;
				secondarrp = &odds;
			}
		}
	}
	if (odds.size() != evens.size()) {
		printf("-1");
		return 0;
	}
	vi& firstarr = *firstarrp;
	vi& secondarr = *secondarrp;
	for (int i = 0; i < firstarr.size(); i++) {
		for (int j = 0; j < secondarr.size(); j++) {
			if (isprime(firstarr[i] + secondarr[j])) {
				adj[i][j] = true;
			}
		}
	}
	vi ans;
	rsize = secondarr.size();
	for (int i = 0; i < secondarr.size(); i++) {
		if (!adj[0][i]) continue;
		fill(matched, matched + N, -1);		
		matched[i] = 0;
		bool success = true;
		for (int j = 1; j < firstarr.size(); j++) {
			fill(chk, chk + 50, false);
			chk[0] = true;
			if (!dfs(j)) {
				success = false;
				break;
			}
		}
		if (success) {
			ans.push_back(secondarr[i]);
		}
	}
	if (ans.empty()) {
		printf("-1");
	}
	else {
		sort(ans.begin(), ans.end());
		for (auto& i : ans) {
			printf("%d ", i);
		}
	}
	return 0;
}