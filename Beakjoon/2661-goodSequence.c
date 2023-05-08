#include <stdio.h>
#include <stdlib.h>

int solve(char arr[], int depth, int goal) {
	if (depth == 0) {
		arr[0] = '1';
		solve(arr, 1, goal);
		return 1;
	}
	if (depth == goal) {
		return 1;
	}
	int left, right;
	int i, j, k;
	for (i = 0; i < 3; i++) {
		if (arr[depth - 1] == i + '1') {
			continue;
		}
		arr[depth] = i + '1';
		for (k = 2; depth + 1 - k * 2 >= 0; k++) {
			left = depth + 1 - k * 2;
			right = left + k;
			for (j = 0; j < k; j++) {
				if (arr[left] != arr[right]) {
					break;
				}
				left++; right++;
			}
			if (j == k) {
				break;
			}
		}
		if (depth + 1 - k * 2 < 0) {
			if (solve(arr, depth + 1, goal) == 1) {
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	int len;
	char arr[81];
	scanf("%d", &len);

	solve(arr, 0, len);
	arr[len] = '\0';
	printf("%s", arr);
	return 0;
}