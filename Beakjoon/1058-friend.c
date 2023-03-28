#include <stdio.h>
#include <stdlib.h>

/*깊이 제한시
6

NYYNYN

YNYNNN

YYNYNN

NNYNNN

YNNNNY

NNNNYN

위와 같은 케이스에서 일반적인 DFS를 돌리면 '거리'개념과 다르기에
올바른 결과인 5가 아닌 4를 출력함
*/
int count2Friends(char** matrix, int person, int size, int depth, int* visited) {
	if (depth == 2) {
		if (visited[person] == 1) {
			return 0;
		}
		//printf("%d person is friend\n", person);
		visited[person] = 1;
		return 1;
	}
	else {
		if (visited[person] == 1) {
			int count = 0;
			int i;
			for (i = 0; i < size; i++) {
				if (matrix[person][i] == 'Y') {
					count += count2Friends(matrix, i, size, depth + 1, visited);
				}
			}
			return count;
		}
		else {
			//printf("%d person is friend\n", person);
			visited[person] = 1;
			int count = depth;
			int i;
			for (i = 0; i < size; i++) {
				if (matrix[person][i] == 'Y') {
					count += count2Friends(matrix, i, size, depth + 1, visited);
				}
			}
			return count;
		}
	}
}

int main() {
	int numPersons, i, j;
	int maxFriends = 0, num2friends;
	char** adjMatrix;

	scanf("%d", &numPersons);
	adjMatrix = (char**)malloc(numPersons*sizeof(char*));
	for (i = 0; i < numPersons; i++) {
		adjMatrix[i] = (char*)malloc(numPersons * sizeof(char));
		for (j = 0; j < numPersons; j++) {
			scanf(" %c", &adjMatrix[i][j]);
		}
	}
	//printf("\n");
	int* visited = (int*)calloc(numPersons, sizeof(int));
	for (i = 0; i < numPersons; i++) {
		//printf("\nLet's see %d Person\n", i);
		num2friends = count2Friends(adjMatrix, i, numPersons, 0, visited);
		if (num2friends > maxFriends) {
			maxFriends = num2friends;
		}
		for (j = 0; j < numPersons; j++) {
			visited[j] = 0;
		}
	}
	printf("%d", maxFriends);
	return 0;
}