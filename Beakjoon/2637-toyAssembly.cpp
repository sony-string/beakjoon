#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;

#define fore(a, b) for (int i = a; i < b; i++)

int* sum;
int* basic;
vector<pair<int, int>>* need;
vector<int>* basicneed;
int* visited;

void solve(int idx, int t) {
	visited[idx] = 1;
	int numneed;
	numneed = need[idx].size();
	fore(0, numneed) {
		if (basic[need[idx][i].first] == 1 && visited[need[idx][i].first] == 0) {
			solve(need[idx][i].first, t * need[idx][i].second);

			for (int j = 0; j < 100; j++) {
				basicneed[idx][j] += basicneed[need[idx][i].first][j] * need[idx][i].second;
			}
		}
		else if (basic[need[idx][i].first] == 0) {
			sum[need[idx][i].first] += t * need[idx][i].second;
			basicneed[idx][need[idx][i].first] += need[idx][i].second;
		}
		else {
			for (int j = 0; j < 100; j++) {
				sum[j] += t * basicneed[need[idx][i].first][j] * need[idx][i].second;
				basicneed[idx][j] += basicneed[need[idx][i].first][j] * need[idx][i].second;
			}
		}
	}
}

int main() {
	sum = new int[101];
	basic = new int[101];
	visited = new int[101];
	memset(basic, 0, sizeof(int) * 100);
	memset(sum, 0, sizeof(int) * 100);
	memset(visited, 0, sizeof(int) * 100);
	need = new vector<pair<int, int>>[101];
	basicneed = new vector<int>[101];
	for (int i = 0; i <= 100; i++) {
		basicneed[i].assign(101, 0);
	}

	int size, link;
	int x, y, z;
	scanf("%d", &size);
	scanf("%d", &link);

	fore(0, link) {
		scanf("%d %d %d", &x, &y, &z);
		basic[x] = 1;
		need[x].push_back(make_pair(y, z));
	}
	solve(size, 1);
	fore(1, size) {
		if (basic[i] == 0) {
			printf("%d %d\n", i, sum[i]);
		}
	}
	return 0;
}