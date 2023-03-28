#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mergeSort(int*, int, int);

int main() {
	char* src_file = "C:/Users/clc26/source/repos/practice/practice/input.txt";
	freopen(src_file, "r", stdin);

	int size;
	scanf("%d", &size);
	int* array = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		scanf("%d", &array[i]);
	}
	mergeSort(array, 0, size - 1);

	for (int i = 0; i < size; i++) {
		printf("%d\n", array[i]);
	}
	free(array);
	freopen("CON", "r", stdin);
	system("pause");
	
	return 0;
}

void merge(int* array, int s, int m, int l) {
	int* sorted = (int*)malloc((l - s + 1) * sizeof(int));
	int i=s, j=m,k=0;
	while (i <= m - 1 && j <= l) {
		if (array[i] <= array[j]) {
			sorted[k] = array[i];
			i++;
			k++;
		}
		else {
			sorted[k] = array[j];
			j++;
			k++;
		}
	}
	if (i < m) {
		while (k <= l -s) {
			sorted[k] = array[i];
			i++;
			k++;
		}
	}
	else if (j < l +1) {
		while (k <= l-s) {
			sorted[k] = array[j];
			j++;
			k++;
		}
	}
	for (int count = s; count <= l; count++) {
		array[count] = sorted[count-s];
	}
	free(sorted);
}

void mergeSort(int* array, int s, int l) {
	int m = (int)ceil(((double)s + l) / 2);
	if (l - m + 1 > 1) {
		mergeSort(array, s,m - 1);
		mergeSort(array,m,l);
	}
	if(s!=l)
		merge(array, s,m,l);
}