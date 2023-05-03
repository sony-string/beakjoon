#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	unsigned long long search = 1;
	unsigned long long num[2], left, right;
	unsigned long long count[2] = { 0 , 0 };
	unsigned long long temp;
	int i;
	scanf("%llu %llu", num, num + 1);
	num[0] -= 1;
	
	for (i = 0; i < 2; i++) {
		for (search = 1; search <= num[i]; search <<= 1) {
			left = num[i] / (search << 1);
			right = search - 1;
			if (right == 0) {
				temp = search & num[i];
				if (temp == 0) {
					count[i] += left;
				}
				else {
					count[i] += left + 1;
				}
				continue;
			}
			else if (left == 0) {
				count[i] += num[i] - search + 1;
				continue;
			}
			else {
				temp = search & num[i];
				if (temp == 0) {
					count[i] += left * search;
				}
				else {
					count[i] += left * search;
					count[i] += (num[i] % search) + 1;
				}
				continue;
			}
		}
	}
	printf("%llu", count[1] - count[0]);
	return 0;
}