#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = *a;
}

void merge(char** arr, int s, int m, int l, int* indexArr, int* indexToName) {
	int size = l - s + 1;
	if (size != 1) {
		int i = s, j = m + 1, k = 0;
		char** sorted = (char**)malloc(size * sizeof(char*));
		int* sortedIndex = (int*)malloc(size * sizeof(int));
		while (i <= m && j <= l) {
			if (strlen(arr[i]) < strlen(arr[j])) {
				sorted[k] = arr[i];
				sortedIndex[k] = indexArr[i];
				i++; k++;
			}
			else if (strlen(arr[i]) == strlen(arr[j])) {
				if (strcmp(arr[i], arr[j]) < 0) {
					sorted[k] = arr[i];
					sortedIndex[k] = indexArr[i];
					i++; k++;
				}
				else {
					sorted[k] = arr[j];
					sortedIndex[k] = indexArr[j];
					j++; k++;
				}
			}
			else {
				sorted[k] = arr[j];
				sortedIndex[k] = indexArr[j];
				j++; k++;
			}
		}
		if (i <= m) {
			while (k < size) {
				sorted[k] = arr[i];
				sortedIndex[k] = indexArr[i];
				k++; i++;
			}
		}
		else {
			while (k < size) {
				sorted[k] = arr[j];
				sortedIndex[k] = indexArr[j];
				k++; j++;
			}
		}
		for (i = 0; i < size; i++) {
			arr[i + s] = sorted[i];
			indexArr[i + s] = sortedIndex[i];
			indexToName[sortedIndex[i]] = i + s;
		}
		free(sorted);
		free(sortedIndex);
	}
}

void sort(char** arr, int s, int l, int* index, int* indexToName) {
	int m = (s + l) / 2;
	if (m - s == 0) {
		merge(arr, s, m, l, index, indexToName);
	}
	else {
		sort(arr, s, m, index, indexToName);
		sort(arr, m + 1, l, index, indexToName);
		merge(arr, s, m, l, index, indexToName);
	}
}

int main() {
	int numPokemons, i, L, numQuizs;
	int number, len, l, r, m;
	scanf("%d %d", &numPokemons, &numQuizs);
	char** pokemons = (char**)malloc(numPokemons * sizeof(char*));
	int* index = (int*)malloc(numPokemons * sizeof(int));
	int* indexToName = (int*)malloc(numPokemons * sizeof(int));
	char quiz[21];
	for (i = 0; i < numPokemons; i++) {
		pokemons[i] = (char*)malloc(21 * sizeof(char));
		scanf("%s", pokemons[i]);
		index[i] = i;
		indexToName[i] = i;
	}
	sort(pokemons, 0, numPokemons-1, index, indexToName);
	for (L = 0; L < numQuizs; L++) {
		scanf("%s", quiz);
		if (quiz[0] >= 48 && quiz[0] <= 57) {
			number = 0;
			len = (int)strlen(quiz);
			for (i = 0; i < len; i++) {
				number += (int)pow(10, (double)len - 1 - i) * (quiz[i]-48);
			}
			number --;
			printf("%s\n", pokemons[indexToName[number]]);
			continue;
		}
		l = 0; r = numPokemons - 1;
		while (1) {
			m = (l + r) / 2;
			if (strlen(quiz) < strlen(pokemons[m])) {
				r = m - 1;
				continue;
			}
			if (strlen(quiz) == strlen(pokemons[m])) {
				number = strcmp(quiz, pokemons[m]);
				if (number == 0) {
					printf("%d\n", index[m] + 1);
					break;
				} else if (number < 0) {
					r = m - 1;
					continue;
				}
				else {
					l = m + 1;
				}
			}
			l = m + 1;
		}
	}
	return 0;
}