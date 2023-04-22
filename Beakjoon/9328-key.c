#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	lockedDoor, empty, obj, wall, findKey
};

int checkBlock (char keys[26], const char** map, int row, int col) {
	if (map[row][col] != '*') {
		if (map[row][col] == '.') {
			return empty;
		}
		if (map[row][col] == '$') {
			return obj;
		}
		if (map[row][col] >= 97) {
			keys[map[row][col] - 'a'] = 1;
			return findKey;
		}
		if (keys[map[row][col] - 'A'] == 1) {
			return empty;
		}
		return lockedDoor;
	}
	return wall;
}

int main() {
	char** map;
	char* keyString, key, iskeyFound;
	char keys[26];
	int** visited, ** queue, ** lockedDoors;
	int flag, result;
	int h, w, l, r, numLockedDoors, temp;
	int numTestcases;
	int row, col;

	int i, k, T;
	scanf("%d", &numTestcases);
	for (T = 0; T < numTestcases; T++) {
		scanf("%d %d", &h, &w);
		//문제 초기화
		map = (char**)calloc(h + 2, sizeof(char*));
		visited = (int**)calloc(h + 2, sizeof(int*));
		queue = (int**)calloc(h * w, sizeof(int*));
		lockedDoors = (int**)calloc(h * w, sizeof(int*));
		memset(keys, 0, 26 * sizeof(char));
		result = 0; flag = 0;
		l = 0; r = 0;
		numLockedDoors = 0; iskeyFound = 0;
		//맵 입력받기, visited 동적할당
		for (i = 0; i < h + 2; i++) {
			map[i] = (char*)calloc(w + 2, sizeof(char));
			visited[i] = (int*)calloc(w + 2, sizeof(int));
			memset(map[i], '*', (w + 2));
			if (i == 0 || i == h + 1) {
				continue;
			}
			scanf("%s", &map[i][1]);
			map[i][w + 1] = '*';
		}
		//queue, lockedDoors 동적할당
		for (i = 0; i < h * w; i++) {
			queue[i] = (int*)calloc(2, sizeof(int));
			lockedDoors[i] = (int*)calloc(2, sizeof(int));
		}

		//가진 키 입력받기
		keyString = (char*)calloc(27, sizeof(char));
		scanf("%s", keyString);
		k = strlen(keyString);
		for (i = 0; i < k; i++) {
			key = keyString[i];
			if (key == '0') {
				break;
			}
			keys[key - 'a'] = 1;
		}
		free(keyString);
		//가장자리 입구 찾기
		for (i = 1; i < w + 1; i++) {
			if (visited[1][i] == 0) {
				visited[1][i] = 1;
				flag = checkBlock(keys, map, 1, i);
				if (flag == lockedDoor) {
					lockedDoors[numLockedDoors][0] = 1;
					lockedDoors[numLockedDoors][1] = i;
					numLockedDoors++;
				}
				else if (flag != wall) {
					queue[r][0] = 1;
					queue[r][1] = i;
					r++;
					if (flag == obj) {
						result++;
					}
					if (flag == findKey) {
						iskeyFound = 1;
					}
				}
			}
			if (visited[h][i] == 0) {
				visited[h][i] = 1;
				flag = checkBlock(keys, map, h, i);
				if (flag == lockedDoor) {
					lockedDoors[numLockedDoors][0] = h;
					lockedDoors[numLockedDoors][1] = i;
					numLockedDoors++;
				}
				else if (flag != wall) {
					queue[r][0] = h;
					queue[r][1] = i;
					r++;
					if (flag == obj) {
						result++;
					}
					if (flag == findKey) {
						iskeyFound = 1;
					}
				}
			}
		}
		for (i = 2; i < h; i++) {
			if (visited[i][1] == 0) {
				visited[i][1] = 1;
				flag = checkBlock(keys, map, i, 1);
				if (flag == lockedDoor) {
					lockedDoors[numLockedDoors][0] = i;
					lockedDoors[numLockedDoors][1] = 1;
					numLockedDoors++;
				}
				else if (flag != wall) {
					queue[r][0] = i;
					queue[r][1] = 1;
					r++;
					if (flag == obj) {
						result++;
					}
					if (flag == findKey) {
						iskeyFound = 1;
					}
				}
			}
			if (visited[i][w] == 0) {
				visited[i][w] = 1;
				flag = checkBlock(keys, map, i, w);
				if (flag == lockedDoor) {
					lockedDoors[numLockedDoors][0] = i;
					lockedDoors[numLockedDoors][1] = w;
					numLockedDoors++;
				}
				else if (flag != wall) {
					queue[r][0] = i;
					queue[r][1] = w;
					r++;
					if (flag == obj) {
						result++;
					}
					if (flag == findKey) {
						iskeyFound = 1;
					}
				}
			}
		}
		while (1) {
			while (l != r) {
				row = queue[l][0]; col = queue[l][1];
				l++;
				if (visited[row + 1][col] == 0) {
					visited[row + 1][col] = 1;
					flag = checkBlock(keys, map, row + 1, col);
					if (flag == lockedDoor) {
						lockedDoors[numLockedDoors][0] = row + 1;
						lockedDoors[numLockedDoors][1] = col;
						numLockedDoors++;
					}
					else if (flag != wall) {
						queue[r][0] = row + 1;
						queue[r][1] = col;
						r++;
						if (flag == obj) {
							result++;
						}
						if (flag == findKey) {
							iskeyFound = 1;
						}
					}
				}
				if (visited[row - 1][col] == 0) {
					visited[row - 1][col] = 1;
					flag = checkBlock(keys, map, row - 1, col);
					if (flag == lockedDoor) {
						lockedDoors[numLockedDoors][0] = row - 1;
						lockedDoors[numLockedDoors][1] = col;
						numLockedDoors++;
					}
					else if (flag != wall) {
						queue[r][0] = row - 1;
						queue[r][1] = col;
						r++;
						if (flag == obj) {
							result++;
						}
						if (flag == findKey) {
							iskeyFound = 1;
						}
					}
				}
				if (visited[row][col + 1] == 0) {
					visited[row][col + 1] = 1;
					flag = checkBlock(keys, map, row, col + 1);
					if (flag == lockedDoor) {
						lockedDoors[numLockedDoors][0] = row;
						lockedDoors[numLockedDoors][1] = col + 1;
						numLockedDoors++;
					}
					else if (flag != wall) {
						queue[r][0] = row;
						queue[r][1] = col + 1;
						r++;
						if (flag == obj) {
							result++;
						}
						if (flag == findKey) {
							iskeyFound = 1;
						}
					}
				}
				if (visited[row][col - 1] == 0) {
					visited[row][col - 1] = 1;
					flag = checkBlock(keys, map, row, col - 1);
					if (flag == lockedDoor) {
						lockedDoors[numLockedDoors][0] = row;
						lockedDoors[numLockedDoors][1] = col - 1;
						numLockedDoors++;
					}
					else if (flag != wall) {
						queue[r][0] = row;
						queue[r][1] = col - 1;
						r++;
						if (flag == obj) {
							result++;
						}
						if (flag == findKey) {
							iskeyFound = 1;
						}
					}
				}
			}
			if (iskeyFound == 0) {
				break;
			}
			else {
				temp = numLockedDoors;
				numLockedDoors = 0;
				for (i = 0; i < temp; i++) {
					row = lockedDoors[i][0];
					col = lockedDoors[i][1];
					if (keys[map[row][col] - 'A'] == 1) {
						queue[r][0] = row;
						queue[r][1] = col;
						r++;
					}
					else {
						lockedDoors[numLockedDoors][0] = row;
						lockedDoors[numLockedDoors][1] = col;
						numLockedDoors++;
					}
				}
			}
			iskeyFound = 0;
		}
		printf("%d\n", result);
		//queue, lockedDoors, visited, map 할당 해제
		for (i = 0; i <= h + 1; i++) {
			free(map[i]);
			free(visited[i]);
		}
		for (i = 0; i < h * w; i++) {
			free(queue[i]);
			free(lockedDoors[i]);
		}
		free(map);
		free(visited);
		free(queue);
		free(lockedDoors);
	}
	return 0;
}