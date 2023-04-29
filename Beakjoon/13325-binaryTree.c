#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	int* tree;
	int* edge;
	int level, numNodes, left, right;
	long long sum;
	scanf("%d", &level);
	numNodes = pow(2, level + 1) - 1;
	tree = (int*)calloc(numNodes, sizeof(int));
	edge = (int*)calloc(numNodes, sizeof(int));
	int i, k, temp;
	
	for (i = 1; i < numNodes; i++) {
		scanf("%d", &edge[i]);
	}
	for (i = pow(2, level - 1); i > 0; i >>= 1) {
		temp = (i << 1) - 1;
		for (k = i - 1; k < temp; k++) {
			left = k * 2 + 1;
			right = k * 2 + 2;
			if (tree[left] + edge[left] < tree[right] + edge[right]) {
				edge[left] = tree[right] - tree[left] + edge[right];
				//printf("edge to %d is now %d\n", left, edge[left]);
			}
			else if (tree[left] + edge[left] > tree[right] + edge[right]) {
				edge[right] = tree[left] - tree[right] + edge[left];
				//printf("edge to %d is now %d\n", right, edge[right]);
			}
			tree[k] = edge[left] + tree[left];
		}
	}
	left = 1; right = 2;
	if (tree[left] + edge[left] < tree[right] + edge[right]) {
		edge[left] = tree[right] - tree[left] + edge[right];
		//printf("edge to %d is now %d\n", left, edge[left]);
	}
	else if (tree[left] + edge[left] > tree[right] + edge[right]) {
		edge[right] = tree[left] - tree[right] + edge[left];
		//printf("edge to %d is now %d\n", right, edge[right]);
	}
	tree[0] = edge[left] + tree[left];

	sum = 0;
	for (i = 1; i < numNodes; i++) {
		sum += edge[i];
	}
	printf("%d", sum);

	return 0;
}