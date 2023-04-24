#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int index;
	long long value;
	struct Node* next;
} Node;

Node* addElement(Node* list, Node* node) {
	Node* cur, * pre;
	pre = NULL; cur = list;
	while (cur != NULL) {
		if (node->index < cur->index) {
			break;
		}
		pre = cur;
		cur = cur->next;
	}
	if (pre == NULL) {
		node->next = cur;
		return node;
	}
	if (pre->index == node->index) {
		pre->value = node->value;
		free(node);
		return list;
	}
	pre->next = node;
	node->next = cur;
	return list;
}

int main() {
	//FILE* fp = freopen("input.txt", "r", stdin);
	long long* prefixSum, * arr, result;
	Node* node, * changedNum;
	int sizeArr, numChanged, numSum;
	scanf("%d %d %d", &sizeArr, &numChanged, &numSum);
	prefixSum = (long long*)calloc(sizeArr, sizeof(long long));
	arr = (long long*)calloc(sizeArr, sizeof(long long));
	changedNum = (Node*)calloc(numChanged, sizeof(Node));

	int i, cmd;
	long long left, right;
	scanf("%lld", &arr[0]);
	prefixSum[0] = arr[0];
	for (i = 1; i < sizeArr; i++) {
		scanf("%lld", &arr[i]);
		prefixSum[i] = prefixSum[i - 1] + arr[i];
	}

	//system("cls");
	//for (i = 0; i < sizeArr; i++) {
	//	printf("%d : %lld / %lld\n", i + 1, arr[i], prefixSum[i]);
	//}
	
	for (i = 0; i < numChanged + numSum; i++) {
		scanf("%d %lld %lld", &cmd, &left, &right);
		left--;
		if (cmd == 1) {
			node = (Node*)calloc(1, sizeof(Node));
			node->index = left;
			node->value = right - arr[left];
			//printf("%d num is added by %lld\n", node->index + 1, node->value);
			changedNum = addElement(changedNum, node);
		}
		else {
			right--;
			if (left != 0) {
				result = prefixSum[right] - prefixSum[left - 1];
			}
			else {
				result = prefixSum[right];
			}
			node = changedNum;
			while (node != NULL) {
				if (right < node->index) {
					break;
				}
				if (left <= node->index) {
					result += node->value;
				}
				node = node->next;
			}
			printf("%lld\n", result);
		}
	}
	//fclose(fp);
	return 0;
}