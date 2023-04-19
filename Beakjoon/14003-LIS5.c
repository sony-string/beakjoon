#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node* nextNode;
} Node;

//return index of num or smaller and closest to num : decreasing sorted array
int bSearch(Node** arr, int num, int l, int r) {
	int m;
	while (r >= l) {
		m = (r + l) / 2;
		if (arr[m]->value < num) {
			r = m - 1;
			continue;
		}
		if (arr[m]->value > num) {
			l = m + 1;
			continue;
		}
		if (arr[m]->value == num) {
			break;
		}
	}
	if (arr[m]->value == num) {
		return m;
	}
	if (r == m - 1) {
		return m;
	}
	if (l == m + 1) {
		return l;
	}
}

int main() {
	Node* node;
	Node** nodeList;
	int numN, result = 0, index, num;
	int* array;
	//FILE* fp = freopen("input.txt", "r", stdin);/********/
	scanf("%d", &numN);
	array = (int*)malloc(numN * sizeof(int));
	Node** table = (Node**)calloc(numN, sizeof(Node*));
	int i;
	for (i = 0; i < numN; i++) {
		scanf("%d", &array[i]);
	}
	num = array[numN - 1];
	//메모리 해제를 위해 노드 포인터를 배열에 저장
	nodeList = (Node**)calloc(numN, sizeof(Node*));
	node = (Node*)calloc(1, sizeof(Node));
	node->value = num;
	table[result] = node;
	nodeList[0] = node;
	result++;
	for (i = numN - 2; i >= 0; i--) {
		node = (Node*)calloc(1, sizeof(Node));
		nodeList[numN - 1 - i] = node;
		num = array[i];
		node->value = num;
		index = bSearch(table, num, 0, result - 1);
		if (index != result) {
			if (table[index]->value == num) {
				continue;
			}
		}
		if (index == 0) {
			table[0] = node;
		}
		else if (index == result) {
			table[index] = node;
			node->nextNode = table[index - 1];
			result++;
		}
		else {
			table[index] = node;
			node->nextNode = table[index - 1];
		}
	}
	//fclose(fp); /******************/
	printf("%d\n", result);
	node = table[result - 1];
	while (node != NULL) {
		printf("%d ", node->value);
		node = node->nextNode;
	}

	for (i = 0; i < numN; i++) {
		free(nodeList[i]);
	}
	free(nodeList);
	free(array);
	free(table);
	return 0;
}