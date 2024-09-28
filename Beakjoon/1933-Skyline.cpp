#include <bits/stdc++.h>
using namespace std;

typedef array<int, 3> Box;

int main() {
#ifdef TEST
	freopen("input.txt", "r", stdin);
#endif

	int N;
	vector<Box> arr;
	scanf("%d", &N);
	arr.reserve(N + 1);
	arr.push_back({ 0, 0, 1'000'000'001 });
	for (int i = 0; i < N; i++) {
		int l, h, r;
		scanf("%d %d %d", &l, &h, &r);
		arr.push_back({ l, h, r });
	}	
	sort(arr.begin(), arr.end());;

	int idx = 1;
	priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
	priority_queue<int> heights, deleted;
	heights.emplace(0);
	pq.push({ 1'000'000'001, 0 });
		
	while (idx <= N || pq.size() > 1) {
		int next_out = pq.top()[0];
		int next_in = (idx <= N ? arr[idx][0] : 1'000'000'002);
		int x = min(next_out, next_in);
		int height_now = heights.top();

		if (next_out <= next_in) {
			do {
				int height = heights.top();

				Box& target = arr[pq.top()[1]];
				pq.pop();
				if (target[1] == height) {
					heights.pop();
					while (deleted.size() && deleted.top() == heights.top()) {
						deleted.pop(); heights.pop();
					}
				}
				else {
					deleted.push(target[1]);
				}	
			} while (next_out == pq.top()[0]);
		}
		if (next_in <= next_out) {
			do {
				Box& target = arr[idx];
				pq.push({ target[2], idx });
				idx++;
				heights.push(target[1]);
			} while (next_in == (idx <= N ? arr[idx][0] : 1'000'000'002));
		}

		int height_new = heights.top();

		if (height_now != height_new) {
			printf("%d %d ", x, height_new);
		}
	}

	return 0;
}