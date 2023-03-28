#include <stdio.h>

int main() {
	int scale[8];
	int i;
	for (i = 0; i < 8; i++) {
		scanf("%d", &scale[i]);
	}
	if (scale[0] == 1) {
		for (i = 1; i < 8; i++) {
			if (scale[i] == scale[i - 1] + 1) {
				if (i == 7)
					printf("ascending");
			}
			else {
				printf("mixed");
				break;
			}
		}
	}
	else if (scale[0] == 8) {
		for (i = 1; i < 8; i++) {
			if (scale[i] == scale[i - 1] - 1) {
				if (i == 7)
					printf("descending");
			}
			else {
				printf("mixed");
				break;
			}
		}
	}
	else {
		printf("mixed");
	}
	return 0;
}