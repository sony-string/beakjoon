#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int numSushi, numTypes, numStreak, coupon;
	int left, right, count, best, deleted, added;
	int* belt, * selected;
	scanf("%d %d %d %d", &numSushi, &numTypes, &numStreak, &coupon);
	belt = (int*)malloc(numSushi * sizeof(int));
	selected = (int*)calloc(numTypes + 1, sizeof(int));
	int i;
	for (i = 0; i < numSushi; i++) {
		scanf("%d", belt + i);
	}

	left = 0;
	selected[coupon] = numSushi + 1;
	count = 1;
	best = 1;
	for (right = 0; right < numStreak; right++) {
		selected[belt[right]] += 1;
		if (selected[belt[right]] == 1) {
			count++;
			best++;
		}
	}
	right--;
	for (left = 1; left < numSushi; left++) {
		deleted = belt[left - 1];
		right++;
		if (right >= numSushi) {
			right = 0;
		}
		added = belt[right];
		selected[deleted] -= 1;
		selected[added] += 1;
		if (deleted != added) {
			if (selected[added] == 1) {
				count++;
			}
			if (selected[deleted] == 0) {
				count--;
			}
			if (count > best) {
				best = count;
			}
		}
	}

	printf("%d", best);
	return 0;
}