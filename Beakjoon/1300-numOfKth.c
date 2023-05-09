#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int order, size;
	scanf("%d %d", &size, &order);
	int count = 0;
	int l, r, m, i;
	l = 0; r = order;
	while (l < r) {
		m = l + r;
		m /= 2;
		count = 0;
		for (i = 1; i <= size && m >= i; i++) {
			if (m / i > size) {
				count += size;
			}
			else {
				count += m / i;
			}
		}
		if (count < order) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}

	for (; ; r++) {
		for (i = 1; i <= size; i++) {
			if (r % i == 0 && r / i <= size) {
				break;
			}
		}
		if (i <= size) {
			break;
		}
	}
	printf("%d", r);
	return 0;
}