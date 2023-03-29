#include <stdio.h>
#include <stdlib.h>

/* BFS 문제
bfs 중 visited 를 변경할때는, 해당 노드를 queue에 추가할 때 이다.
해당 문제 처럼 탐색 목표를 찾을때까지의 탐색 깊이를 반환하고 싶다면
push -> 이전에 푸시한 지점까지 pop (count++) -> push ... 방식을 써야하는데
이때 while 안에 for 가 있고, for에서 pop을 하게 된다
pop 을 for에서 하므로, 목표를 발견하고 break 하면 아직 while에선 빠져나가지 못한다
그러므로 for문 직후, for문 중간에 break로 빠져나왔는지 체크해야한다.

방법은 for문 조건문이 true 라면, 중간에 break로 나온 것을 확인할 수 있다 (여기선 r != endPop)
*/

int main() {
	int Subin, brother;
	int l = 0, r = 0, count = 0, endPop;
	int* nextPointqueue = (int*)malloc(300000 * sizeof(int));
	int* searched = (int*)calloc(100001 , sizeof(int));
	scanf("%d %d", &Subin, &brother);
	nextPointqueue[r] = Subin;
	r++;
	count = -1;
	while (r != l) {
		count++;
		endPop = r;
		for (; l < endPop; l++) {
			if (nextPointqueue[l] == brother) {
				break;
			}
			//printf("count %d : searching %d\n", count, nextPointqueue[l]);
			if (nextPointqueue[l] < 100000) {
				if (searched[nextPointqueue[l] + 1] == 0) {
					nextPointqueue[r] = nextPointqueue[l] + 1;
					searched[nextPointqueue[l] + 1] = 1;
					r++;
				}
				if (nextPointqueue[l] <= 50000) {
					if (searched[nextPointqueue[l] * 2] == 0) {
						nextPointqueue[r] = nextPointqueue[l] * 2;
						searched[nextPointqueue[l] * 2] = 1;
						r++;
					}
				}
			}
			if (nextPointqueue[l] > 0) {
				if (searched[nextPointqueue[l] - 1] == 0) {
					nextPointqueue[r] = nextPointqueue[l] - 1;
					searched[nextPointqueue[l] - 1] = 1;
					r++;
				}
			}
		}
		if (endPop != l) {
			break;
		}
	}
	printf("%d", count);
	free(nextPointqueue);
	free(searched);
	return 0;
}