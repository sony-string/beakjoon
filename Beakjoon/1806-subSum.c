#include <stdio.h>
#include <stdlib.h>

int main() {
	int numNumbers, goalSum, result = 100001;
	scanf("%d %d", &numNumbers, &goalSum);
	int* arr = (int*)malloc(numNumbers * sizeof(int));
	int i;
	int sum = 0, l = 0, r = 0;

	for (i = 0; i < numNumbers; i++) {
		scanf("%d", &arr[i]);
		if (sum < goalSum) {
			sum += arr[i];
			r++;
		}
	}
	if (sum >= goalSum) {
		result = r - l;
	}
	else {
		free(arr);
		printf("0");
		return 0;
	}

	while (r < numNumbers) {
		if (sum >= goalSum) {
			sum -= arr[l];
			l++;
		}
		if (sum < goalSum) {
			sum += arr[r];
			r++;
		}
		
		if (sum <= goalSum) {
			if (result > r - l) {
				result = r - l;
			}
		}
	}
	
	while (sum >= goalSum) {
		sum -= arr[l];
		l++;
	}
	if (result > r - l + 1) {
		result = r - l + 1;
	}

	printf("%d", result);
	free(arr);
	return 0;
}