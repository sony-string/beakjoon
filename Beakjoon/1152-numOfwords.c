#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int count = 0;
	char* str = (char*)malloc(1000002 * sizeof(char));
	fgets(str,1000002, stdin);
	int i,s,len;
	char lastch;
	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] != ' ') {
			s = i;
			break;
		}
	}
	lastch = str[s];
	if (lastch !='\n' && lastch !='\0') {
		for (i = s; i < len; i++) {
			if (str[i] == ' ') {
				count++;
			}
			else if (str[i] == '\n' || str[i] == '\0') {
				if (lastch != ' ')
					count++;
				break;
			}
			lastch = str[i];
		}
	}
	printf("%d", count);
	return 0;
}