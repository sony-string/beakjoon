#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned long long result, num, i, * primeFactor;
	int top = 0, k;
	scanf("%llu", &num);
	result = num;
	primeFactor = (unsigned long long*)calloc(1000000, sizeof(unsigned long long));
	if (num % 2 == 0) {
		primeFactor[0] = 2;
		top++;
		while (num % 2 == 0) {
			num /= 2;
		}
	}
	for (i = 3; i * i <= result; i += 2) {
		if (num % i != 0) {
			continue;
		}
		for (k = 0; k < top; k++) {
			if (i % primeFactor[k] == 0) {
				break;
			}
		}
		if (k != top) {
			continue;
		}
		primeFactor[top] = i;
		top++;
		while (num % i == 0) {
			num /= i;
		}
	}

	if (num != 1) {
		primeFactor[top] = num;
		top++;
	}

	for (i = 0; i < top; i++) {
		result = (primeFactor[i] - 1) * (result /  primeFactor[i]);
	}

	printf("%llu", result);

	free(primeFactor);
	return 0;
}