#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(double* arr, long long** objArr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		double* sorted = (double*)malloc(size * sizeof(double));
		long long** objSorted = (long long**)malloc(size * sizeof(long long*));
		while (i <= m && j <= l) {
			if (arr[i] <= arr[j]) {
				sorted[k] = arr[i];
				objSorted[k] = objArr[i];
				i++; k++;
			}
			else {
				sorted[k] = arr[j];
				objSorted[k] = objArr[j];
				j++; k++;
			}
		}
		if (i <= m) {
			while (k < size) {
				sorted[k] = arr[i];
				objSorted[k] = objArr[i];
				k++; i++;
			}
		}
		else {
			while (k < size) {
				sorted[k] = arr[j];
				objSorted[k] = objArr[j];
				k++; j++;
			}
		}
		for (i = 0; i < size; i++) {
			arr[i + s] = sorted[i];
			objArr[i + s] = objSorted[i];
		}
		free(sorted);
		free(objSorted);
	}
}

void sort(double* arr, long long** objArr, int s, int l) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		merge(arr, objArr, s, m, l);
	}
	else {
		sort(arr, objArr, s, m);
		sort(arr, objArr, m + 1, l);
		merge(arr, objArr, s, m, l);
	}
}

long long getSizeofSquare(long long vector1[2], long long vector2[2]) {
	return vector1[1] * vector2[0] - vector1[0] * vector2[1];
}

int main() {
	long long** pos;
	double* angles, lenLeft, lenRight, area = 0;
	long long vectorLeft[2], vectorRight[2];
	int numVertex;
	scanf("%d", &numVertex);
	int i;
	pos = (long long**)calloc(numVertex, sizeof(long long*));
	angles = (double*)calloc(numVertex, sizeof(double));
	for (i = 0; i < numVertex; i++) {
		pos[i] = (long long*)calloc(3, sizeof(long long));
		scanf("%lld %lld", &pos[i][0], &pos[i][1]);
	}

	for (i = 2; i < numVertex; i++) {
		vectorLeft[0] = pos[i - 1][0] - pos[0][0];
		vectorLeft[1] = pos[i - 1][1] - pos[0][1];
		vectorRight[0] = pos[i][0] - pos[0][0];
		vectorRight[1] = pos[i][1] - pos[0][1];
		area += getSizeofSquare(vectorLeft, vectorRight);
	}
	if (area < 0) {
		area *= -1;
	}
	area /= 2;
	area *= 10;
	area = round(area);
	area /= 10;
	printf("%.1lf", area);
	return 0;
}