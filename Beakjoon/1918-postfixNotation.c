#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void insertChar(char* str, char ch, int index) {
	int len = strlen(str);
	int i;
	for (i = len + 1; i > index; i--) {
		str[i] = str[i - 1];
	}
	str[index] = ch;
}

int main() {
	char* stackOperator, * expressionStr;
	stackOperator = (char*)malloc(MAX * sizeof(char));
	expressionStr = (char*)malloc(5 * MAX * sizeof(char));

	int lastStack = 0, len, bracketStack;
	scanf("%s", expressionStr);
	len = strlen(expressionStr);

	int i, k;
	for (i = 0; expressionStr[i] != '\0'; i++) {
		if (expressionStr[i] == '/' || expressionStr[i] == '*') {
			bracketStack = 0;
			for (k = i - 1; k > 0; k--) {
				if (expressionStr[k] == ')') {
					bracketStack++;
					continue;
				}
				if (expressionStr[k] == '(') {
					bracketStack--;
				}
				if (bracketStack == 0) {
					break;
				}
			}
			insertChar(expressionStr, '(', k);
			//printf("%s\n", expressionStr);
			i++;
			bracketStack = 0;
			for (k = i + 1; expressionStr[k] != '\0'; k++) {
				if (expressionStr[k] == '(') {
					bracketStack++;
					continue;
				}
				if (expressionStr[k] == ')') {
					bracketStack--;
				}
				if (bracketStack == 0) {
					break;
				}
			}
			insertChar(expressionStr, ')', k + 1);
			//printf("%s\n\n", expressionStr);
		}
	}
	for (i = 0; expressionStr[i] != '\0'; i++) {
		if (expressionStr[i] == '+' || expressionStr[i] == '-') {
			bracketStack = 0;
			for (k = i - 1; k > 0; k--) {
				if (expressionStr[k] == ')') {
					bracketStack++;
					continue;
				}
				if (expressionStr[k] == '(') {
					bracketStack--;
				}
				if (bracketStack == 0) {
					break;
				}
			}
			insertChar(expressionStr, '(', k);
			//printf("%s\n", expressionStr);
			i++;
			bracketStack = 0;
			for (k = i + 1; expressionStr[k] != '\0'; k++) {
				if (expressionStr[k] == '(') {
					bracketStack++;
					continue;
				}
				if (expressionStr[k] == ')') {
					bracketStack--;
				}
				if (bracketStack == 0) {
					break;
				}
			}
			insertChar(expressionStr, ')', k + 1);
			//printf("%s\n\n", expressionStr);
		}
	}

	
	for (i = 0; expressionStr[i] != '\0'; i++) {
		if (expressionStr[i] >= 65) {
			printf("%c", expressionStr[i]);
			continue;
		}
		if (expressionStr[i] >= 65) {
			printf("%c", expressionStr[i]);
			continue;
		}
		if (expressionStr[i] >= 42 || expressionStr[i] == '(') {
			stackOperator[lastStack] = expressionStr[i];
			lastStack++;
			continue;
		}
		if (expressionStr[i] == ')') {
			lastStack--;
			if (stackOperator[lastStack] == '(') {
				continue;
			}
			printf("%c", stackOperator[lastStack]);
			lastStack--;
		}
	}
	free(expressionStr);
	free(stackOperator);
	return 0;
}