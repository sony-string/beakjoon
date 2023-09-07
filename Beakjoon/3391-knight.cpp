#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string.h>

int dir[8][2] = { {-2, 1}, {-2, -1}, {2, 1}, {2,  -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };

int ro, co;

int deploy(int** map) {
	int pieces = 0;
	int count;
	int best[2];
	int next[2];
	int bestcount;
	bool end = false;
	int r, c;

	while (!end) {
		best[0] = -1;
		best[1] = -1;
		bestcount = -1;
		for (r = 1; r <= ro; r++) {
			for (c = 1; c <= co; c++) {
				if (map[r][c] != 0) {
					continue;
				}
				count = 0;
				for (int i = 0; i < 8; i++) {
					next[0] = r + dir[i][0];
					next[1] = c + dir[i][1];
					if (next[0] > 0 && next[1] > 0 && next[1] <= co && next[0] <= ro) {
						if (map[next[0]][next[1]] == -1) {
							count++;
						}
						else if (map[next[0]][next[1]] == 1) {
							count = -1;
							break;
						}
					}
					else {
						count++;
					}
				}
				if (count > bestcount) {
					best[0] = r;
					best[1] = c;
					bestcount = count;
				}
			}
		}
		if (bestcount == -1) {
			end = true;
			break;
		}
		else {
			pieces++;
			map[best[0]][best[1]] = 1;
			for (int i = 0; i < 8; i++) {
				next[0] = best[0] + dir[i][0];
				next[1] = best[1] + dir[i][1];

				if (next[0] > 0 && next[1] > 0 && next[1] <= co && next[0] <= ro) {
					map[next[0]][next[1]] = -1;
				}
			}
		}
	}
	return pieces;
}


int main() {
	int** map;
	int N, M;
	int r, c;

	scanf("%d %d", &N, &M);
	ro = N; co = N;
	map = new int* [N + 1];
	for (int i = 0; i <= N; i++) {
		map[i] = new int[N + 1];
		memset(map[i], 0, (N + 1) * sizeof(int));
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &r, &c);
		map[r][c] = -1;
	}

	printf("%d", deploy(map));
	return 0;
}