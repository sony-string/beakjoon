#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;


const char start = 'A';
const char end = 'A';
bool* visited;
int** map;


bool flow(char vertex = 'A') {
	visited[vertex] = true;
	if (vertex == 'Z') {
		return true;
	}
	for (char i = 'A'; i <= 'z'; i++) {
		if (visited[i]) {
			continue;
		}
		else if (map[vertex][i] > 0) {
			if (flow(i)) {
				map[vertex][i]--;
				map[i][vertex]--;
				return true;
			}
		}
	}
	return false;
}


int main() {
	map = new int* ['z' + 1];
	for (int i = 0; i < 'z' + 1; i++) {
		map[i] = new int['z' + 1];
		memset(map[i], 0, sizeof(int) * ('z' + 1));
	}
	visited = new bool['z' + 1];
	memset(visited, false, sizeof(bool) * ('z' + 1));
	int N, cap, maxflow;
	char s, e;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %c %c %d", &s, &e, &cap);
		map[s][e] += cap;
		map[e][s] += cap;
	}

	maxflow = 0;
	while (flow()) {
		maxflow++;
		memset(visited, false, sizeof(bool) * ('z' + 1));
	}

	printf("%d", maxflow);
	return 0;
}