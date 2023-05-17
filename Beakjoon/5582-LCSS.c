#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char str[2][4001];
	int leng[2];
	int compare;
	int streak;
	int best = 0;
	int select = 0;
	int other;
	int common;
	int s[2];
	
	scanf("%s %s", str, str + 1);
	leng[0] = strlen(str[0]);
	leng[1] = strlen(str[1]);
	select = leng[0] < leng[1] ? 0 : 1;
	other = (select + 1) % 2;
	
	s[select] = leng[select] - 1;
	s[other] = 0;
	best = 0;
	common = 1;
	while (s[other] < leng[other]) {
		streak = 0;
		for (compare = 0; compare < common; compare++) {
			if (str[select][s[select] + compare] == str[other][s[other] + compare]) {
				streak++;
				if (streak > best) {
					best = streak;
				}
				continue;
			}
			else {
				streak = 0;
				continue;
			}
		}
		if (s[select] > 0) {
			s[select]--;
			common++;
			continue;
		}
		else if (s[other] + common < leng[other]) {
			s[other]++;
			continue;
		}
		else {
			s[other]++;
			common--;
		}
	}
	printf("%d", best);
	return 0;
}