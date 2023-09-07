#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//선분교차로 다시 풀어보자

enum {
	t, f, end
};

enum {
	position = 0, speed = 1
};

int travel(char** map, int pos[], int vec[], int size[]) {
	if (vec[0] == 0 && vec[1] == 0) {
		return t;
	}
	double now[2] = { pos[0] + 0.5, pos[1] + 0.5 };
	int nowPos[2];
	int nextPos[2];
	char road;
	int dst[2] = { pos[0] + vec[0], pos[1] + vec[1] };
	double spd[2];
	int intvec[2];

	if (abs(vec[0]) > abs(vec[1])) {
		if (vec[0] > 0) {
			spd[0] = 1;
			spd[1] = (double)vec[1] / vec[0];
		}
		else {
			spd[0] = -1;
			spd[1] = (double)vec[1] / vec[0];
			spd[1] *= -1;
		}
	}
	else if (vec[1] != 0){
		if (vec[1] > 0) {
			spd[1] = 1;
			spd[0] = (double)vec[1] / vec[0];
		}
		else {
			spd[1] = -1;
			spd[1] = (double)vec[0] / vec[1];
			spd[0] *= -1;
		}
	}

	if (vec[0] == 0 || vec[1] == 0) {
		nowPos[0] = pos[0];
		nowPos[1] = pos[1];
		if (vec[0] == 0) {
			if (vec[1] > 0) {
				spd[1] = 1;
			}
			else {
				spd[1] = -1;
			}
			while (nowPos[1] != dst[1]) {
				nowPos[1] += spd[1];
				if (nowPos[1] >= size[1] || nowPos[1] < 0) {
					return f;
				}
				road = map[nowPos[0]][nowPos[1]];
				if (road == 'F') {
					return end;
				}
				else if (road == 'X') {
					return f;
				}
			}
			return t;
		}
		else {
			if (vec[0] > 0) {
				spd[0] = 1;
			}
			else {
				spd[0] = -1;
			}
			while (nowPos[0] != dst[0]) {
				nowPos[0] += spd[0];
				if (nowPos[0] >= size[0] || nowPos[0] < 0) {
					return f;
				}
				road = map[nowPos[0]][nowPos[1]];
				if (road == 'F') {
					return end;
				}
				else if (road == 'X') {
					return f;
				}
			}
			return t;
		}
	}
	else if (vec[0] % vec[1] != 0 && vec[1] % vec[0] != 0) {
		if (spd[0] == 1) {
			now[0] += 0.5;
			now[1] += spd[1] / 2;
		}
		else {
			now[1] += 0.5;
			now[0] += spd[0] / 2;
		}
		while ((int)floor(now[0]) != dst[0] || (int)floor(now[1]) != dst[1]) {
			nowPos[0] = (int)floor(now[0]);
			nowPos[1] = (int)floor(now[1]);
			if (nowPos[0] >= size[0] || nowPos[1] >= size[1] || nowPos[0] < 0 || nowPos[1] < 0) {
				return f;
			}
			road = map[nowPos[0]][nowPos[1]];
			if (road == 'F') {
				return end;
			}
			else if (road == 'X') {
				return f;
			}
			now[0] += spd[0];
			now[1] += spd[1];
		}
		road = map[dst[0]][dst[1]];
		if (road == 'F') {
			return end;
		}
		else if (road == 'X') {
			return f;
		}
		return t;
	}
	else {
		if (abs(vec[0]) >= abs(vec[1])) {
			intvec[1] = 1;
			intvec[0] = vec[0] / vec[1];
			if (intvec[1] < 0) {
				intvec[1] *= -1;
				intvec[0] *= -1;
			}
		}
		else {
			intvec[0] = 1;
			intvec[1] = vec[1] / vec[0];
			if (intvec[0] < 0) {
				intvec[0] *= -1;
				intvec[1] *= -1;
			}
		}
		nowPos[0] = pos[0];
		nowPos[1] = pos[1];
		nextPos[0] = pos[0];
		nextPos[1] = pos[1];
		while (nowPos[0] != dst[0] || nowPos[1] != dst[1]) {
			nextPos[0] += intvec[0];
			nextPos[1] += intvec[1];
			if (intvec[0] == 1) {
				if (nextPos[1] > nowPos[1]) {
					for (int i = nowPos[1]; i < nextPos[1]; i++) {
						if (i >= size[1]) {
							return f;
						}
						road = map[nowPos[0]][i];
						if (road == 'F') {
							return end;
						}
						else if (road == 'X') {
							return f;
						}
					}
				}
				else {
					for (int i = nowPos[1]; i > nextPos[1]; i--) {
						if (i < 0)
							road = map[nowPos[0]][i];
						if (road == 'F') {
							return end;
						}
						else if (road == 'X') {
							return f;
						}
					}
				}
				if (nextPos[1] >= size[1] || nextPos[1] < 0 || nextPos[0] >= size[0] || nextPos[0] < 0) {
					return f;
				}
				road = map[nextPos[0]][nextPos[1]];
				if (road == 'F') {
					return end;
				}
				else if (road == 'X') {
					return f;
				}
				nowPos[0] = nextPos[0];
				nowPos[1] = nextPos[1];
			}
			else {
				if (nextPos[0] > nowPos[0]) {
					for (int i = nowPos[0]; i < nextPos[0]; i++) {
						if (i >= size[0]) {
							return f;
						}
						road = map[i][nowPos[1]];
						if (road == 'F') {
							return end;
						}
						else if (road == 'X') {
							return f;
						}
					}
				}
				else {
					for (int i = nowPos[0]; i > nextPos[0]; i--) {
						if (i < 0) {
							return f;
						}
						road = map[i][nowPos[1]];
						if (road == 'F') {
							return end;
						}
						else if (road == 'X') {
							return f;
						}
					}
				}
				if (nextPos[1] >= size[1] || nextPos[1] < 0 || nextPos[0] >= size[0] || nextPos[0] < 0) {
					return f;
				}
				road = map[nextPos[0]][nextPos[1]];
				if (road == 'F') {
					return end;
				}
				else if (road == 'X') {
					return f;
				}
				nowPos[0] = nextPos[0];
				nowPos[1] = nextPos[1];
			}
		}
		return t;
	}
}


int main() {
	int*** queue;
	int l, r, endPop, count = 0;
	l = 0; r = 0;

	char** map;
	int size[2];
	int pos[2];
	int spd[2];
	int vec[2];
	int delta[9][2] = { {1,1}, {1,0}, {1,-1}, {0, 1}, {0, 0}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} };
	int result;

	scanf("%d %d", size, size + 1);
	map = (char**)malloc(size[0] * sizeof(char*));
	for (int i = 0; i < size[0]; i++) {
		map[i] = (char*)malloc(size[1] + 1);
		scanf("%s", map[i]);
		for (int k = 0; k < size[1]; k++) {
			if (map[i][k] == 'S') {
				pos[0] = i;
				pos[1] = k;
			}
		}
	}
	scanf("%d %d", spd, spd + 1);
	queue = (int***)calloc(100000, sizeof(int**));
	for (int i = 0; i < 100000; i++) {
		queue[i] = (int**)calloc(2, sizeof(int*));
		queue[i][position] = (int*)calloc(2, sizeof(int));
		queue[i][speed] = (int*)calloc(2, sizeof(int));
	}
	queue[0][position][0] = pos[0];
	queue[0][position][1] = pos[1];
	queue[0][speed][0] = spd[0];
	queue[0][speed][1] = spd[1];
	r++;

	int i;
	while (l < r) {
		endPop = r;
		count++;
		for (; l < endPop; l++) {
			pos[0] = queue[0][position][0];
			pos[1] = queue[0][position][1];
			spd[0] = queue[0][speed][0];
			spd[1] = queue[0][speed][1];
			for (i = 0; i < 9; i++) {
				vec[0] = spd[0] + delta[i][0];
				vec[1] = spd[1] + delta[i][1];
				result = travel(map, pos, vec, size);
				if (result == end) {
					break;
				}
				else if (result == t) {
					queue[r][position][0] = pos[0] + vec[0];
					queue[r][position][1] = pos[1] + vec[1];
					queue[r][speed][0] = vec[0];
					queue[r][speed][1] = vec[1];
					r++;
					continue;
				}
			}
			if (i < 9) {
				break;
			}
		}
		if (endPop < 9) {
			break;
		}
	}
	if (result == end) {
		printf("%d", count);
	}
	else {
		printf("-1");
	}
	return 0;
}