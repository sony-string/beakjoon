#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size[2] = { -1, -1 };

int solve(char** map, char route[26], int pos[2]) {
	int count = 1, best = 1;
	char newRoute[26];
	int newPos[2] = { pos[0], pos[1] };
	memcpy(newRoute, route, 26);
	newRoute[map[pos[0]][pos[1]] - 'A'] = 1;

	if (pos[0] > 0) {
		newPos[0] = pos[0] - 1;
		if (newRoute[map[newPos[0]][newPos[1]] - 'A'] == 0) {
			count = solve(map, newRoute, newPos) + 1;
			if (count > best) {
				best = count;
			}
		}
	}

	if (pos[0] < size[0] - 1) {
		newPos[0] = pos[0] + 1;
		if (newRoute[map[newPos[0]][newPos[1]] - 'A'] == 0) {
			count = solve(map, newRoute, newPos) + 1;
			if (count > best) {
				best = count;
			}
		}
	}
	newPos[0] = pos[0];
	if (pos[1] > 0) {
		newPos[1] = pos[1] - 1;
		if (newRoute[map[newPos[0]][newPos[1]] - 'A'] == 0) {
			count = solve(map, newRoute, newPos) + 1;
			if (count > best) {
				best = count;
			}
		}
	}
	if (pos[1] < size[1] - 1) {
		newPos[1] = pos[1] + 1;
		if (newRoute[map[newPos[0]][newPos[1]] - 'A'] == 0) {
			count = solve(map, newRoute, newPos) + 1;
			if (count > best) {
				best = count;
			}
		}
	}
	return best;
}


int main() {
	char** map, route[26];
	int result, pos[2] = { 0, 0 };
	memset(route, 0, 26);

	scanf("%d %d", size, size + 1);
	map = (char**)malloc(size[0] * sizeof(char*));
	for (int i = 0; i < size[0]; i++) {
		map[i] = (char*)malloc(size[1] + 1);
		scanf("%s", map[i]);
	}

	result = solve(map, route, pos);
	printf("%d", result);
	return 0;
}