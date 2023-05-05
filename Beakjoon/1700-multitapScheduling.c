#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	int numHoles, numUsing, plugged[101];
	int count = 0, work = 0, target;
	int ** schedule;
	int* queue;
	scanf("%d %d", &numHoles, &numUsing);

	schedule = (int**)malloc((numUsing + 1) * sizeof(int*));
	queue = (int*)malloc((numUsing) * sizeof(int));
	memset(plugged, 0, 101 * sizeof(int));
	for (int i = 0; i <= numUsing; i++) {
		schedule[i] = (int*)calloc((numUsing + 1), sizeof(int));
	}	

	for (int i = 0; i < numUsing; i++) {
		scanf("%d", &work);
		queue[i] = work;
		schedule[work][0] += 1;
		schedule[work][schedule[work][0]] = i;
	}
	for (int i = 0; i <= numUsing; i++) {
		schedule[i][0] = 1;
	}
	for (int i = 0; i < numUsing; i++) {
		work = queue[i];
		schedule[work][0]++;
		if (plugged[work] == 1) {
			continue;
		}
		else if (numHoles != 0) {
			plugged[work] = 1;
			numHoles--;
			continue;
		}
		target = 0;
		for (int j = 1; j <= 100; j++) {
			if (plugged[j] == 0 || j == work) {
				continue;
			}
			else if (target == 0) {
				target = j;
				if (schedule[j][schedule[j][0]] == 0) {
					break;
				}
				continue;
			}
			else {
				if (schedule[j][schedule[j][0]] == 0) {
					target = j;
					break;
				}
				else if (schedule[target][schedule[target][0]] < schedule[j][schedule[j][0]]) {
					target = j;
				}
			}
		}
		plugged[work] = 1;
		plugged[target] = 0;
		count++;
	}

	printf("%d", count);
	return 0;
}