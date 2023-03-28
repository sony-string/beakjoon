#include <stdio.h>
#include <stdlib.h>

int main() {
	int numberOfScores, i, max;
	double sum = 0.0;
	scanf("%d", &numberOfScores);
	int* scores = (int*)malloc(numberOfScores * sizeof(int));
	scanf("%d", &scores[0]);
	max = 0;
	for (i = 1; i < numberOfScores; i++) {
		scanf("%d", &scores[i]);
		if (scores[max] < scores[i])
			max = i;
	}
	for (i = 0; i < numberOfScores; i++)
		sum += 100.0 * (double)scores[i] / (double)scores[max];
	printf("%lf", sum / (double)numberOfScores);
	free(scores);
	return 0;
}