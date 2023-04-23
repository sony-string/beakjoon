#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* data;
	int level;
	struct Node* nextNode;
	struct Node* child;
} Node;

Node* addChildNode(Node* node, Node* child) {
	Node* pre, * cur;
	pre = node;
	cur = pre->child;
	//printf("adding %s below %s\n", child->data, node->data);
	while (cur != NULL) {
		if (strcmp(cur->data, child->data) == 0) {
			//printf("but %s already exists\n", child->data);
			free(child);
			return cur;
		}
		if (strcmp(cur->data, child->data) > 0) {
			break;
		}
		pre = cur;
		cur = pre->nextNode;
	}
	if (pre != node) {
		pre->nextNode = child;
	}
	else {
		pre->child = child;
	}
	child->nextNode = cur;
	child->level = node->level + 1;
	return child;
}

void printTree(Node* root, Node* node) {
	int i;
	if (root != node) {
		for (i = 0; i < node->level; i++) {
			printf("--");
		}
		printf("%s\n", node->data);
	}
	Node* next = node->child;
	while (next != NULL) {
		printTree(root, next);
		next = next->nextNode;
	}
}

int main() {
	Node root;
	root.level = -1;
	root.nextNode = NULL;
	root.child = NULL;
	root.data = (char*)calloc(20, sizeof(char));
	root.data[0] = '\0';
	Node* node, * cur;

	int numLeaves, numLevel;
	int i, level;

	scanf("%d", &numLeaves);
	for (i = 0; i < numLeaves; i++) {
		scanf("%d", &numLevel);
		cur = &root;
		for (level = 0; level < numLevel; level++) {
			node = (Node*)calloc(1, sizeof(Node));
			node->data = (char*)calloc(16, sizeof(char));
			scanf("%s", node->data);
			cur = addChildNode(cur, node);
		}
	}
	//printf("\n\n");
	printTree(&root, &root);
	return 0;
}