#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	unsigned long long weight, temp;
	int count[10], number, digit = 1;
	int i, k, left, right, radix;
	memset(count, 0, 10 * sizeof(int));
	scanf("%d", &number);
	temp = 10;
	while (number / temp != 0) {
		temp *= 10;
		digit++;
	}
	weight = 10;
	for (i = 0; i < digit; i++) {
		left = number / weight;
		right = number % (weight / 10);
		radix = number / (weight / 10);
		radix %= 10;
		for (k = 0; k <= 9; k++) {
			if (k < radix) {
				if (i == 0) {
					count[k] += left + 1;
					if (k == 0) {
						count[0] -= 1;
					}
				}
				else if (i < digit - 1) {
					count[k] += (left + 1) * weight / 10;
					if (k == 0) {
						count[0] -= weight / 10;
					}
				}
				else {
					if (k == 0) {
						continue;
					}
					count[k] += weight / 10;
				}
			}
			else if (k == radix) {
				if (i == 0) {
					count[k] += left + 1;
					if (k == 0) {
						count[0] -= 1;
					}
				}
				else if (i < digit - 1) {
					count[k] += (left * weight / 10) + right + 1;
					if (k == 0) {
						count[0] -= weight / 10;
					}
				}
				else {
					count[k] += right + 1;
				}
			}
			else if (k > radix) {
				if (i == 0) {
					count[k] += left;
				}
				else if (i < digit - 1) {
					count[k] += left * weight / 10;
				}
				else {
					break;
				}
			}
		}
		weight *= 10;
	}
	for (i = 0; i < 10; i++) {
		printf("%d", count[i]);
		if (i != 9) {
			printf(" ");
		}
	}
	return 0;
}