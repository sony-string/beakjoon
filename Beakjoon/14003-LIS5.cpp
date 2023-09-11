#include <bits/stdc++.h>
using namespace std;
void solve(vector<int> trace, const vector<int>& arr) {
	int index;
	pair<int, int> answer(0, 0);
	vector<int> stack;
	vector<int> indexStack;
	for (int i = 0; i < arr.size(); i++) {
		if (stack.empty() || stack.back() < arr[i]) {
			stack.emplace_back(arr[i]);
			indexStack.emplace_back(i);
			if (answer.first < (int)stack.size())
				answer = make_pair(stack.size(), i);
			index = stack.size() - 1;
		}
		else {
			index = lower_bound(stack.begin(), stack.end(), arr[i]) - stack.begin();
			stack[index] = arr[i];
			indexStack[index] = i;
		}
		trace[i] = index == 0 ? -1 : indexStack[index - 1];
	}

	printf("%d\n", answer.first);
	stack.clear();
	for (int i = answer.second; i != -1; i = trace[i])
		stack.emplace_back(arr[i]);
	while (!stack.empty()) {
		printf("%d ", stack.back());
		stack.pop_back();
	}
}

int main() {
	int N;
	vector<int> arr;
	vector<int> trace;
	scanf("%d", &N);
	arr.assign(N, 0);
	trace.assign(N, -1);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	solve(trace, arr);
	return 0;
}