#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	long long coef;
	long long expo;
	long long index;
	struct Node* leftNode;
	struct Node* rightNode;
	struct Node* parentNode;
} Node;

typedef struct LinkedList {
	long long value;
	struct LinkedList* next;
	struct LinkedList* pre;
} List;

typedef struct Heap {
	long long numNodes;
	Node* root;
	List* routeToLast;
} Heap;

void swap(long long* a, long long* b) {
	long long temp = *a;
	*a = *b;
	*b = temp;
}

void push(Heap* heap, Node* node) {
	Node* cur, * parent;
	List* route;
	heap->numNodes += 1;
	long long num = heap->numNodes;
	long long numNodes = heap->numNodes;
	long long index = 1;
	route = heap->routeToLast;
	while (num != 1) {
		route->value = num;
		if (route->next == NULL) {
			//현재 pop시 free안하므로 next 가 NULL이 아니면 calloc 필요없기는 하지만, pop하고 push하는 일 X
			route->next = (List*)calloc(1, sizeof(List));
			route->next->pre = route;
		}
		route = route->next;
		num /= 2;
	}
	cur = heap->root;
	route = route->pre;
	while (route->value != numNodes) {
		if (route->value == index * 2) {
			cur = cur->leftNode;
			route = route->pre;
			index = index * 2;
		}
		else {
			cur = cur->rightNode;
			route = route->pre;
			index = index * 2 + 1;
		}
	}
	if (numNodes == cur->index * 2) {
		cur->leftNode = node;
		node->parentNode = cur;
		node->index = numNodes;
	}
	else {
		cur->rightNode = node;
		node->parentNode = cur;
		node->index = numNodes;
	}
	cur = node;
	
	while (cur->parentNode != NULL) {
		parent = cur->parentNode;
		if (cur->expo > parent->expo) {
			swap(&cur->coef, &parent->coef);
			swap(&cur->expo, &parent->expo);
			cur = parent;
		}
		else {
			break;
		}
	}
}

Node* pop(Heap* heap) {
	if (heap->numNodes == 1) {
		heap->numNodes -= 1;
		return heap->root;
	}
	Node* cur, * left, * right, * max, * returnNode;
	List* route;
	long long num = heap->numNodes;
	long long numNodes = heap->numNodes;
	long long index = 1;
	route = heap->routeToLast;
	while (num != 1) {
		route->value = num;
		route = route->next;
		num /= 2;
	}
	cur = heap->root;
	route = route->pre;
	while (route->value != numNodes) {
		if (route->value == index * 2) {
			cur = cur->leftNode;
			route = route->pre;
			index = index * 2;
		}
		else {
			cur = cur->rightNode;
			route = route->pre;
			index = index * 2 + 1;
		}
	}
	if (numNodes == cur->index * 2) {
		cur = cur->leftNode;
	}
	else {
		cur = cur->rightNode;
	}
	swap(&cur->coef, &heap->root->coef);
	swap(&cur->expo, &heap->root->expo);
	returnNode = cur;
	cur = heap->root;
	heap->numNodes -= 1;
	numNodes--;

	while (cur->index * 2 + 1 <= numNodes) {
		left = cur->leftNode;
		right = cur->rightNode;
		if (left->expo > right->expo) {
			max = left;
		}
		else {
			max = right;
		}
		if (cur->expo < max->expo) {
			swap(&cur->expo, &max->expo);
			swap(&cur->coef, &max->coef);
			cur = max;
		}
		else {
			break;
		}
	}

	if (cur->index * 2 == numNodes) {
		max = cur->leftNode;
		if (cur->expo < max->expo) {
			swap(&cur->expo, &max->expo);
			swap(&cur->coef, &max->coef);
			cur = max;
		}
	}
	return returnNode;
}


int main() {
	FILE* fp = freopen("input.txt", "r", stdin);
	clock_t start, end;
	start = clock();
	//polynomial in heap
	Heap heap;
	Node* node;
	char ch;
	char* buffer;
	long long expo, coef;
	
	heap.numNodes = 1;
	heap.routeToLast = (List*)calloc(1, sizeof(List));
	heap.root = (Node*)calloc(1, sizeof(Node));
	heap.root->index = 1;

	if (scanf("%c", &ch) != EOF) {
		scanf("%lld,%lld)", &heap.root->coef, &heap.root->expo);
		node = (Node*)calloc(1, sizeof(Node));

		while (scanf("%c", &ch) != EOF) {
			if (ch != '(') {
				continue;
			}
			scanf("%lld,%lld)", &node->coef, &node->expo);
			push(&heap, node);
			node = (Node*)calloc(1, sizeof(Node));

		}
	}
	//free(node);
	buffer = (char*)malloc(heap.numNodes * 18 + 1);
	setvbuf(stdout, buffer, _IOFBF, heap.numNodes * 18 + 1);
	while (1) {
		node = pop(&heap);
		expo = node->expo; coef = node->coef;
		while (heap.root->expo == expo && heap.numNodes != 0) {
			node = pop(&heap);
			coef += node->coef;
		}
		printf("%lldx^%lld", coef, expo);
		if (heap.numNodes != 0) {
			printf(" + ");
			continue;
		}
		else {
			break;
		}
	}
	fflush(stdout);
	freopen("C:/Users/clc26/source/repos/Beakjoon/Release/output.txt", "w", stdout);
	end = clock();
	printf("\n%.5f sec", (double)((double)end - start) / CLOCKS_PER_SEC);
	fflush(stdout);
	fclose(fp);
	return 0;
}