#include <bits/stdc++.h>
using namespace std;

int solve(const vector<int>& arr) {
	int answer = 0;
	vector<int> stack;
	for (const auto& i : arr) {
		if (stack.empty() || stack.back() < i) {
			stack.emplace_back(i);
			answer = max(answer, (int)stack.size());
		}
		else {
			*lower_bound(stack.begin(), stack.end(), i) = i;
		}
	}
	return answer;
}

int main() {
	int N;
	vector<int> arr;
	scanf("%d", &N);
	arr.assign(N, 0);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", solve(arr));
	return 0;
}