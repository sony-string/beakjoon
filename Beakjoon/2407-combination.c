#include <stdio.h>
#include <stdlib.h>

void product(int num[100], int mul) {
	int i, success = 0;
	for (i = 0; i < 100; i++) {
		num[i] *= mul;
		num[i] += success;
		success = num[i] / 10;
		num[i] %= 10;
	}
}

void divide(int upper[100], int lower) {
	int i, temp = 0, count = 0;
	
	//for (i = 99; upper[i] == 0; i--) {}
	//for (; i >= 0; i--) {
	//	printf("%d", upper[i]);
	//}
	//printf(" / %d = ", lower);
	
	int* result = (int*)malloc(100 * sizeof(int));

	for (i = 99; upper[i] == 0; i--) {}
	for (; i >= 0; i--) {
		temp *= 10;
		temp += upper[i];
		if (temp >= lower) {
			result[count] = temp / lower;
			temp = temp % lower;
			//printf("%d", result[count]);
			count++;
		}
		else {
			result[count] = 0;
			//printf("%d", result[count]);
			count++;
		}
	}
	count--;
	for (i = 0; count >= 0; count--) {
		upper[i] = result[count];
		i++;
	}
	for (; i < 100; i++) {
		upper[i] = 0;
	}
	//printf("\n");
	free(result);
}

int main() {
	int pool, selection;
	int upperFraction[100];
	int i;
	for (i = 0; i < 100; i++) {
		upperFraction[i] = 0;
	}
	upperFraction[0] = 1;
	scanf("%d %d", &pool, &selection);
	if (pool == selection) {
		printf("1");
		return 0;
	}
	if (pool / 2 > selection) {
		selection = pool - selection;
	}
	for (i = pool; i > selection; i--) {
		product(upperFraction, i);
	}
	for (i = pool - selection; i >= 1; i--) {
		divide(upperFraction, i);
	}
	for (i = 99; upperFraction[i] == 0; i--) {}
	for (; i >= 0; i--) {
		printf("%d", upperFraction[i]);
	}
	return 0;
}