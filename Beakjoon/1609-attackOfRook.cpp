#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;


int main() {
	int N;
	int** map;
	int* rowSum;
	int* colSum;
	int sum = 0, best = 0;

	scanf("%d", &N);
	map = new int* [N];
	rowSum = new int[N];
	colSum = new int[N];
	for (int i = 0; i < N; i++) {
		map[i] = new int[N];
		sum = 0;
		for (int k = 0; k < N; k++) {
			scanf("%d", &map[i][k]);
			sum += map[i][k];
		}
		rowSum[i] = sum;
	}

	for (int k = 0; k < N; k++) {
		sum = 0;
		for (int i = 0; i < N; i++) {
			sum += map[i][k];
		}
		colSum[k] = sum;
	}
	int count = 0;
	for (int r = N - 1; r > 0; r--) {
		for (int c = 0; c < N - 1; c++) {
			for (int rr = r - 1; rr >= 0; rr--) {
				for (int cc = c + 1; cc < N; cc++) {
					count++;
					sum = rowSum[r] + rowSum[rr] + colSum[c] + colSum[cc];
					sum -= map[r][c] + map[rr][c] + map[r][cc] + map[rr][cc];
					sum -= min(map[r][c] + map[rr][cc], map[rr][c] + map[r][cc]);
					best = max(sum, best);
				}
			}
		}
	}

	printf("%d", best);
	return 0;
}