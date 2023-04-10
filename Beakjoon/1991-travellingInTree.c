#include <stdio.h>
#include <stdlib.h>

const char A = 'A';

typedef struct Node {
	struct Node* left;
	struct Node* right;
	char node;
} Node;

void preorder(const Node* tree, int node) {
	printf("%c", tree[node].node);
	if (tree[node].left != NULL) {
		preorder(tree, (int)(tree[node].left->node - A));
	}
	if (tree[node].right != NULL) {
		preorder(tree, (int)(tree[node].right->node - A));
	}
}

void inorder(const Node* tree, int node) {
	if (tree[node].left != NULL) {
		inorder(tree, (int)(tree[node].left->node - A));
	}
	printf("%c", tree[node].node);
	if (tree[node].right != NULL) {
		inorder(tree, (int)(tree[node].right->node - A));
	}
}

void postorder(const Node* tree, int node) {
	if (tree[node].left != NULL) {
		postorder(tree, (int)(tree[node].left->node - A));
	}
	if (tree[node].right != NULL) {
		postorder(tree, (int)(tree[node].right->node - A));
	}
	printf("%c", tree[node].node);
}

int main() {
	char ch, left, right;
	int numNodes;
	Node* tree;

	scanf("%d", &numNodes);
	tree = (Node*)calloc(numNodes, sizeof(Node));
	int i;
	for (i = 0; i < numNodes; i++) {
		tree[i].node = A + i;
	}
	for (i = 0; i < numNodes; i++) {
		scanf("%c", &ch);
		while (ch == '\n') {
			scanf("%c", &ch);
		}
		scanf("%c", &left);
		while (left == ' ') {
			scanf("%c", &left);
		}
		scanf("%c", &right);
		while (right == ' ') {
			scanf("%c", &right);
		}

		if (left != '.') {
			tree[ch - A].left = &tree[left - A];
		}
		if (right != '.') {
			tree[ch - A].right = &tree[right - A];
		}
	}

	preorder(tree, 0);
	printf("\n");
	inorder(tree, 0);
	printf("\n");
	postorder(tree, 0);

	free(tree);
	return 0;
}