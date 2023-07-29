#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#define MAX_DEPTH 10

enum {
	up = 0, left = 1, down = 2, right = 3
};

enum {
	noChange, noMixed, mixed
};


typedef vector<int> vi;

int N;
int maxScore = 0;
unsigned long long _count = 0;


int moveMap(int** map, vi& elementsCount, int dir) {
	_count++;
	int posDiff, start, end;
	int top = -1;
	bool isMixAvaliable = true;
	bool isBlankExist = false;
	int returnFlag = noChange;
	if (dir == up || dir == down) {
		if (dir == up) {
			start = 0;
			end = N;
			posDiff = 1;
		}
		else {
			start = N - 1;
			end = -1;
			posDiff = -1;
		}

		for (int i = 0; i < N; i++) {
			isMixAvaliable = true;
			top = start - posDiff;
			for (int k = start; k != end; k += posDiff) {
				while (map[k][i] == 0) {
					k += posDiff;
					if (k == end) {
						break;
					}
				}
				if (k == end) {
					break;
				}
				else if ((k - posDiff < N && k - posDiff >= 0)) {
					if (map[k - posDiff][i] == 0) {
						isBlankExist = true;
					}
				}

				if (top != start - posDiff) {
					if (map[top][i] == map[k][i] && isMixAvaliable) {
						elementsCount[map[top][i]] -= 2;
						elementsCount[map[top][i] + 1] += 1;
						map[top][i] += 1;
						returnFlag = mixed;
						isMixAvaliable = false;
					}
					else {
						top += posDiff;
						map[top][i] = map[k][i];
						isMixAvaliable = true;
					}
				}
				else {
					top += posDiff;
					map[top][i] = map[k][i];
					isMixAvaliable = true;
				}
				if (top != k) {
					map[k][i] = 0;
				}
			}
		}
	}

	if (dir == left || dir == right) {
		if (dir == left) {
			start = 0;
			end = N;
			posDiff = 1;
		}
		else {
			start = N - 1;
			end = -1;
			posDiff = -1;
		}

		for (int i = 0; i < N; i++) {
			isMixAvaliable = true;
			top = start - posDiff;
			for (int k = start; k != end; k += posDiff) {
				while (map[i][k] == 0) {
					k += posDiff;
					if (k == end) {
						break;
					}
				}
				if (k == end) {
					break;
				}
				else if ((k - posDiff < N && k - posDiff >= 0)) {
					if (map[i][k - posDiff] == 0) {
						isBlankExist = true;
					}
				}

				if (top != start - posDiff) {
					if (map[i][top] == map[i][k] && isMixAvaliable) {
						elementsCount[map[i][top]] -= 2;
						elementsCount[map[i][top] + 1] += 1;
						map[i][top] += 1;
						returnFlag = mixed;
						isMixAvaliable = false;
					}
					else {
						top += posDiff;
						map[i][top] = map[i][k];
						isMixAvaliable = true;
					}
				}
				else {
					top += posDiff;
					map[i][top] = map[i][k];
					isMixAvaliable = true;
				}

				if (top != k) {
					map[i][k] = 0;
				}
			}
		}
	}

	if (returnFlag != mixed && isBlankExist) {
		returnFlag = noMixed;
	}

	return returnFlag;
}


int solve(int** map, vi elementCount, bool isnoMixed, int dir, int depth = 1) {
	int returnFlag, maxCount, score;
	bool isAbleMix = false;
	int** newMap = new int* [N];
	for (int i = 0; i < N; i++) {
		newMap[i] = new int[N];
		memcpy(newMap[i], map[i], sizeof(int) * N);
	}

	returnFlag = moveMap(newMap, elementCount, dir);

	maxCount = 0;
	score = 0;
	for (int i = 18; i >= 0; i--) {
		if (elementCount[i] != 0) {
			score = i;
			maxScore = max(score, maxScore);
			break;
		}
	}

	if (!(returnFlag == noChange || depth == MAX_DEPTH || maxScore >= score + MAX_DEPTH - depth))  {
		for (int i = 0; i <= score; i++) {
			maxCount = (elementCount[i] + maxCount) / 2;
		}
		if (maxCount != 0) {
			for (int i = 0; i < 4; i++) {
				if (isnoMixed && (i + 2) % 4 == dir) {
					continue;
				}
				score = max(solve(newMap, elementCount, returnFlag == noMixed, i, depth + 1), score);
				maxScore = max(score, maxScore);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		delete[](newMap[i]);
	}
	delete[](newMap);

	return score;
}


int main() {
	vi elementsCount;
	int** map;
	
	elementsCount.assign(20, 0);

	scanf("%d", &N);
	map = new int* [N];
	for (int i = 0; i < N; i++) {
		map[i] = new int[N];
		for (int k = 0; k < N; k++) {
			scanf("%d", &map[i][k]);
			if (map[i][k] != 0) {
				map[i][k] = (int)log2(map[i][k]);
				elementsCount[map[i][k]] += 1;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		solve(map, elementsCount, false, i);
	}

	printf("%d", (int)pow(2, maxScore));

	return 0;
}