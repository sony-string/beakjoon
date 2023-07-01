#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;

#define DOMINATOR 1'000'000'007

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
	li D;
	li* pow2Arr = new li[31];
	pow2Arr[0] = 1;

	for (int i = 1; i < 31; i++) {
		pow2Arr[i] = pow2Arr[i - 1] * 2;
	}

	li adjMatrix[8][8] = {
		{ 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 1, 0, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 1, 1, 0 }
	};

	li*** powOfMatrixArr = new li** [31];
	powOfMatrixArr[0] = new li* [8];
	for (int i = 0; i < 8; i++) {
		powOfMatrixArr[0][i] = new li[8];
		memcpy(powOfMatrixArr[0][i], adjMatrix[i], sizeof(li[8]));
	}
	
	for (int i = 1; i < 31; i++) {
		powOfMatrixArr[i] = multiplyMatrix(powOfMatrixArr[i - 1], powOfMatrixArr[i - 1], 8);
	}


	li bits[32];
	li** matrix = NULL;
	li** newMarix;
	memset(bits, 0, sizeof(li) * 32);


	scanf("%lld", &D);
	if (D > 1) {
		D -= 1;
		for (int i = 30; i >= 0; i--) {
			if (pow2Arr[i] <= D) {
				D -= pow2Arr[i];
				bits[i] = 1;
			}
		}

		int bitsIndex = 0;
		while (bits[bitsIndex] == 0) {
			bitsIndex++;
		}
		matrix = powOfMatrixArr[bitsIndex];
		bitsIndex++;

		for (; bitsIndex <= 30; bitsIndex++) {
			if (bits[bitsIndex] == 0) {
				continue;
			}

			newMarix = multiplyMatrix(matrix, powOfMatrixArr[bitsIndex], 8);
			for (int i = 0; i < 8; i++) {
				delete[](matrix[i]);
			}
			delete[](matrix);

			matrix = newMarix;
		}

		printf("%lld", (matrix[0][1] + matrix[0][2]) % DOMINATOR);
	}
	else {
		if (D == 0)
			printf("1");
		else
			printf("0");
	}
	return 0;
}