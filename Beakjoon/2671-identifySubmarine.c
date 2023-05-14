#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int mask[150];
	char pattern[151];
	int len;
	int start;
	int index;

	scanf("%s", pattern);
	len = strlen(pattern);
	memset(mask, 0, 600);
	
	for (int i = 0; i < len - 2; i++) {
		if (pattern[i] == '1') {
			start = i;
			if (pattern[i + 1] == pattern[i + 2] && pattern[i + 1] == '0') {
				i += 3;
				while (pattern[i] == '0' && i < len) {
					i++;
				}
				if (i < len) {
					while (pattern[i] == '1') {
						i++;
					}
					memset(&mask[start], -1, (i - start) * sizeof(int));
					i--;
					if (pattern[i] == pattern[i - 1]) {
						i--;
					}
				}
				else {
					break;
				}
			}
		}
	}
	for (int i = 0; i < len - 1; i++) {
		if (mask[i] == mask[i + 1] && mask[i] == 0) {
			if (pattern[i] == '0' && pattern[i + 1] == '1') {
				mask[i] = -1;
				mask[i + 1] = -1;
				i++;
				continue;
			}
			break;
		}
	}
	for (index = 0; index < len; index++) {
		if (mask[index] == 0) {
			break;
		}
	}
	if (index < len) {
		printf("NOISE");
	}
	else {
		printf("SUBMARINE");
	}
	return 0;
}