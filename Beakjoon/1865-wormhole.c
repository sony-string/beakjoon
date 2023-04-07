#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int main() {
	int numLoads, numWormholes, numVertices, src, dst, time;
	int numTestCases;
	int** distArr = NULL;

	scanf("%d", &numTestCases);
	int T, i, k;
	int s, e, m;
	for (T = 0; T < numTestCases; T++) {


		scanf("%d %d %d", &numVertices, &numLoads, &numWormholes);
		distArr = (int**)malloc(numVertices * sizeof(int*));
		for (i = 0; i < numVertices; i++) {
			distArr[i] = (int*)malloc(numVertices * sizeof(int));
			for (k = 0; k < numVertices; k++) {
				distArr[i][k] = INT_MAX;
			}
			distArr[i][i] = 0;
		}
		for (i = 0; i < numLoads; i++) {
			scanf("%d %d %d", &src, &dst, &time);
			src--; dst--;
			if (distArr[src][dst] > time) {
				distArr[src][dst] = time;
				distArr[dst][src] = time;
			}
		}
		for (i = 0; i < numWormholes; i++) {
			scanf("%d %d %d", &src, &dst, &time);
			src--; dst--;
			if (distArr[src][dst] > -1 * time) {
				distArr[src][dst] = -1 * time;
			}
		}
		for (m = 0; m < numVertices; m++) {
			for (s = 0; s < numVertices; s++) {
				for (e = 0; e < numVertices; e++) {
					if (distArr[s][m] != INT_MAX && distArr[m][e] != INT_MAX) {
						if (distArr[s][m] + distArr[m][e] < distArr[s][e]) {
							distArr[s][e] = distArr[s][m] + distArr[m][e];
						}
					}
				}
			}
		}
		for (s = 0; s < numVertices; s++) {
			if (distArr[s][s] < 0) {
				break;
			}
		}
		if (s != numVertices) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
		for (s = 0; s < numVertices; s++) {
			free(distArr[s]);
		}
		free(distArr);


	}
	return 0;
}