#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	int value;
	int stack;
	int cur;
	int color;
	struct TreeNode* leftNode;
	struct TreeNode* rightNode;
	struct TreeNode* parentNode;
} TreeNode;

enum {
	red, black
};

TreeNode* handleDoubledColor(TreeNode*);

TreeNode* findNextNode(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* cur = node->rightNode;

	if (node->cur < node->stack) {
		node->cur += 1;
		return node;
	}

	if (parentNode != NULL) {
		while (parentNode->parentNode != NULL && parentNode->value < node->value) {
			parentNode = parentNode->parentNode;
		}
	}

	if (cur != NULL) {
		while (cur->leftNode != NULL) {
			cur = cur->leftNode;
		}
	}

	if (cur == NULL) {
		if (parentNode != NULL) {
			if (parentNode->value > node->value) {
				parentNode->cur = 1;
				return parentNode;
			}
			return NULL;
		}
	}
	if (cur != NULL) {
		cur->cur = 1;
	}
	return cur;
}

TreeNode* findPreviousNode(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* cur = node->leftNode;

	if (node->cur > 1) {
		node->cur -= 1;
		return node;
	}

	if (parentNode != NULL) {
		while (parentNode->parentNode != NULL && parentNode->value > node->value) {
			parentNode = parentNode->parentNode;
		}
	}

	if (cur != NULL) {
		while (cur->rightNode != NULL) {
			cur = cur->rightNode;
		}
	}

	if (cur == NULL) {
		if (parentNode != NULL) {
			if (parentNode->value < node->value) {
				parentNode->cur = parentNode->stack;
				return parentNode;
			}
			return NULL;
		}
	}
	if (cur != NULL) {
		cur->cur = cur->stack;
	}
	return cur;
}
TreeNode* rotateLeft(TreeNode* node) {
	TreeNode* right = node->rightNode, * parent = node->parentNode;

	if (right == NULL) {
		return node;
	}

	if (parent != NULL) {
		if (parent->leftNode == node) {
			parent->leftNode = right;
			right->parentNode = parent;
		}
		else {
			parent->rightNode = right;
			right->parentNode = parent;
		}
	}
	else {
		right->parentNode = NULL;
	}

	if (right->leftNode != NULL) {
		right->leftNode->parentNode = node;
		node->rightNode = right->leftNode;
	}
	else {
		node->rightNode = NULL;
	}

	right->leftNode = node;
	node->parentNode = right;

	return right;
}

TreeNode* rotateRight(TreeNode* node) {
	TreeNode* left = node->leftNode, * parent = node->parentNode;

	if (left == NULL) {
		return node;
	}

	if (parent != NULL) {
		if (parent->leftNode == node) {
			parent->leftNode = left;
			left->parentNode = parent;
		}
		else {
			parent->rightNode = left;
			left->parentNode = parent;
		}
	}
	else {
		left->parentNode = NULL;
	}

	if (left->rightNode != NULL) {
		left->rightNode->parentNode = node;
		node->leftNode = left->rightNode;
	}
	else {
		node->leftNode = NULL;
	}

	left->rightNode = node;
	node->parentNode = left;

	return left;
}

TreeNode* resturcting(TreeNode* node, TreeNode* parentNode, TreeNode* grandNode) {
	TreeNode* newLeftNode, * newRightNode, * newParentNode;

	if (grandNode->leftNode == parentNode) {
		if (parentNode->leftNode == node) {
			newRightNode = grandNode;
			newLeftNode = node;
			newParentNode = parentNode;
			rotateRight(grandNode);
		}
		else {
			newRightNode = grandNode;
			newParentNode = node;
			newLeftNode = parentNode;
			rotateLeft(parentNode);
			rotateRight(grandNode);
		}
	}
	else {
		if (parentNode->leftNode == node) {
			newRightNode = parentNode;
			newParentNode = node;
			newLeftNode = grandNode;
			rotateRight(parentNode);
			rotateLeft(grandNode);
		}
		else {
			newRightNode = node;
			newLeftNode = grandNode;
			newParentNode = parentNode;
			rotateLeft(grandNode);
		}
	}

	newRightNode->color = red;
	newLeftNode->color = red;
	newParentNode->color = black;

	TreeNode* cur = newParentNode->parentNode;
	if (cur == NULL) {
		return newParentNode;
	}
	while (cur->parentNode != NULL) {
		cur = cur->parentNode;
	}
	return cur;
}

TreeNode* recoloring(TreeNode* node) {
	TreeNode* parentNode;
	TreeNode* grandNode;
	TreeNode* uncleNode;
	while (1) {
		parentNode = node->parentNode;
		grandNode = parentNode->parentNode;
		if (grandNode->leftNode == parentNode) {
			uncleNode = grandNode->rightNode;
		}
		else {
			uncleNode = grandNode->leftNode;
		}

		parentNode->color = black;
		uncleNode->color = black;
		grandNode->color = red;
		if (grandNode->parentNode == NULL) {
			grandNode->color = black;
		}
		else if (grandNode->parentNode->color == red) {
			node = grandNode;
			continue;
		}
		return node;
	}
}

TreeNode* handleDoubledColor(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* grandNode = parentNode->parentNode;
	TreeNode* uncleNode;
	if (grandNode->leftNode == parentNode) {
		uncleNode = grandNode->rightNode;
	}
	else {
		uncleNode = grandNode->leftNode;
	}

	if (uncleNode == NULL) {
		resturcting(node, parentNode, grandNode);
	}
	else if (uncleNode->color == black) {
		resturcting(node, parentNode, grandNode);
	}
	else {
		recoloring(node);
	}

	return node;
}

//red-black tree insert : always return root node
TreeNode* insert(TreeNode* root, TreeNode* node) {
	TreeNode* cur = root;
	TreeNode* previous = root;
	while (cur != NULL) {
		previous = cur;
		if (cur->value < node->value) {
			cur = cur->rightNode;
			continue;
		}
		else if (cur->value > node->value) {
			cur = cur->leftNode;
			continue;
		}
		else if (cur->value == node->value) {
			cur->stack += 1;
			free(node);
			return root;
		}
	}
	if (previous->value < node->value) {
		previous->rightNode = node;
	}
	else {
		previous->leftNode = node;
	}
	node->color = red;
	node->parentNode = previous;

	if (previous->color == red) {
		handleDoubledColor(node);
	}
	while (root->parentNode != NULL) {
		root = root->parentNode;
	}
	return root;
}

void freeMemTree(TreeNode* root) {
	if (root->leftNode != NULL) {
		freeMemTree(root->leftNode);
	}
	if (root->rightNode != NULL) {
		freeMemTree(root->rightNode);
	}
	free(root);
}

int main() {
	int testCases, len, dir, count;
	char* buffer = (char*)malloc(150);
	setvbuf(stdout, buffer, _IOFBF, 150);
	TreeNode* arr, * node, * middle;
	scanf("%d", &testCases);
	for (int T = 0; T < testCases; T++) {
		arr = (TreeNode*)calloc(1, sizeof(TreeNode));
		scanf("%d", &len);
		printf("%d\n", (len + 1) / 2);
		fflush(stdout);
		scanf("%d", &arr->value);
		printf("%d", arr->value);
		count = 1;
		if (len != 1) {
			printf(" ");
		}
		arr->stack = 1;
		arr->cur = 1;
		arr->color = black;
		middle = arr;
		for (int i = 1; i < len; i += 2) {
			dir = 0;
			node = (TreeNode*)calloc(1, sizeof(TreeNode));
			scanf("%d", &node->value);
			if (node->value == middle->value) {
				free(node);
				middle->stack += 1;
			}
			else {
				if (node->value < middle->value) {
					dir--;
				}
				else {
					dir++;
				}
				node->color = red;
				node->stack = 1;
				node->cur = 1;
				arr = insert(arr, node);
			}
			node = (TreeNode*)calloc(1, sizeof(TreeNode));
			scanf("%d", &node->value);
			if (node->value == middle->value) {
				free(node);
				middle->stack += 1;
				if (dir >= 0) {
					middle->cur += 1;
				}
			}
			else {
				if (node->value < middle->value) {
					dir--;
				}
				else {
					dir++;
				}
				node->color = red;
				node->stack = 1;
				node->cur = 1;
				arr = insert(arr, node);
				if (dir > 0) {
					middle = findNextNode(middle);
				}
				else if (dir < 0) {
					if (dir != -1) {
						middle = findPreviousNode(middle);
					}
				}
			}
			printf("%d", middle->value);
			count++;
			if (i + 2 < len) {
				if (count % 10 == 0) {
					printf("\n");
					fflush(stdout);
				}
				else {
					printf(" ");
				}
			}
		}
		if (T != testCases - 1) {
			printf("\n");
			freeMemTree(arr);
		}
		fflush(stdout);
	}
	return 0;
}