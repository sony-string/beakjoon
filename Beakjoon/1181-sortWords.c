#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char**, int, int);

int main() {
	int numberOfLines;
	scanf("%d", &numberOfLines);
	char** arr = (char**)malloc(numberOfLines * sizeof(char*));
	int i;

	for (i = 0; i < numberOfLines; i++) {
		arr[i] = (char*)malloc(51 * sizeof(char));
		scanf("%s", arr[i]);
	}
	sort(arr, 0, numberOfLines-1);
	char* lastsentence;
	printf("%s\n", arr[0]);
	lastsentence = arr[0];
	for (i = 1; i < numberOfLines; i++) {
		if (strcmp(lastsentence, arr[i]) == 0)
			continue;
		lastsentence = arr[i];
		printf("%s\n", arr[i]);
	}

	for (i = 0; i < numberOfLines; i++)
		free(arr[i]);
	free(arr);
	return 0;
}

void merge(char** arr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		char** sorted = (char**)malloc(size * sizeof(char*));
		while (i <= m && j <= l) {
			if (strlen(arr[i])<strlen(arr[j])) {
				sorted[k] = arr[i];
				i++; k++;
			}
			else if (strlen(arr[i]) == strlen(arr[j])) {
				if (strcmp(arr[i], arr[j]) < 0) {
					sorted[k] = arr[i];
					i++; k++;
				}
				else {
					sorted[k] = arr[j];
					j++; k++;
				}
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

void sort(char** arr, int s, int l) {
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
