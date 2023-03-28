#include <stdio.h>
#include <stdlib.h>

int main() {
	int numTrees, neededWoods, gottenWoods;
	int maxHeight, goalHeight;
	int* tree;
	scanf("%d %d", &numTrees, &neededWoods);
	tree = (int*)malloc(numTrees * sizeof(int));
	int i;
	maxHeight = 0;
	for (i = 0; i < numTrees; i++) {
		scanf("%d", &tree[i]);
		if (tree[i] > maxHeight)
			maxHeight = tree[i];
	}
	int l = 0, r = maxHeight;
	while (1) {
		if (r - l < 2) {
			break;
		}
		goalHeight = (r + l) / 2;
		gottenWoods = 0;
		for (i = 0; i < numTrees; i++) {
			if (tree[i] > goalHeight)
				gottenWoods += tree[i] - goalHeight;
			if (gottenWoods < 0) {
				l = goalHeight;
				break;
			}
		}
		if (gottenWoods < 0)
			continue;
		if (gottenWoods > neededWoods) {
			l = goalHeight;
		}
		else if (gottenWoods == neededWoods) {
			break;
		}
		else if (gottenWoods < neededWoods) {
			r = goalHeight;
		}
	}
	if (gottenWoods == neededWoods)
		printf("%d", goalHeight);
	else {
		goalHeight = r;
		gottenWoods = 0;
		for (i = 0; i < numTrees; i++) {
			if (tree[i] > goalHeight)
				gottenWoods += tree[i] - goalHeight;
		}
		if (gottenWoods < neededWoods) {
			printf("%d", l);
		}
		else {
			printf("%d", r);
		}
	}
	free(tree);
	return 0;
}