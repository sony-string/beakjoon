#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = *a;
}

void merge(char** arr, int s, int m, int l) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		char** sorted = (char**)malloc(size * sizeof(char*));
		int* sortedIndex = (int*)malloc(size * sizeof(int));
		while (i <= m && j <= l) {
			if (strlen(arr[i]) < strlen(arr[j])) {
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
		free(sortedIndex);
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

void mergeInDict(char** arr, int s, int m, int l) {
	int size = l - s + 1;
	int temp;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		char** sorted = (char**)malloc(size * sizeof(char*));
		int* sortedIndex = (int*)malloc(size * sizeof(int));
		while (i <= m && j <= l) {
			temp = strcmp(arr[i], arr[j]);
			if (temp < 0) {
				sorted[k] = arr[i];

				i++; k++;
			}
			else if (strcmp > 0) {
				sorted[k] = arr[j];

				j++; k++;
			}
			else {
				printf("error in dictionary sort : strcmp is zero\n");
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
		free(sortedIndex);
	}
}

void sortInDict(char** arr, int s, int l) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		mergeInDict(arr, s, m, l);
	}
	else {
		sortInDict(arr, s, m);
		sortInDict(arr, m + 1, l);
		mergeInDict(arr, s, m, l);
	}
}

int main() {
	int nHeard, nSeen, small, large, count, l, r, m, num;
	char** personHeard, ** personUnknown, ** personSeen;
	char** sorted, ** searchingName;
	scanf("%d %d", &nHeard, &nSeen);
	personHeard = (char**)malloc(nHeard * sizeof(char*));
	personSeen = (char**)malloc(nSeen * sizeof(char*));
	int i;
	for (i = 0; i < nHeard; i++) {
		personHeard[i] = (char*)malloc(20 * sizeof(char));
		scanf("%s", personHeard[i]);
	}
	for (i = 0; i < nSeen; i++) {
		personSeen[i] = (char*)malloc(20 * sizeof(char));
		scanf("%s", personSeen[i]);
	}

	if (nHeard > nSeen) {
		small = nSeen;
		large = nHeard;
	}
	else {
		small = nHeard;
		large = nHeard;
	}
	personUnknown = (char**)malloc(small * sizeof(char*));

	if (small == nHeard) {
		sort(personHeard, 0, nHeard - 1);
		sorted = personHeard;
		searchingName = personSeen;
	}
	else {
		sort(personSeen, 0, nSeen - 1);
		sorted = personSeen;
		searchingName = personHeard;
	}

	count = 0;
	for (i = 0; i < large; i++) {
		l = 0; r = small - 1;
		while (r >= l) {
			m = (l + r) / 2;
			if (strlen(sorted[m]) > strlen(searchingName[i])) {
				r = m - 1;
				continue;
			}
			if (strlen(sorted[m]) == strlen(searchingName[i])) {
				num = strcmp(sorted[m], searchingName[i]);
				if (num > 0) {
					r = m - 1;
					continue;
				}
				if (num == 0) {
					personUnknown[count] = searchingName[i];
					count++;
					break;
				}
				l = m + 1;
				continue;
			}
			l = m + 1;
		}
	}

	sortInDict(personUnknown, 0, count - 1);
	printf("%d\n", count);
	for (i = 0; i < count; i++) {
		printf("%s\n", personUnknown[i]);
	}
	for (i = 0; i < small; i++) {
		free(sorted[i]);
	}
	free(sorted);
	for (i = 0; i < large; i++) {
		free(searchingName[i]);
	}
	free(searchingName);
	free(personUnknown);

	return 0;
}