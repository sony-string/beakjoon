#include <stdio.h>

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int i;
	for (N; N <= M; N++) {
		if (N <= 2) {
			if (N == 2) {
				printf("2\n");
			}
			continue;
		}
		else if (N % 2 != 0) {
			for (i = 3; i * i <= N; i++) {
				if (N % i == 0) {
					break;
				}
			}
			if (i * i > N) {
				printf("%d\n", N);
			}
		}
	}
	return 0;
}