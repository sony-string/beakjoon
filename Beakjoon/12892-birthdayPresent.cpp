#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<pair<int, int>> vii;
typedef pair<int, int> ii;
typedef long long ll;


bool comp(const ii& lhs, const ii& rhs) {
	return lhs.first < rhs.first;
}


int main() {
	vii presentArr;
	int N, D, P, V;
	ll sumScore = 0;
	ll bestScore = 0;
	int l = 0, r = 0;
	int diff;
	ii* sortedPresentArr;
	scanf("%d %d", &N, &D);
	presentArr.reserve(N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &P, &V);
		presentArr.push_back(make_pair(P, V));
	}

	sort(presentArr.begin(), presentArr.end(), &comp);
	sortedPresentArr = presentArr.data();
	diff = 0;
	sumScore = sortedPresentArr[0].second;
	for (r = 1; r < N; r++) {
		diff = sortedPresentArr[r].first - sortedPresentArr[l].first;
		if (diff >= D) {
			bestScore = max(bestScore, sumScore);
			while (diff >= D) {
				sumScore -= sortedPresentArr[l].second;
				l++;
				diff = sortedPresentArr[r].first - sortedPresentArr[l].first;
			}
		}
		sumScore += sortedPresentArr[r].second;
	}
	bestScore = max(bestScore, sumScore);

	printf("%lld", bestScore);

	return 0;
}