#include <stdio.h>

int main() {
	int arr[10];
	int i, j, count = 1;
	for (i = 0; i < 10; i++) {
		scanf("%d", &arr[i]);
		arr[i] %= 42;
	}
	for (i = 1; i < 10; i++) {
		for (j = 0; j < i; j++) {
			if (arr[j] == arr[i])
				break;
		}
		if (j == i)
			count++;
	}
	printf("%d", count);
	return 0;
}