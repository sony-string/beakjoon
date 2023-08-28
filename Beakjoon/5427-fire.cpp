#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

enum {
	emptySquare = '.', wall = '#', startPos = '@', fire = '*', outside = '^'
};

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int T;
int w, h, r, c;
bool isPossible;
char** map;
queue<ii> posVector;


void fireInit() {
	for (int i = 1; i <= h; i++) {
		for (int k = 1; k <= w; k++) {
			if (map[i][k] == fire) {
				posVector.emplace(i, k);
			}
		}
	}
}


void fireSpread() {
	int fireCount = posVector.size();
	ii pos;
	for (int k = 0; k < fireCount; k++) {
		pos = posVector.front();
		posVector.pop();
		for (int i = 0; i < 4; i++) {
			if (map[pos.first + dir[i][0]][pos.second + dir[i][1]] == emptySquare) {
				map[pos.first + dir[i][0]][pos.second + dir[i][1]] = fire;
				posVector.emplace(pos.first + dir[i][0], pos.second + dir[i][1]);
			}
		}
	}
}


int main() {
	//freopen("input.txt", "r", stdin);
	queue<ii> q;
	bool** visited;
	int answer;
	int qCount;
	ii pos;

	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d", &w, &h);
		map = new char* [h + 2];
		map[0] = new char[w + 3];
		map[h + 1] = new char[w + 3];
		memset(map[0], outside, sizeof(char) * (w + 3));
		memset(map[h + 1], outside, sizeof(char) * (w + 3));
		map[0][w + 2] = 0;
		map[h + 1][w + 2] = 0;

		visited = new bool* [h + 2];
		for (int i = 0; i < h + 2; i++) {
			visited[i] = new bool[w + 2];
			memset(visited[i], false, w + 2);
		}

		for (int i = 1; i < h + 1; i++) {
			map[i] = new char[w + 3];
			map[i][0] = outside;
			scanf("%s", &map[i][1]);
			map[i][w + 2] = '\0';
			map[i][w + 1] = outside;
		}

		for (int i = 1; i < h + 1; i++) {
			for (int k = 1; k < w + 1; k++) {
				if (map[i][k] == startPos) {
					q.emplace(i, k);
					visited[i][k] = true;
					map[i][k] = emptySquare;
					break;
				}
			}
			if (!q.empty()) {
				break;
			}
		}

		answer = 0;
		isPossible = false;
		fireInit();
		while (!isPossible && !q.empty()) {
			qCount = q.size();
			answer++;
			fireSpread();
			for (int i = 0; i < qCount; i++) {
				pos = q.front();
				q.pop();
				for (int k = 0; k < 4; k++) {
					if (!visited[pos.first + dir[k][0]][pos.second + dir[k][1]] &&
						map[pos.first + dir[k][0]][pos.second + dir[k][1]] == emptySquare) {
						visited[pos.first + dir[k][0]][pos.second + dir[k][1]] = true;
						q.emplace(pos.first + dir[k][0], pos.second + dir[k][1]);
					}
					if (map[pos.first + dir[k][0]][pos.second + dir[k][1]] == outside) {
						isPossible = true;
						break;
					}
				}
			}
		}

		if (isPossible) {
			printf("%d\n", answer);
		}
		else {
			printf("IMPOSSIBLE\n");
		}
		
		for (int i = 0; i < h + 2; i++) {
			delete[](map[i]);
			delete[](visited[i]);
		}
		delete[](map);
		delete[](visited);
		while (!q.empty()) {
			q.pop();
		}
		while (!posVector.empty()) {
			posVector.pop();
		}
	}

	return 0;
}
