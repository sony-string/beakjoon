#include <stdio.h>
#include <stdlib.h>

int max = 1;

typedef struct TreeNode {
	int value;
	int streak;
	int color;
	int* list;
	struct TreeNode* leftNode;
	struct TreeNode* rightNode;
	struct TreeNode* parentNode;
} TreeNode;

enum {
	red, black
};

TreeNode* findNextNode(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* cur = node->rightNode;

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
				return parentNode;
			}
			return NULL;
		}
	}

	return cur;
}

int handleDoublyBlack(TreeNode*);
TreeNode* handleDoubledColor(TreeNode*);

TreeNode* findPreviousNode(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* cur = node->leftNode;

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
				return parentNode;
			}
			return NULL;
		}
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
	TreeNode* parentNode = node->parentNode;
	TreeNode* grandNode = parentNode->parentNode;
	TreeNode* uncleNode;
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
		handleDoubledColor(grandNode);
	}
	return node;
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

//sibling is red => rotate and solve with new sibling
void doublyblackCase2(TreeNode* sibling) {
	TreeNode* newSibling;
	sibling->color = sibling->parentNode->color;
	sibling->parentNode->color = red;
	if (sibling->parentNode->rightNode == sibling) {
		newSibling = sibling->leftNode;
		rotateLeft(sibling->parentNode);
	}
	else {
		newSibling = sibling->rightNode;
		rotateRight(sibling->parentNode);
	}
	handleDoublyBlack(newSibling);
}

//sibling is black and sibling's outside child is red
void doublyblackCase6(TreeNode* sibling) {
	sibling->color = sibling->parentNode->color;
	sibling->parentNode->color = black;
	if (sibling->parentNode->rightNode == sibling) {
		sibling->rightNode->color = black;
		rotateLeft(sibling->parentNode);
	}
	else {
		sibling->leftNode->color = black;
		rotateRight(sibling->parentNode);
	}
}

int handleDoublyBlack(TreeNode* sibling) {
	//sibling is red
	if (sibling->color == red) {
		doublyblackCase2(sibling);
		return 0;
	}

	if (sibling->color == black) {
		//sibling 과 그의 자식노드가 모두 black 일때
		if (sibling->leftNode == NULL && sibling->rightNode == NULL) {
			//sibling의 부모도 black 일때 => sibling과 doublyBlack의 블랙을 부모에게 위임
			if (sibling->parentNode->color == black) {
				sibling->color = red;
				if (sibling->parentNode->parentNode == NULL) {
					return 0;
				}
				if (sibling->parentNode->parentNode->leftNode == sibling->parentNode) {
					handleDoublyBlack(sibling->parentNode->parentNode->rightNode);
					return 0;
				}
				else {
					handleDoublyBlack(sibling->parentNode->parentNode->leftNode);
					return 0;
				}
			}
			//sibling 의 부모는 red일때 => 색 위임, doubly black 미발생
			sibling->color = red;
			sibling->parentNode->color = black;
			return 0;
		}
		if (sibling->leftNode != NULL && sibling->rightNode == NULL) {
			if (sibling->leftNode->color == black) {
				//sibling의 부모도 black 일때 => sibling과 doublyBlack의 블랙을 부모에게 위임
				if (sibling->parentNode->color == black) {
					sibling->color = red;
					if (sibling->parentNode->parentNode == NULL) {
						return 0;
					}
					if (sibling->parentNode->parentNode->leftNode == sibling->parentNode) {
						handleDoublyBlack(sibling->parentNode->parentNode->rightNode);
						return 0;
					}
					else {
						handleDoublyBlack(sibling->parentNode->parentNode->leftNode);
						return 0;
					}
				}
				//sibling 의 부모는 red일때 => 색 위임, doubly black 미발생
				sibling->color = red;
				sibling->parentNode->color = black;
				return 0;
			}
		}
		if (sibling->rightNode != NULL && sibling->leftNode == NULL) {
			if (sibling->rightNode->color == black) {
				//sibling의 부모도 black 일때 => sibling과 doublyBlack의 블랙을 부모에게 위임
				if (sibling->parentNode->color == black) {
					sibling->color = red;
					if (sibling->parentNode->parentNode == NULL) {
						return 0;
					}
					if (sibling->parentNode->parentNode->leftNode == sibling->parentNode) {
						handleDoublyBlack(sibling->parentNode->parentNode->rightNode);
						return 0;
					}
					else {
						handleDoublyBlack(sibling->parentNode->parentNode->leftNode);
						return 0;
					}
				}
				//sibling 의 부모는 red일때 => 색 위임, doubly black 미발생
				sibling->color = red;
				sibling->parentNode->color = black;
				return 0;
			}
		}
		if (sibling->leftNode != NULL && sibling->rightNode != NULL) {
			if (sibling->leftNode->color == black && sibling->rightNode->color == black) {
				//sibling의 부모도 black 일때 => sibling과 doublyBlack의 블랙을 부모에게 위임
				if (sibling->parentNode->color == black) {
					sibling->color = red;
					if (sibling->parentNode->parentNode == NULL) {
						return 0;
					}
					if (sibling->parentNode->parentNode->leftNode == sibling->parentNode) {
						handleDoublyBlack(sibling->parentNode->parentNode->rightNode);
						return 0;
					}
					else {
						handleDoublyBlack(sibling->parentNode->parentNode->leftNode);
						return 0;
					}
				}
				//sibling 의 부모는 red일때 => 색 위임, doubly black 미발생
				sibling->color = red;
				sibling->parentNode->color = black;
				return 0;
			}
		}

		//silbing 이 black 이고, 자식노드중 하나 이상이 red일때
		//sibling이 오른쪽 형제일때
		if (sibling->parentNode->rightNode == sibling) {
			/*silbing 의 왼쪽 자식이 red일때
			=> sibling 기준 우회전 후, silbing의 새로운 부모와 sibling의 색을 바꿔서 case6를 만족시킴
			*/
			if (sibling->leftNode != NULL) {
				if (sibling->leftNode->color == red) {
					rotateRight(sibling);
					sibling->color = red;
					sibling->parentNode->color = black;
					sibling = sibling->parentNode;
					doublyblackCase6(sibling);
					return 0;
				}
			}
			
			//case 6 : sibling 이 black, 오른쪽 자식 노드가 red
			if (sibling->rightNode->color == red) {
				doublyblackCase6(sibling);
				return 0;
			}
		}
		//sibling 이 왼쪽 형제일때
		if (sibling->parentNode->leftNode == sibling) {
			/*silbing 의 오른쪽 자식이 red일때
			=> sibling 기준 좌회전 후, silbing의 새로운 부모와 sibling의 색을 바꿔서 case6를 만족시킴
			*/
			if (sibling->rightNode != NULL) {
				if (sibling->rightNode->color == red) {
					rotateLeft(sibling);
					sibling->color = red;
					sibling->parentNode->color = black;
					sibling = sibling->parentNode;
					doublyblackCase6(sibling);
					return 0;
				}
			}

			//case 6 : sibling 이 black, 왼쪽 자식 노드가 red
			if (sibling->leftNode->color == red) {
				doublyblackCase6(sibling);
				return 0;
			}
		}
	}
	int i;
	for (i = 0; i < 1000000; i++) {
		printf("error ");
	}
}

//red-black tree delete : always return root node
TreeNode* delete(TreeNode* node) {
	TreeNode* left = node->leftNode, * right = node->rightNode, * parent = node->parentNode;
	TreeNode* cur, * siblingOfReplacer;
	//현 문제에서 빈 트리가 될 일은 없으니 체크 X
	if (left == NULL && right == NULL) {
		if (parent->leftNode == node) {
			parent->leftNode = NULL;
			siblingOfReplacer = parent->rightNode;
		}
		else {
			parent->rightNode = NULL;
			siblingOfReplacer = parent->leftNode;
		}
		if (node->color == black) {
			handleDoublyBlack(siblingOfReplacer);
		}
		//free(node->list);
		free(node);
		cur = parent;
		return cur;
	}
	if (left != NULL && right != NULL) {
		cur = node->leftNode;
		while (cur->rightNode != NULL) {
			cur = cur->rightNode;
		}
		node->value = cur->value;
		node->streak = cur->streak;
		//free(node->list);
		//node->list = cur->list;
		//cur->list = (int*)calloc(cur->streak, sizeof(int));
		return delete(cur);
	}

	if (parent == NULL) {
		if (left == NULL) {
			right->color = black;
			right->parentNode = NULL;
			//free(node->list);
			free(node);
			return right;
		}
		else {
			left->color = black;
			left->parentNode = NULL;
			//free(node->list);
			free(node);
			return left;
		}
	}

	if (left == NULL) {
		cur = right;
	}
	else {
		cur = left;
	}
	cur->parentNode = node->parentNode;
	if (parent->leftNode == node) {
		parent->leftNode = cur;
		siblingOfReplacer = parent->rightNode;
	}
	else {
		parent->rightNode = cur;
		siblingOfReplacer = parent->leftNode;
	}


	if (node->color == black) {
		if (cur->color == red) {
			cur->color = black;
			free(node);
			return cur;
		}
		free(node);
		handleDoublyBlack(siblingOfReplacer);
	}
	return cur;
}


//red-black tree insert : always return root node
TreeNode* insert(TreeNode* root, TreeNode* node) {
	TreeNode* cur = root;
	TreeNode* previous = root;
	int i;
	while (cur != NULL) {
		previous = cur;
		if (cur->value < node->value) {
			cur = cur->rightNode;
			continue;
		}
		if (cur->value > node->value) {
			cur = cur->leftNode;
			continue;
		}
		if (cur->value == node->value) {
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

	// 문제 풀이 상 삭제해야할 노드가 있는지 확인
	//printf("inserting %d\n", node->value);
	TreeNode* nextNode = findNextNode(node);
	if (nextNode == NULL) {
		//printf("new start : %d\n", node->value);
		node->streak = 1;
		//node->list = (int*)calloc(1, sizeof(int));
		//node->list[0] = node->value;
	}
	else {
		node->streak = nextNode->streak + 1;
		//node->list = (int*)calloc(node->streak, sizeof(int));
		//for (i = 0; i < nextNode->streak; i++) {
		//	node->list[i] = nextNode->list[i];
		//}
		//node->list[i] = node->value;
		//printf("successing %d -> %d\n", nextNode->value, node->value);
	}
	nextNode = findPreviousNode(node);
	if (nextNode != NULL) {
		//printf("%d is replaced by %d\n", nextNode->value, node->value);
		if (node->streak == nextNode->streak) {
			delete(nextNode);
		}
	}
	//printf("***********************************\n");
	
	return node;
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
	TreeNode* root, * node;
	int numN;
	int* array;

	FILE* fp = freopen("input.txt", "r", stdin);/********/

	scanf("%d", &numN);
	array = (int*)malloc(numN * sizeof(int));
	int i;
	for (i = 0; i < numN; i++) {
		scanf("%d", &array[i]);
	}
	root = (TreeNode*)calloc(1, sizeof(TreeNode));
	root->value = array[numN - 1];
	root->color = black;
	root->streak = 1;
	//root->list = (int*)calloc(1, sizeof(int));
	//root->list[0] = root->value;

	for (i = numN - 2; i >= 0; i--) {
		//뒤에서부터 이진탐색트리에 적절히 삽입 / 삭제
		node = (TreeNode*)calloc(1, sizeof(TreeNode));
		node->value = array[i];
		root = insert(root, node);
		if (root->parentNode != NULL) {
			while (root->parentNode != NULL) {
				root = root->parentNode;
			}
		}
	}

	node = root;
	while (node->leftNode != NULL) {
		node = node->leftNode;
	}
	fclose(fp);/********/
	printf("%d", node->streak);
	//for (i = node->streak - 1; i >= 0; i--) {
	//	printf("%d ", node->list[i]);
	//}
	free(array);
	freeMemTree(root);
	return 0;
}