#include <stdio.h>
#include <stdlib.h>

int sorted[200000][2];
int stack[100000];


void merge(int** arr, int l, int r) {
	int m = l + r;
	m /= 2;
	int top = 0, left = l, right = m + 1;
	while (left <= m && right <= r) {
		if (arr[left][0] < arr[right][0]) {
			sorted[top][0] = arr[left][0];
			sorted[top][1] = arr[left][1];
			top++;
			left++;
			continue;
		}
		else if (arr[left][0] > arr[right][0]) {
			sorted[top][0] = arr[right][0];
			sorted[top][1] = arr[right][1];
			top++;
			right++;
			continue;
		}
		else {
			if (arr[left][1] < arr[right][1]) {
				sorted[top][0] = arr[left][0];
				sorted[top][1] = arr[left][1];
				top++;
				left++;
				continue;
			}
			else {
				sorted[top][0] = arr[right][0];
				sorted[top][1] = arr[right][1];
				top++;
				right++;
				continue;
			}
		}
	}
	while (left <= m) {
		sorted[top][0] = arr[left][0];
		sorted[top][1] = arr[left][1];
		top++;
		left++;
	}
	while (right <= r) {
		sorted[top][0] = arr[right][0];
		sorted[top][1] = arr[right][1];
		top++;
		right++;
	}
	top = 0;
	for (; l <= r; l++) {
		arr[l][0] = sorted[top][0];
		arr[l][1] = sorted[top][1];
		top++;
	}
}

void mergeSort(int** arr, int l, int r) {
	int m = l + r;
	m /= 2;
	if (l != r) {
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
	}
	else {
		return;
	}
	merge(arr, l, r);
}

int bisearch(int** arr, int num, int l, int r) {
	int m;
	while (r >= l) {
		m = r + l;
		m /= 2;
		if (num > arr[m][1]) {
			l = m + 1;
			continue;
		}
		else if (num < arr[m][1]) {
			r = m - 1;
			continue;
		}
		else {
			return 1;
		}
	}
	return 0;
}

int main() {
	int top = 0, cur, next;
	int** edges, numEdges;
	int* degrees;
	int* ptr;
	int* visited;
	int j;
	scanf("%d", &numEdges);
	degrees = (int*)calloc(numEdges + 1, sizeof(int));
	visited = (int*)calloc(numEdges + 1, sizeof(int));
	ptr = (int*)calloc(numEdges + 2, sizeof(int));
	numEdges -= 1;
	edges = (int**)malloc(numEdges * 2 * sizeof(int*));
	for (int i = 0; i < numEdges * 2; i += 2) {
		edges[i] = (int*)malloc(2 * sizeof(int));
		edges[i + 1] = (int*)malloc(2 * sizeof(int));
		scanf("%d %d", &edges[i][0], &edges[i][1]);
		edges[i + 1][0] = edges[i][1];
		edges[i + 1][1] = edges[i][0];
		degrees[edges[i][0]]++;
		degrees[edges[i][1]]++;
	}
	mergeSort(edges, 0, numEdges * 2 - 1);
	for (int i = 1; i <= numEdges + 1; i++) {
		ptr[i] = ptr[i - 1] + degrees[i - 1];
	}
	ptr[numEdges + 2] = numEdges * 2;
	
	scanf("%d", &cur);
	if (cur != 1) {
		printf("0");
		return 0;
	}
	visited[cur] = 1;
	top = 0;
	for (int i = 0; i < numEdges; i++) {
		stack[top] = cur;
		top++;
		scanf("%d", &next);
		if (bisearch(edges, next, ptr[cur], ptr[cur + 1] - 1) == 0) {
			printf("0");
			return 0;
		}
		visited[next] = 1;

		cur = next;
		while (top != 0) {
			for (j = ptr[cur]; j < ptr[cur + 1]; j++) {
				if (visited[edges[j][1]] == 0) {
					break;
				}
			}
			if (j == ptr[cur + 1]) {
				top--;
				cur = stack[top];
				continue;
			}
			else {
				break;
			}
		}
	}
	printf("1");
	return 0;
}