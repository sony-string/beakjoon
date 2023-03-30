#include <stdio.h>

int divide(const int num, int* factorial) {
	int numThrees = 0, numTwos = 0, numOnes =0 ;
	int leftNum, count = 0;
	int overlapedNum;
	for (numThrees = 0; num - (3 * numThrees) >= 0; numThrees++) {
		leftNum = num - 3 * numThrees;
		for (numTwos = 0; leftNum - (2 * numTwos) >= 0; numTwos++) {
			numOnes = leftNum - (2 * numTwos);
			overlapedNum = 1;
			overlapedNum *= factorial[numThrees];
			overlapedNum *= factorial[numTwos];
			overlapedNum *= factorial[numOnes];
			count += factorial[numOnes + numTwos + numThrees] / overlapedNum;
		 }
	}
	return count;
}

int main() {
	int factorial[11];
	factorial[1] = 1; factorial[0] = 1;
	int num, i, numT;
	for (i = 2; i < 11; i++) {
		factorial[i] = factorial[i - 1] * i;
	}
	scanf("%d", &numT);
	for (i = 0; i < numT; i++) {
		scanf("%d", &num);
		printf("%d\n", divide(num, factorial));
	}
	return 0;
}