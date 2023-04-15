#include <stdio.h>
#include <stdlib.h>

#ifndef INT_MAX
#define INT_MAX 2140000000
#endif

typedef struct Building {
	int node;
	int buildTimes;
	int hasRequirement;
	struct Building* nextBuilding;
} Building;

void getTimeTable(int* timeTable, const Building* adjList, int node) {
	int time = 0;
	const Building* nodep = &adjList[node];
	while (nodep->nextBuilding != NULL) {
		if (adjList[nodep->nextBuilding->node].hasRequirement == 0) {
			if (adjList[nodep->nextBuilding->node].buildTimes > time) {
				time = adjList[nodep->nextBuilding->node].buildTimes;
			}
			nodep = nodep->nextBuilding;
			continue;
		}
		if (timeTable[nodep->nextBuilding->node] == INT_MAX) {
			getTimeTable(timeTable, adjList, nodep->nextBuilding->node);
		}
		if (timeTable[nodep->nextBuilding->node] > time) {
			time = timeTable[nodep->nextBuilding->node];
		}
		nodep = nodep->nextBuilding;
	}
	timeTable[node] = time + adjList[node].buildTimes;
}

int main() {
	int numTestCases, numBuildings, numBuildOrders, src, dst, goal;
	int* timeTable;
	Building* adjList, * nodep;
	scanf("%d", &numTestCases);
	int i, T;
	for (T = 0; T < numTestCases; T++) {
		scanf("%d %d", &numBuildings, &numBuildOrders);
		timeTable = (int*)calloc(numBuildings, sizeof(int));
		adjList = (Building*)calloc(numBuildings, sizeof(Building));

		for (i = 0; i < numBuildings; i++) {
			scanf("%d", &adjList[i].buildTimes);
			adjList[i].node = i;
			timeTable[i] = INT_MAX;
		}
		for (i = 0; i < numBuildOrders; i++) {
			scanf("%d %d", &dst, &src);
			dst--; src--;
			if (adjList[src].nextBuilding == NULL) {
				adjList[src].hasRequirement = 1;
			}
			nodep = &adjList[src];
			while (nodep->nextBuilding != NULL) {
				nodep = nodep->nextBuilding;
			}
			nodep->nextBuilding = (Building*)calloc(1, sizeof(Building));
			nodep->nextBuilding->node = dst;
		}
		for (i = 0; i < numBuildings; i++) {
			if (adjList[i].hasRequirement == 0) {
				timeTable[i] = adjList[i].buildTimes;
			}
		}
		scanf("%d", &goal);
		goal--;
		getTimeTable(timeTable, adjList, goal);
		printf("%d\n", timeTable[goal]);

		free(timeTable);
		free(adjList);
	}

	return 0;
}