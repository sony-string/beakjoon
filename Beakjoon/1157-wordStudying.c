#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *word = (char*)malloc(1000001);
	int count[128];
	scanf("%s", word);
	
	int len = strlen(word);
	int i;
	for (i = 0; i < 128; i++) {
		count[i] = 0;
	}
	for (i = 0; i < len; i++) {
		if (word[i] >= 97) {
			count[(int)word[i] - 32] ++;
		}
		else {
			count[(int)word[i]] ++;
		}
	}
	int firstFrequency = 65, secondFrequency = 66;
	for (i = 66; i < 91; i++) {
		if (count[i] >= count[secondFrequency]) {
			secondFrequency = i;
			if (count[i] >= count[firstFrequency]) {
				secondFrequency = firstFrequency;
				firstFrequency = i;
			}
		}
	}
	if (count[firstFrequency] == count[secondFrequency]) {
		printf("?");
	}
	else {
		printf("%c", firstFrequency);
	}
	free(word);
	return 0;
}