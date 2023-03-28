#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(int* arr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		int* sorted = (int*)malloc(size * sizeof(int));
		while (i <= m && j <= l) {
			if (arr[i] <= arr[j]) {
				sorted[k] = arr[i];
				i++; k++;
			}
			else {
				sorted[k] = arr[j];
				j++; k++;
			}
		}
		if (i <= m) {
			while (k < size) {
				sorted[k] = arr[i];
				k++; i++;
			}
		}
		else {
			while (k < size) {
				sorted[k] = arr[j];
				k++; j++;
			}
		}
		for (i = 0; i < size; i++) {
			arr[i + s] = sorted[i];
		}
		free(sorted);
	}
}

void sort(int* arr, int s, int l) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		merge(arr, s, m, l);
	}
	else {
		sort(arr, s, m);
		sort(arr, m + 1, l);
		merge(arr, s, m, l);
	}
}

int main() {
	int* arr, *count;
	int numNumbers, sum = 0;
	int avg, middle, range, mode = 0;
	count = (int*)malloc(8001*sizeof(int));
	scanf("%d", &numNumbers);
	arr = (int*)malloc(numNumbers * sizeof(int));
	int i;
	for (i = 0; i < 8001; i++) {
		count[i] = 0;
	}
	for (i = 0; i < numNumbers; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
		count[arr[i]+4000] ++;
		if (count[arr[i]+4000] > count[mode+4000]) {
			mode = arr[i];
		}
	}
	avg = round((double)sum / numNumbers);
	sort(arr,0,numNumbers-1);
	middle = arr[(numNumbers - 1) / 2];
	range = arr[numNumbers - 1] - arr[0];
	
	int flag = 0;
	for (i = 0; i < 8001; i++) {
		if (count[i] == count[mode+4000]) {
			mode = i-4000;
			if (flag == 0) {
				flag++;
			}
			else {
				break;
			}
		}
	}
	free(arr);
	printf("%d\n%d\n%d\n%d", avg, middle, mode, range);
	return 0;
}