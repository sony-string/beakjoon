#include <cstdio>
#include <queue>
using namespace std;

template <typename T, typename _Container = vector<T>, typename _Comp = less<T>>
class P : public priority_queue<T, _Container, _Comp> {
public:
	int& operator[](unsigned int i) {
		return c[i];
	}
};

int main() {
	P<int, vector<int>, greater<int>> pq;
	int N;
	int ans = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		pq.push(n);
	}
	while (pq.size() > 2) {		
		int n;
		ans += n = pq[0] + min(pq[1], pq[2]);
		pq.pop(); pq.pop();
		pq.push(n);
	}
	if (N > 1) ans += pq[0] + pq[1];
	printf("%d", ans);
	return 0;
}