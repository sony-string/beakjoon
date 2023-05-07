#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int* arr;
	int size;
	scanf("%d", &size);
	arr = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		scanf("%d", arr + i);
	}
	int coef, remain, temp, isValid = 0;
	if (size < 3) {
		if (size == 2) {
			if (arr[0] == arr[1]) {
				printf("%d", arr[0]);
				return 0;
			}
		}
		printf("A");
		return 0;
	}

	if (arr[0] == arr[1]) {
		coef = 1; remain = 0;
		isValid = 1;
	}
	else {
		temp = arr[2] - arr[1];
		if (temp % (arr[1] - arr[0]) == 0) {
			coef = temp / (arr[1] - arr[0]);
			temp = arr[1] * arr[1] - arr[0] * arr[2];
			if (temp % (arr[1] - arr[0]) == 0) {
				remain = temp / (arr[1] - arr[0]);
				isValid = 1;
			}
		}
	}
	if (isValid == 0) {
		printf("B");
		return 0;
	}

	for (int i = 0; i < size - 1; i++) {
		if (arr[i + 1] != coef * arr[i] + remain) {
			isValid = 0;
			break;
		}
	}
	if (isValid == 0) {
		printf("B");
		return 0;
	}
	else {
		printf("%lld", (long long)coef * (long long)arr[size - 1] + remain);
	}
	return 0;
}