#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

typedef struct Node {
    int value;
    int sum;
    struct Node* nextRoute;
    struct Node* nextNode;
} Node;

int putNumber(Node* adjList) {
    Node* cur = &adjList[1], * pre = &adjList[1];
    while (cur->nextNode != NULL) {
        pre = cur;
        cur = &adjList[cur->nextRoute->value];
        pre->nextRoute = pre->nextRoute->nextNode;
        if (pre->nextRoute == NULL) {
            pre->nextRoute = pre->nextNode;
        }
    }
    return pre->value;
}

int* solve(int* depth, int* order, const Node* tree, const int target[], int num) {
    *depth += 1;
    int next, best = INT_MAX, thisDepth = *depth;
    int i, k;
    int* result = NULL, * temp;
    int* newOrder = calloc(*depth, sizeof(int));
    Node* newTree = (Node*)calloc(tree[0].value + 1, sizeof(Node));
    memcpy(newTree, tree, (tree[0].value + 1) * sizeof(Node));
    if (order != NULL) {
        memcpy(newOrder, order, (*depth - 1) * sizeof(int));
    }
    newOrder[*depth - 1] = num;

    next = putNumber(newTree);
    newTree[next].sum += num;
    if (newTree[next].sum > target[next - 1]) {
        free(newTree);
        free(newOrder);
        return NULL;
    }
    else if (newTree[next].sum == target[next - 1]) {
        for (i = 1; i <= tree[0].value; i++) {
            if (newTree[i].sum != target[i - 1]) {
                break;
            }
        }
        if (i == tree[0].value + 1) {
            free(newTree);
            return newOrder;
        }
    }

    for (i = 1; i <= 3; i++) {
        *depth = thisDepth;
        temp = solve(depth, newOrder, newTree, target, i);
        if (temp == NULL) {
            continue;
        }
        if (result == NULL) {
            result = temp;
            best = *depth;
        }
        else {
            if (best < *depth) {
                free(result);
                result = temp;
            }
            else if (best == *depth) {
                for (k = thisDepth; k < *depth; k++) {
                    if (temp[k] < result[k]) {
                        break;
                    }
                }
                if (k != *depth) {
                    free(result);
                    result = temp;
                }
                else {
                    free(temp);
                }
            }
            else {
                free(temp);
            }
        }
    }
    free(newTree);
    free(newOrder);
    return result;
}

void freeAdjList(Node* adjList) {
    Node* cur, * next;
    int i;
    for (i = 0; i <= adjList[0].value; i++) {
        cur = &adjList[i];
        next = cur->nextNode;
        while (next != NULL) {
            cur = next;
            next = next->nextNode;
            free(cur);
        }
    }
    free(adjList);
}

// edges_rows는 2차원 배열 edges의 행 길이, edges_cols는 2차원 배열 edges의 열 길이입니다.
// target_len은 배열 target의 길이입니다.
int* solution(int** edges, size_t edges_rows, size_t edges_cols, int target[], size_t target_len) {
    int* answer;
    int* result, * temp;
    Node* adjList = (Node*)calloc(target_len, sizeof(Node));
    Node* node, * cur, * pre;
    int parent, child;
    int* order = NULL;
    size_t i, k, depth = 0, best = INT_MAX;
    for (i = 1; i <= target_len; i++) {
        adjList[i].value = i;
    }
    adjList[0].value = target_len;

    for (i = 0; i < edges_rows; i++) {
        parent = edges[i][0];
        child = edges[i][1];
        pre = &adjList[parent];
        cur = adjList[parent].nextNode;
        while (cur != NULL) {
            if (cur->value > child) {
                break;
            }
            pre = cur;
            cur = cur->nextNode;
        }
        node = (Node*)calloc(1, sizeof(Node));
        node->value = child;
        pre->nextNode = node;
        node->nextNode = cur;
    }

    for (i = 0; i <= target_len; i++) {
        adjList[i].nextRoute = adjList[i].nextNode;
    }

    result = NULL;
    for (i = 1; i <= 3; i++) {
        depth = 0;
        temp = solve(&depth, order, adjList, target, i);
        if (temp == NULL) {
            continue;
        }
        if (result == NULL) {
            result = temp;
            best = depth;
        }
        else {
            if (best < depth) {
                free(result);
                result = temp;
            }
            else if (best == depth) {
                for (k = 0; k < depth; k++) {
                    if (temp[k] < result[k]) {
                        break;
                    }
                }
                if (k != depth) {
                    free(result);
                    result = temp;
                }
                else {
                    free(temp);
                }
            }
            else {
                free(temp);
            }
        }
    }
    if (best == INT_MAX) {
        freeAdjList(adjList);
        answer = (int*)malloc(sizeof(int));
        answer[0] = -1;
        return answer;
    }

    answer = (int*)malloc(best * sizeof(int));
    memcpy(answer, result, best * sizeof(int));
    return answer;
}

//int* solution(int** edges, size_t edges_rows, size_t edges_cols, int target[], size_t target_len)

int main() {
    int** edges, target[10];
    int* result;
    size_t target_len = 10, edges_rows = 9, edges_cols = 2;
    int i;
    edges = (int**)malloc(edges_rows * sizeof(int*));
    for (i = 0; i < 9; i++) {
        edges[i] = (int*)malloc(edges_cols * sizeof(int));
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }
    result = solution(edges, edges_rows, edges_cols, target, target_len);
    return 0;
}