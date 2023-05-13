#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char value;
	char isEnd;
	struct Node* childNode;
	struct Node* lastChild;
	struct Node* nextSibling;
} Node;

void freeMemTree(Node* root) {
	Node* node, * next;
	node = root->childNode;
	while (node != NULL) {
		next = node->nextSibling;
		freeMemTree(node);
		node = next;
	}
	free(root);
}

int main() {
	int numCases;
	int numNumbers;
	char num;
	int len;
	char number[11];
	Node* root, * node, * cur, * pre;
	int i = 0, j = 0;

	scanf("%d", &numCases);
	for (int T = 0; T < numCases; T++) {
		root = (Node*)calloc(1, sizeof(Node));
		node = NULL; cur = NULL;
		root->value = -1;
		scanf("%d", &numNumbers);
		for (j = 0; j < numNumbers; j++) {
			scanf("%s", number);
			len = strlen(number);
			cur = root;
			for (i = 0; i < len; i++) {
				if (cur->isEnd == 1) {
					break;
				}
				num = number[i];
				pre = cur;
				cur = cur->childNode;
				if (pre->childNode != NULL) {
					while (cur != NULL) {
						if (cur->value == num) {
							break;
						}
						cur = cur->nextSibling;
					}
					if (cur == NULL) {
						node = (Node*)calloc(1, sizeof(Node));
						node->value = num;
						pre->lastChild->nextSibling = node;
						pre->lastChild = node;
						cur = node;
					}
					continue;
				}
				else {
					node = (Node*)calloc(1, sizeof(Node));
					pre->childNode = node;
					pre->lastChild = node;
					node->value = num;
					cur = node;
					continue;
				}
			}
			if (i != len) {
				printf("NO\n");
				break;
			}
			else if (cur != NULL) {
				cur->isEnd = 1;
				if (cur->childNode != NULL) {
					printf("NO\n");
					break;
				}
			}
		}
		if (j == numNumbers) {
			printf("YES\n");
		}
		else {
			j++;
			for (; j < numNumbers; j++) {
				scanf("%s", number);
			}
		}
		freeMemTree(root);
	}
	return 0;
}