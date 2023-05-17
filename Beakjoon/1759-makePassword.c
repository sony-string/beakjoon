#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
	char l = *(char*)a;
	char r = *(char*)b;
	if (l > r) {
		return 1;
	} else{
		return -1;
	}
}

int isVowel(char ch) {
	if (ch == 'a' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'e') {
		return 1;
	}
	return 0;
}

int main() {
	int numChars;
	int len;
	char chars[16];
	char password[16];
	scanf("%d %d", &len, &numChars);
	for (int i = 0; i < numChars; i++) {
		scanf(" %c", chars + i);
	}

	qsort(chars, numChars, 1, compare);
	int i;
	int count;
	int vowels;
	int consonant;
	int stack[16];
	vowels = 0;
	consonant = 0;
	count = 0;
	i = 0;
	password[len] = '\0';
	while (count >= 0) {
		if (count == len) {
			if (vowels > 0 && consonant >= 2) {
				printf("%s\n", password);
			}
			count--;
			if (isVowel(password[len - 1])) {
				vowels--;
			} else {
				consonant--;
			}
			i = stack[count] + 1;
		}
		if (i == numChars) {
			count--;
			if (isVowel(password[count])) {
				vowels--;
			} else{
				consonant--;
			}
			i = stack[count] + 1;
			continue;
		}
		password[count] = chars[i];
		stack[count] = i;
		if (isVowel(chars[i])) {
			vowels++;
		}
		else {
			consonant++;
		}
		count++;
		i++;
	}
	return 0;
}