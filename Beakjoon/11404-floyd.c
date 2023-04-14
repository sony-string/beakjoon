#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int main() {
	int numLoads, numVertices, src, dst, cost;
	int** distArr = NULL;
	int i, k;
	int s, e, m;
		scanf("%d %d", &numVertices, &numLoads);
		distArr = (int**)malloc(numVertices * sizeof(int*));
		for (i = 0; i < numVertices; i++) {
			distArr[i] = (int*)malloc(numVertices * sizeof(int));
			for (k = 0; k < numVertices; k++) {
				distArr[i][k] = INT_MAX;
			}
			distArr[i][i] = 0;
		}
		for (i = 0; i < numLoads; i++) {
			scanf("%d %d %d", &src, &dst, &cost);
			src--; dst--;
			if (distArr[src][dst] > cost) {
				distArr[src][dst] = cost;
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
			if (s > 1) {
				printf("\n");
			}
			for (e = 0; e < numVertices; e++) {
				if (distArr[s][e] == INT_MAX) {
					printf("0 ");
					continue;
				}
				printf("%d ", distArr[s][e]);
			}
		}


		for (s = 0; s < numVertices; s++) {
			free(distArr[s]);
		}
		free(distArr);

	return 0;
}