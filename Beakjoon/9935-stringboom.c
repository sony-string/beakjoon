#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define fore(a, b) for (int i = a; i < b; i++)



char str[2][1000001];
int countTable[1000001];

int main() {
	char bomb[37];
	char jumpTable[37];
	int lenBomb;
	int len;
	int nextLen;
	int count;

	scanf("%s", str[0]);
	scanf("%s", bomb);
	lenBomb = strlen(bomb);

	jumpTable[0] = -1;
	int idxl = 0;
	count = -1;
	while (idxl < lenBomb) {
		while (count >= 0 && bomb[idxl] != bomb[count]) {
			count = jumpTable[count];
		}
		idxl++;
		count++;
		jumpTable[idxl] = count;
	}

	len = strlen(str[0]);
	nextLen = 0;
	count = -1;
	fore(0, len) {
		str[1][nextLen] = str[0][i];
		countTable[nextLen] = count;
		nextLen++;
		count++;
		if (str[0][i] == bomb[count]) {
			if (count == lenBomb - 1) {
				nextLen -= lenBomb;
				count = countTable[nextLen];
			}
			continue;
		}
		else {
			count = jumpTable[count];
			while (count >= 0 && str[0][i] != bomb[count]) {
				count = jumpTable[count];
			}
			continue;
		}
	}
	str[1][nextLen] = '\0';


	if (nextLen != 0) {
		printf("%s", str[1]);
	}
	else {
		printf("FRULA");
	}
	return 0;
}