#include <stdio.h>
#include <string.h>

int main() {
	int cases, i, j, combo, score, len;
	char test[81];
	scanf("%d", &cases);
	for (i = 0; i < cases; i++) {
		combo = 1; score = 0;
		scanf("%s", test);
		len = (int)strlen(test);
		for (j = 0; j < len; j++) {
			if (test[j] == 'O') {
				score += combo;
				combo++;
			}
			else {
				combo = 1;
			}
		}
		printf("%d\n", score);
	}
	return 0;
}