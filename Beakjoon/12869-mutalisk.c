#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	int numSCV, damage;
	int hp[3] = { 0 , 0 , 0}, nextHp[3];
	int table[61][61][61];
	int tableSize = pow(61, 3);
	int** queue = (int**)malloc(tableSize * sizeof(int*));
	int l = 0, r = 0;
	memset(table, -1, sizeof(int[61][61][61]));
	scanf("%d", &numSCV);
	for (int i = 0; i < numSCV; i++) {
		scanf("%d", hp + i);
	}
	for (int i = 0; i < tableSize; i++) {
		queue[i] = (int*)malloc(3 * sizeof(int));
	}
	table[hp[0]][hp[1]][hp[2]] = 0;
	queue[r][0] = hp[0];
	queue[r][1] = hp[1];
	queue[r][2] = hp[2];
	table[hp[0]][hp[1]][hp[2]] = 0;
	r++;
	for (; l < r; l++) {
		hp[0] = queue[l][0];
		hp[1] = queue[l][1];
		hp[2] = queue[l][2];
		if (hp[0] == 0 && hp[1] == 0 && hp[2] == 0) {
			break;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j == i) {
					continue;
				}
				for (int k = 0; k < 3; k++) {
					if (k == j || k == i) {
						continue;
					}
					damage = 9;
					if (hp[i] != 0) {
						nextHp[i] = hp[i] - damage;
						if (nextHp[i] < 0) {
							nextHp[i] = 0;
						}
						damage /= 3;
					}
					else {
						nextHp[i] = 0;
					}
					if (hp[j] != 0) {
						nextHp[j] = hp[j] - damage;
						if (nextHp[j] < 0) {
							nextHp[j] = 0;
						}
						damage /= 3;
					}
					else {
						nextHp[j] = 0;
					}
					if (hp[k] != 0) {
						nextHp[k] = hp[k] - damage;
						if (nextHp[k] < 0) {
							nextHp[k] = 0;
						}
					}
					else {
						nextHp[k] = 0;
					}
					if (table[nextHp[0]][nextHp[1]][nextHp[2]] != -1) {
						if (table[nextHp[0]][nextHp[1]][nextHp[2]] <= table[hp[0]][hp[1]][hp[2]] + 1) {
							continue;
						}
					}
					queue[r][0] = nextHp[0];
					queue[r][1] = nextHp[1];
					queue[r][2] = nextHp[2];
					table[nextHp[0]][nextHp[1]][nextHp[2]] = table[hp[0]][hp[1]][hp[2]] + 1;
					r++;
				}
			}
		}
	}
	printf("%d", table[0][0][0]);
	return 0;
}