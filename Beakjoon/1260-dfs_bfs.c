#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int node;
	struct Node* nextNode;
} Node;

typedef struct Graph {
	Node* adjList;
	//int numVertices;
} Graph;

int insertEdge(Graph* graph, int src, int dst) {
	Node* dstNode = (Node*)malloc(sizeof(Node));
	Node* srcNode = (Node*)malloc(sizeof(Node));
	dstNode->node = dst;
	srcNode->node = src;
	dstNode->nextNode = NULL;
	srcNode->nextNode = NULL;
	
	Node* node = &(graph->adjList[src]);
	while (node->nextNode != NULL) {
		if (node->nextNode->node > dst) {
			break;
		}
		else if (node->nextNode->node == dst) {
			free(dstNode);
			free(srcNode);
			return 0;
		}
		node = node->nextNode;
	}
	dstNode->nextNode = node->nextNode;
	node->nextNode = dstNode;

	node = &(graph->adjList[dst]);
	while (node->nextNode != NULL) {
		if (node->nextNode->node > src) {
			break;
		}
		node = node->nextNode;
	}
	srcNode->nextNode = node->nextNode;
	node->nextNode = srcNode;
	
	return 1;
}

void createGraph(Graph* graph, int size) {
	//graph->numVertices = size;
	graph->adjList = (Node*)malloc(size * sizeof(Node));
	int i;
	for (i = 0; i < size; i++) {
		graph->adjList[i].node = i;
		graph->adjList[i].nextNode = NULL;
	}
}

void dfs(const Graph* graph, int vertex, int* visited) {
	if (visited[vertex] == 1) {
	}
	else {
		visited[vertex] = 1;
		Node* iteratorNode = graph->adjList[vertex].nextNode;
		printf("%d ", vertex);
		while (iteratorNode != NULL) {
			dfs(graph, iteratorNode->node, visited);
			iteratorNode = iteratorNode->nextNode;
		}
	}
}

int main() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	int numVertices, numEdges, startVertex;
	scanf("%d %d %d", &numVertices, &numEdges, &startVertex);
	createGraph(graph, numVertices+1);
	int src, dst, i;
	for (i = 0; i < numEdges; i++) {
		scanf("%d %d", &src, &dst);
		insertEdge(graph, src, dst);
	}
	int* visited = (int*)malloc((numVertices+1)*sizeof(int));
	for (i = 0; i < numVertices + 1; i++) {
		visited[i] = 0;
	}
	dfs(graph, startVertex, visited);

	for (i = 0; i < numVertices + 1; i++) {
		visited[i] = 0;
	}
	printf("\n");
	
	int* queue = (int*)malloc(numEdges * sizeof(int));
	int l = 0, r = 0;
	queue[r] = graph->adjList[startVertex].node;
	r++;
	while (l != r) {
		int vertex = queue[l];
		l++;
		Node* node = graph->adjList[vertex].nextNode;
		while (node != NULL) {
			if (visited[node->node] == 1) {
				node = node->nextNode;
				continue;
			}
			queue[r] = node->node;
			r++;
			node = node->nextNode;
		}
		if (visited[vertex] == 1) {
			continue;
		}
		visited[vertex] = 1;
		printf("%d ", vertex);
	}
	return 0;
}