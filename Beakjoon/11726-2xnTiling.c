#include <stdio.h>

void divide(int length, int* records) {
	int count = 0;
	count += (records[length - 2] * 2) % 10007;
	count += (records[length - 3]) % 10007;
	records[length] = count % 10007;
}

int main() {
	int length;
	int records[1001];
	scanf("%d", &length);
	int i;
	for (i = 0; i < 1001; i++) {
		records[i] = -1;
	}
	records[0] = 0; records[1] = 1; records[2] = 2; records[3] = 3, records[4] = 5;
	for (i = 5; i < 1001; i++) {
		divide(i, records);
	}
	printf("%d", records[length]);
	return 0;
}