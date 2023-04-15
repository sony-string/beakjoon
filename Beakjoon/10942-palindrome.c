#include <stdio.h>
#include <stdlib.h>

int main() {
	int start, end, length, numAnswer,ansStart, ansEnd;
	int* arr, ** isPalindrome;
	scanf("%d", &length);
	start = 0; end = 0;
	arr = (int*)malloc(length * sizeof(int));
	isPalindrome = (int**)calloc(length, sizeof(int*));
	int i;
	for (i = 0; i < length; i++) {
		scanf("%d", &arr[i]);
		isPalindrome[i] = (int*)calloc(length, sizeof(int));
	}
	for (i = 0; i < length - 1; i++) {
		start = i; end = i;
		while (start >= 0 && end < length) {
			if (arr[start] == arr[end]) {
				isPalindrome[start][end] = 1;
				start--;
				end++;
				continue;
			}
			break;
		}
		start = i; end = i + 1;
		while (start >= 0 && end < length) {
			if (arr[start] == arr[end]) {
				isPalindrome[start][end] = 1;
				start--;
				end++;
				continue;
			}
			break;
		}
	}
	isPalindrome[length - 1][length - 1] = 1;
	scanf("%d", &numAnswer);
	for (i = 0; i < numAnswer; i++) {
		scanf("%d %d", &ansStart, &ansEnd);
		ansStart--; ansEnd--;
		printf("%d\n", isPalindrome[ansStart][ansEnd]);
	}

	free(arr);
	for (i = 0; i < length; i++) {
		free(isPalindrome[i]);
	}
	free(isPalindrome);
	return 0;
}