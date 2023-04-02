#include <stdio.h>
#include <stdlib.h>

void makeRightTree(int, int*, int*, int, int, int);

void makeLeftTree(int head, int* inOrder, int* postOrder, int numNodes, int l, int r) {
	printf("%d ", head);
	int numLeft, numRight, indexHead;
	int i;
	for (i = 0; head != inOrder[i]; i++) {}
	indexHead = i;
	numLeft = indexHead - l;
	numRight = r - indexHead;
	int left = - 1, right = -1;
	for (i = 0; head != postOrder[i]; i++) {}
	if (numRight > 0) {
		right = postOrder[i - 1];
	}
	if (numLeft > 0) {
		left = postOrder[i - numRight - 1];
	}
	if (left != -1) {
		makeLeftTree(left, inOrder, postOrder, numNodes, l, indexHead - 1);
	}
	if (right != -1) {
		makeRightTree(right, inOrder, postOrder, numNodes, indexHead + 1, r);
	}
}

void makeRightTree(int head, int* inOrder, int* postOrder, int numNodes, int l, int r) {
	printf("%d ", head);
	int numLeft, numRight, indexHead;
	int i;
	for (i = numNodes - 1;head != inOrder[i]; i--) {}
	indexHead = i;
	numLeft = indexHead - l;
	numRight = r - indexHead;
	int left = -1, right = -1;
	for (i = 0; head != postOrder[i]; i++) {}
	if (numRight > 0) {
		right = postOrder[i - 1];
	}
	if (numLeft > 0) {
		left = postOrder[i - numRight - 1];
	}
	if (left != -1) {
		makeLeftTree(left, inOrder, postOrder, numNodes, l, indexHead - 1);
	}
	if (right != -1) {
		makeRightTree(right, inOrder, postOrder, numNodes, indexHead + 1, r);
	}
}

int main() {
	int numNodes;
	scanf("%d", &numNodes);
	int* inOrder = (int*)malloc(numNodes * sizeof(int));
	int* postOrder = (int*)malloc(numNodes * sizeof(int));
	int i;
	for (i = 0; i < numNodes; i++) {
		scanf("%d", &inOrder[i]);
	}
	for (i = 0; i < numNodes; i++) {
		scanf("%d", &postOrder[i]);
	}
	int root = postOrder[numNodes - 1];
	for (i = 0; inOrder[i] != root; i++) {}
	int rootIndex = i;
	int numLeft, numRight;
	numLeft = i;
	numRight = numNodes - i - 1;
	int left = -1, right = -1;
	for (i = 0; root != postOrder[i]; i++) {}
	if (numRight > 0) {
		right = postOrder[i - 1];
	}
	if (numLeft > 0) {
		left = postOrder[i - numRight - 1];
	}
	printf("%d ", root);
	if (left != -1) {
		makeLeftTree(left, inOrder, postOrder, numNodes, 0, rootIndex - 1);
	}
	if (right != -1) {
		makeRightTree(right, inOrder, postOrder, numNodes, rootIndex + 1, numNodes - 1);
	}

	free(inOrder);
	free(postOrder);
	return 0;
}