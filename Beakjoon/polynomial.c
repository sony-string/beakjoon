#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	long long expo;
	long long coef;
	int color;
	struct TreeNode* leftNode;
	struct TreeNode* rightNode;
	struct TreeNode* parentNode;
} TreeNode;

enum {
	red, black
};

TreeNode* handleDoubledColor(TreeNode*);

TreeNode* findPreviousNode(TreeNode* node) {
	TreeNode* parentNode = node->parentNode;
	TreeNode* cur = node->leftNode;

	if (parentNode != NULL) {
		while (parentNode->parentNode != NULL && parentNode->expo > node->expo) {
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
			if (parentNode->expo < node->expo) {
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

//red-black tree insert : always return root node
TreeNode* insert(TreeNode* root, TreeNode* node) {
	TreeNode* cur = root;
	TreeNode* previous = root;
	while (cur != NULL) {
		previous = cur;
		if (cur->expo < node->expo) {
			cur = cur->rightNode;
			continue;
		}
		else if (cur->expo > node->expo) {
			cur = cur->leftNode;
			continue;
		}
		else if (cur->expo == node->expo) {
			cur->coef += node->coef;
			//free(node)
			return root;
		}
	}
	if (previous->expo < node->expo) {
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
	clock_t start, end;
	start = clock();

	FILE* fp = freopen("input.txt", "r", stdin);
	TreeNode* polynomial, * node;
	char ch;
	int count = 0;
	polynomial = (TreeNode*)calloc(1, sizeof(TreeNode));

	/*
	입력 데이터 처리 (다항식 덧셈 연산 포함)
	계수가 0인 항은 유지 (노드 삭제 비용이 큼에 비해 얻는 이득이 없음)
	*/
	if (scanf("%c", &ch) != EOF) {
		scanf("%lld,%lld)", &polynomial->coef, &polynomial->expo);
		polynomial->color = black;
		node = (TreeNode*)calloc(1, sizeof(TreeNode));
		count++;

		while (scanf("%c", &ch) != EOF) {
			if (ch != '(') {
				continue;
			}
			scanf("%lld,%lld)", &node->coef, &node->expo);
			node->color = red;
			polynomial = insert(polynomial, node);
			node = (TreeNode*)calloc(1, sizeof(TreeNode));
			count++;
		}
	}
	//free(node);



	/*
	빠른 표준 출력을 위한 버퍼링
	버퍼의 기본 크기는 20 * (항의 개수) byte 이나, 할당 실패시 계수를 줄여가며 할당 재시도
	*/
	/*
	char* buffer;
	i = 20;
	buffer = (char*)malloc(count *  i);
	for (; i >= 0 && buffer == NULL; i--) {
		buffer = (char*)malloc(count *  i);
		if (buffer != NULL) {
			break;
		}
	}
	setvbuf(stdout, buffer, _IOFBF, count * 18);
	*/


	/*
	표준 출력을 파일 출력으로 redirecting
	*/
	//freopen("output.txt", "w", stdout);

	/*
	연산 결과 다항식 출력
	*/
	node = polynomial;
	while (node->rightNode != NULL) {
		node = node->rightNode;
	}
	while (node->coef == 0) {
		node = findPreviousNode(node);
		if (node == NULL) {
			break;
		}
	}
	if (node != NULL) {
		if (node->coef < 0) {
			//printf(" - ");
			//printf("%lldx^%lld", -1 * node->coef, node->expo);
		}
		else {
			//printf("%lldx^%lld", node->coef, node->expo);
		}
		node = findPreviousNode(node);
		if (node != NULL) {
			while (node->coef == 0) {
				node = findPreviousNode(node);
				if (node == NULL) {
					break;
				}
			}
		}
	}
	if (node != NULL) {
		while (1) {
			if (node->coef < 0) {
				//printf(" - ");
				//printf("%lldx^%lld", -1 * node->coef, node->expo);
			}
			else {
				//printf(" + ");
				//printf("%lldx^%lld", node->coef, node->expo);
			}
			node = findPreviousNode(node);
			if (node == NULL) {
				break;
			}
			while (node->coef == 0) {
				node = findPreviousNode(node);
				if (node == NULL) {
					break;
				}
			}
			if (node == NULL) {
				break;
			}
		}
	}
	//fflush(stdout);
	end = clock();
	printf("\n%.5f sec", (double)(end - start) / CLOCKS_PER_SEC);
	fclose(fp);
	/*
	프로그램이 종료되며 메모리 반환이 되므로
	직접 반환해줄 필요성 없음
	*/
	//freeMemTree(polynomial)
	fflush(stdout);
	return 0;
}