#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

enum {
	D = 'D', S = 'S', L = 'L', R = 'R'
};


int main() {
	int cases;
	int num;
	int next;
	int goal;
	int visited[10000][2];
	int queue[20000];
	char str[10001];
	int top;
	int l, r;

	scanf("%d", &cases);
	for (int T = 0; T < cases; T++) {
		l = 0;
		r = 0;
		memset(visited, -1, sizeof(visited));
		scanf("%d %d", &num, &goal);
		queue[r] = num;
		visited[num][0] = num;
		r++;
		while (l < r) {
			num = queue[l];
			l++;
			next = (num * 2) % 10000;
			if (visited[next][0] == -1) {
				visited[next][0] = num;
				visited[next][1] = D;
				if (next == goal) {
					break;
				}
				queue[r] = next;
				r++;
			}

			next = num - 1;
			if (next == -1) {
				next = 9999;
			}
			if (visited[next][0] == -1) {
				visited[next][0] = num;
				visited[next][1] = S;
				if (next == goal) {
					break;
				}
				queue[r] = next;
				r++;
			}

			next = ((num % 1000) * 10) + (num / 1000);
			if (visited[next][0] == -1) {
				visited[next][0] = num;
				visited[next][1] = L;
				if (next == goal) {
					break;
				}
				queue[r] = next;
				r++;
			}

			next = (num % 10) * 1000 + (num / 10);
			if (visited[next][0] == -1) {
				visited[next][0] = num;
				visited[next][1] = R;
				if (next == goal) {
					break;
				}
				queue[r] = next;
				r++;
			}
		}

		top = 0;
		num = goal;
		while (visited[num][1] != -1) {
			str[top] = visited[num][1];
			top++;
			num = visited[num][0];
		}
		for (int i = top - 1; i >= 0; i--) {
			printf("%c", str[i]);
		}
		printf("\n");
	}
	return 0;
}