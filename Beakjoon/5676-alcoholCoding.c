#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum {
	plus, minus, zero
};

typedef struct Node {
	int left, right;
	int sign;
	int numZero;
} Node;

void updateSegTree(Node** segTree, int index, int sign, int before) {
	if (before == sign) {
		return;
	}
	int cur = 1;
	int m;
	while (segTree[cur] != NULL) {
		if (before == zero) {
			segTree[cur]->numZero -= 1;
			if (sign == minus) {
				segTree[cur]->sign = segTree[cur]->sign == minus ? plus : minus;
			}
		}
		else if (before == plus) {
			if (sign == minus) {
				segTree[cur]->sign = segTree[cur]->sign == minus ? plus : minus;
			}
			else if (sign == zero) {
				segTree[cur]->numZero += 1;
			}
		}
		else if (before == minus) {
			segTree[cur]->sign = segTree[cur]->sign == minus ? plus : minus;
			if (sign == zero) {
				segTree[cur]->numZero += 1;
			}
		}

		m = segTree[cur]->right + segTree[cur]->left;
		m /= 2;
		if (index <= m) {
			cur = cur * 2;
		}
		else {
			cur = cur * 2 + 1;
		}
	}
}

void createSegTree(Node** segTree, int* arr, int node, int left, int right) {
	Node* nodep = (Node*)calloc(1, sizeof(Node));
	segTree[node] = nodep;
	segTree[node]->left = left;
	segTree[node]->right = right;

	if (right == left) {
		segTree[node]->sign = plus;
		if (arr[left] == 0) {
			segTree[node]->numZero = 1;
		}
		else if (arr[left] < 0) {
			segTree[node]->sign = minus;
		}
		return;
	}

	int m = left + right, leftNode = node * 2, rightNode = leftNode + 1;
	m /= 2;
	createSegTree(segTree, arr, leftNode, left, m);
	createSegTree(segTree, arr, rightNode, m + 1, right);
	segTree[node]->numZero = segTree[leftNode]->numZero + segTree[rightNode]->numZero;
	if (segTree[leftNode]->sign != segTree[rightNode]->sign) {
		segTree[node]->sign = minus;
	}
	else {
		segTree[node]->sign = plus;
	}
}

int getSign(Node** segTree, int node, int left, int right) {
	if (segTree[node]->left == left && segTree[node]->right == right) {
		if (segTree[node]->numZero > 0) {
			return zero;
		}
		else {
			return segTree[node]->sign;
		}
	}
	int sign = plus;
	int get;
	int leftNode = node * 2;
	int rightNode = leftNode + 1;
	int m = segTree[node]->left + segTree[node]->right;
	m /= 2;
	if (m >= right) {
		sign = getSign(segTree, leftNode, left, right);
	}
	else if (m < left) {
		sign = getSign(segTree, rightNode, left, right);
	}
	else {
		get = getSign(segTree, leftNode, left, m);
		if (get == zero) {
			return zero;
		}
		else if (get == minus) {
			sign = sign == minus ? plus : minus;
		}
		get = getSign(segTree, rightNode, m + 1, right);
		if (get == zero) {
			return zero;
		}
		else if (get == minus) {
			sign = sign == minus ? plus : minus;
		}
	}
	return sign;
}

void freeSegTree(Node** segTree, int node) {
	int left = node * 2;
	int right = left + 1;
	if (segTree[left] != NULL) {
		freeSegTree(segTree, left);
	}
	if (segTree[right] != NULL) {
		freeSegTree(segTree, right);
	}
	free(segTree[node]);
}

int main() {
	Node** segTree;
	int startFlag = 0;
	int* arr, size, numCmd, logSize;
	char cmd = 'C';
	char* result;
	int top;
	int left, right, index, num, sign, before;
	int i;
	
	while (scanf("%d %d", &size, &numCmd) != EOF) {
		if (startFlag == 1) {
			printf("\n");
		}
		else {
			startFlag = 1;
		}
		top = 0;
		logSize = (int)floor(log2((double)size)) + 1;
		segTree = (Node**)calloc((int)pow(2, logSize + 2) + 1, sizeof(Node*));
		result = (char*)malloc(numCmd + 1);
		arr = (int*)malloc((size + 1) * sizeof(int));
		for (i = 1; i <= size; i++) {
			scanf("%d", arr + i);
		}
		createSegTree(segTree, arr, 1, 1, size);
		for (i = 0; i < numCmd; i++) {
			scanf("%c", &cmd);
			while (cmd == '\n') {
				scanf("%c", &cmd);
			}
			if (cmd == 'C') {
				scanf("%d %d", &index, &num);
				if (arr[index] < 0) {
					before = minus;
				}
				else if (arr[index] == 0) {
					before = zero;
				}
				else {
					before = plus;
				}
				arr[index] = num;
				if (num > 0) {
					sign = plus;
				}
				else if (num == 0) {
					sign = zero;
				}
				else {
					sign = minus;
				}
				updateSegTree(segTree, index, sign, before);
			}
			else if (cmd == 'P') {
				scanf("%d %d", &left, &right);
				sign = getSign(segTree, 1, left, right);
				if (sign == zero) {
					result[top] = '0';
				}
				else if (sign == plus) {
					result[top] = '+';
				}
				else {
					result[top] = '-';
				}
				top++;
			}
			else {
				for (i = 0; i < 6251512; i++) {
					printf("*\n");
				}
			}
		}
		result[top] = '\0';
		printf("%s", result);
		freeSegTree(segTree, 1);
		free(result);
		free(arr);
	}

	return 0;
}