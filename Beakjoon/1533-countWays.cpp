#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#define DOMINATOR 1000003


typedef long long li;


li** multiplyMatrix(li** lmatrix, li** rmatrix, int N) {
	li sum = 0;
	li** newMatrix = new li * [N];
	for (int i = 0; i < N; i++) {
		newMatrix[i] = new li[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum = 0;
			for (int k = 0; k < N; k++) {
				sum += lmatrix[i][k] * rmatrix[k][j];
			}
			sum %= DOMINATOR;
			newMatrix[i][j] = sum;
		}
	}

	return newMatrix;
}


int main() {
	li** adjMatrix;
	li** expandedMatrix;
	li*** powOfExpandedMatrixArr = new li** [31];
	int N, S, E, T;
	int* pow2Arr = new int[31];
	char number;
	pow2Arr[0] = 1;

	for (int i = 1; i < 31; i++) {
		pow2Arr[i] = pow2Arr[i - 1] * 2;
	}

	scanf("%d %d %d %d", &N, &S, &E, &T);
	S--;
	E--;
	adjMatrix = new li * [N];
	for (int i = 0; i < N; i++) {
		adjMatrix[i] = new li[N];
		for (int k = 0; k < N; k++) {
			scanf("%c", &number);
			while (number < '0' || number > '9') {
				scanf("%c", &number);
			}
			adjMatrix[i][k] = number - '0';
		}
	}

	int expandedN = 5 * N;
	expandedMatrix = new li * [expandedN];
	for (int i = 0; i < expandedN; i++) {
		expandedMatrix[i] = new li[expandedN];
		memset(expandedMatrix[i], 0, sizeof(li) * expandedN);
	}

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 4; k++) {
			expandedMatrix[i * 5 + k][i * 5 + k + 1] = 1;
		}

		for (int k = 0; k < N; k++) {
			if (adjMatrix[i][k] > 0) {
				expandedMatrix[i * 5 + 4][5 * (k + 1) - (int)adjMatrix[i][k]] = 1;
			}
		}
	}

	powOfExpandedMatrixArr[0] = expandedMatrix;
	for (int i = 1; i < 31; i++) {
		powOfExpandedMatrixArr[i] = multiplyMatrix(powOfExpandedMatrixArr[i - 1], 
			powOfExpandedMatrixArr[i - 1], expandedN);
	}

	int bits[32];
	li** matrix = NULL;
	li** newMarix;
	memset(bits, 0, sizeof(int) * 32);

	for (int i = 30; i >= 0; i--) {
		if (pow2Arr[i] <= T) {
			T -= pow2Arr[i];
			bits[i] = 1;
		}
	}

	int bitsIndex = 0;
	while (bits[bitsIndex] == 0) {
		bitsIndex++;
	}
	matrix = powOfExpandedMatrixArr[bitsIndex];
	bitsIndex++;

	for (; bitsIndex <= 30; bitsIndex++) {
		if (bits[bitsIndex] == 0) {
			continue;
		}

		newMarix = multiplyMatrix(matrix, powOfExpandedMatrixArr[bitsIndex], expandedN);
		for (int i = 0; i < expandedN; i++) {
			delete[](matrix[i]);
		}
		delete[](matrix);

		matrix = newMarix;
	}

	printf("%lld", matrix[S * 5 + 4][E * 5 + 4]);
	return 0;
}