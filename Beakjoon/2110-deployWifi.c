#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int compare(const void* a, const void* b) {
	int l = *(int*)a;
	int r = *(int*)b;
	if (l > r) {
		return 1;
	}
	else {
		return -1;
	}
}

int getPos(int* arr, int start, int end, int dist) {
	int upper;
	int l = start, m, r = end;
	upper = end + 1;
	
	while (l <= r) {
		m = l + r;
		m /= 2;
		if (arr[m] - arr[start - 1] > dist) {
			upper = m;
			r = m - 1;
		}
		else if (dist == arr[m] - arr[start - 1]) {
			return m;
		}
		else {
			l = m + 1;
		}
	}

	return upper;
}


int main() {
	int* posArr;
	int numHome, numWifi;
	int dist;
	int l, m, r;
	int count;
	int index;


	scanf("%d %d", &numHome, &numWifi);
	posArr = (int*)malloc(numHome * sizeof(int));
	for (int i = 0; i < numHome; i++) {
		scanf("%d", posArr + i);
	}
	qsort(posArr, numHome, sizeof(int), &compare);
	
	index = 1;
	count = 1;
	dist = posArr[numHome - 1] - posArr[0];
	dist /= numWifi - 1;
	l = 1; r = dist;

	while (l <= r) {
		index = 1;
		count = 1;
		m = l + r;
		m /= 2;
		while (count < numWifi) {
			index = getPos(posArr, index, numHome - 1, m) + 1;
			if (index > numHome) {
				index = 1;
				count = 1;
				break;
			}
			count++;
		}
		if (count < numWifi) {
			r = m - 1;
		}
		else {
			dist = m;
			l = m + 1;
		}
	}
	printf("%d", dist);
	return 0;
}