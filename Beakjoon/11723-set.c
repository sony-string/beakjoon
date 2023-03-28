#include <stdio.h>
#include <string.h>

int main() {
	int numLines;
	int set[21];
	char cmd[7];
	scanf("%d", &numLines);
	int L, i, num;
	for (i = 0; i < 21; i++) {
		set[i] = 0;
	}
	for (L = 0; L < numLines; L++) {
		scanf("%s", cmd);
		if (strcmp(cmd, "add") == 0) {
			scanf("%d", &num);
			set[num] = 1;
			continue;
		}
		if (strcmp(cmd, "remove") == 0) {
			scanf("%d", &num);
			set[num] = 0;
			continue;
		}
		if (strcmp(cmd, "check") == 0) {
			scanf("%d", &num);
			printf("%d\n", set[num]);
			continue;
		}
		if (strcmp(cmd, "toggle") == 0) {
			scanf("%d", &num);
			if (set[num] == 1) {
				set[num] = 0;
				continue;
			}
			set[num] = 1;
			continue;
		}
		if (strcmp(cmd, "all") == 0) {
			for (i = 1; i <= 20; i++) {
				set[i] = 1;
			}
			continue;
		}
		if (strcmp(cmd, "empty") == 0) {
			for (i = 1; i <= 20; i++) {
				set[i] = 0;
			}
			continue;
		}
	}
	return 0;
}