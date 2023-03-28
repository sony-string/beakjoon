#include <stdio.h>

int l = 0, r = 0;

int pop(int *queue) {
	int item = queue[l];
	l++;
	return item;
}

void push(int *queue, int item) {
	queue[r] = item;
	r++;
}

int main() {
	int itemIndex, cases, numPrints, i, count, item;
	int maxWeight;
	int queue[1000];
	int weight[10];
	scanf("%d", &cases);
	
	for (i = 0; i < cases; i++) {
		scanf("%d %d", &numPrints, &itemIndex);
		l = 0; r = 0; maxWeight = 0;
		int j;
		for (j = 0; j < 10; j++) {
			weight[j] = 0;
		}
		for (r; r < numPrints; r++) {
			scanf("%d", &queue[r]);
			if (queue[r] > maxWeight) {
				maxWeight = queue[r];
			}
			weight[queue[r]]++;
		}
		count = 0;
		while (itemIndex >= l) {
			if (maxWeight > queue[l]) {
				//printf("objective print is in queue %d\n", itemIndex-l);
				push(queue, pop(queue));
				if (itemIndex < l) {
					itemIndex = r - 1;
				}
			}
			else {
				//printf("objective print is in queue %d\n", itemIndex-l);
				item = pop(queue);
				//printf("printing %d...\n", item);
				weight[item]--;
				if (weight[item] == 0) {
					for (j = item - 1; j > 0; j--) {
						if (weight[j] != 0) {
							maxWeight = j;
							break;
						}
					}
				}
				count++;
				if (itemIndex < l) {
					break;
				}
			}
		}
		printf("%d\n", count);
	}
	return 0;
}