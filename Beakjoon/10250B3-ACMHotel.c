#include <stdio.h>

int main() {
	int lines, H, W, N;
	scanf("%d", &lines);
	int i;
	for (i = 0; i < lines; i++) {
		scanf("%d %d %d", &H, &W, &N);
		if (N % H == 0) {
			printf("%d%02d", H, (N / H));
		}
		else {
			printf("%d%02d", N % H, (N / H) + 1);
		}
		printf("%n");
	}
	return 0;
}