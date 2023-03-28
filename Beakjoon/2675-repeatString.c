#include <stdio.h>
#include <string.h>

int main() {
	char str[21];
	int cases, i, j, k, repeat,len;
	scanf("%d", &cases);
	for (i = 0; i < cases; i++) {
		scanf("%d %s", &repeat, str);
		len = (int)strlen(str);
		for (j = 0; j < len; j++) {
			for (k = 0; k < repeat; k++) {
				printf("%c", str[j]);
			}
		}
		printf("\n");
	}
	return 0;
}