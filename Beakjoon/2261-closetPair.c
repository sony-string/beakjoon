#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	long long** pos;
	long long dist, lower, * distArr, cos;
	int src, dst, cur;
	int numPoint;
	scanf("%d", &numPoint);
	pos = (long long**)malloc(numPoint * sizeof(long long*));
	distArr = (long long*)malloc(numPoint * sizeof(long long));
	for (int i = 0; i < numPoint; i++) {
		pos[i] = (long long*)malloc(2 * sizeof(long long));
		scanf("%lld %lld", pos[i], pos[i] + 1);
	}
	cur = 0;
	while (1) {
		lower = 1000000000;
		for (int i = 0; i < numPoint; i++) {
			if (i == cur) {
				continue;
			}
			dist = (long long)pow(abs(pos[i][0] - pos[cur][0]), 2) + (long long)pow(abs(pos[i][1] - pos[cur][1]), 2);
			distArr[i] = dist;
			if (dist < lower) {
				lower = dist;
				src = i;
			}
		}
		for (dst = 0; dst < numPoint; dst++) {
			if (dst == cur || dst == src) {
				continue;
			}
			cos = (pos[src][0] - pos[cur][0]) * (pos[dst][0] - pos[cur][0]) + (pos[src][1] - pos[cur][1]) * (pos[dst][1] - pos[cur][1]);
			if (distArr[dst] - 2 * cos < 0) {
				cur = dst;
				break;
			}
		}
		if (dst == numPoint) {
			break;
		}
	}
	printf("%lld", lower);
	return 0;
}