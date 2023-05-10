#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int stack[100];

typedef struct Node {
	int value;
	int left, right;
}Node;

enum {
	even, odd
};

void makeSegTree(Node* sT, int* arr, int size) {
	int top = 0, cur, l, r, m, next;
	sT[1].left = 1;
	sT[1].right = size;
	stack[top] = 1;
	top++;
	while (top > 0) {
		top--;
		cur = stack[top];
		l = sT[cur].left;
		r = sT[cur].right;
		while (1) {
			if (l == r) {
				if (arr[l] % 2 == 0) {
					sT[cur].value = 1;
				}
				else {
					sT[cur].value = 0;
				}
				break;
			}
			next = cur * 2;
			m = l + r;
			m /= 2;
			if (sT[next].value == -1) {
				stack[top] = cur;
				top++;
				sT[next].left = l;
				sT[next].right = m;
				r = m;
				cur = next;
				continue;
			}
			next++;
			if (sT[next].value == -1) {
				stack[top] = cur;
				top++;
				sT[next].left = m + 1;
				sT[next].right = r;
				l = m + 1;
				cur = next;
				continue;
			}
			sT[cur].value = sT[next].value + sT[next - 1].value;
			break;
		}
	}
}

void updateSegTree(Node* sT, int index, int before, int now) {
	if (before == now) {
		return;
	}
	int top = 0, cur = 1, m;
	int flag;
	if (now == even && before == odd) {
		flag = 1;
	}
	else {
		flag = -1;
	}

	while (sT[cur].value != -1) {
		sT[cur].value += flag;
		m = sT[cur].left + sT[cur].right;
		m /= 2;
		if (sT[cur].left == sT[cur].right) {
			break;
		}
		else if (m >= index) {
			cur = cur * 2;
			continue;
		}
		else {
			cur = cur * 2 + 1;
			continue;
		}
	}
}

int getNumOfEven(Node* sT, int node, int l, int r) {
	int m, left, right, sum = 0;
	left = sT[node].left;
	right = sT[node].right;
	m = left + right;
	m /= 2;

	if (l == left && r == right) {
		return sT[node].value;
	}
	else {
		if (r <= m) {
			sum += getNumOfEven(sT, node * 2, l, r);
			return sum;
		}
		else if (l > m) {
			sum += getNumOfEven(sT, node * 2 + 1, l, r);
			return sum;
		}
		else {
			sum += getNumOfEven(sT, node * 2, l, m);
			sum += getNumOfEven(sT, node * 2 + 1, m + 1, r);
			return sum;
		}
	}
	return sum;
}

int main() {
	int cmd, arrSize, logSize, numQuery;
	int* arr;
	int answer, num, befo, now, left, right, index;
	Node* segTree;
	scanf("%d", &arrSize);
	logSize = (int)ceil((double)log2(arrSize)) + 1;
	segTree = (Node*)calloc((1 << logSize), sizeof(Node));
	arr = (int*)malloc((arrSize + 1) * sizeof(int));
	memset(segTree, -1, (1 << logSize) * sizeof(Node));

	for (int i = 1; i <= arrSize; i++) {
		scanf("%d", arr + i);
	}
	makeSegTree(segTree, arr, arrSize);
	scanf("%d", &numQuery);
	for (int i = 0; i < numQuery; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d %d", &index, &num);
			if (arr[index] % 2 == 0) {
				befo = even;
			}
			else {
				befo = odd;
			}
			if (num % 2 == 0) {
				now = even;
			}
			else {
				now = odd;
			}
			if (befo == now) {
				continue;
			}
			updateSegTree(segTree, index, befo, now);
			arr[index] = num;
		}
		else if (cmd == 2) {
			scanf("%d %d", &left, &right);
			answer = getNumOfEven(segTree, 1, left, right);
			printf("%d\n", answer);
		}
		else {
			scanf("%d %d", &left, &right);
			num = right - left + 1;
			answer = num - getNumOfEven(segTree, 1, left, right);
			printf("%d\n", answer);
		}
	}
	return 0;
}