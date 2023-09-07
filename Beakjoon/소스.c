#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>


#ifndef MIN
#define MIN(a ,b) ((a) < (b) ? (a) : (b))
#endif

#define fore(a, b, c) for (int i = a; i < b; i += c)

typedef struct LowTable {
    int first, second;
} LowTable;

typedef struct stack {
    int size;
    int capacity;
    LowTable* arr;
} stack;

typedef struct Node {
    int degree;
    int capacity;
    int* edges;
} Node;

stack* new_stack(int cap) {
    stack* st = (stack*)malloc(sizeof(stack));
    st->arr = (LowTable*)malloc(sizeof(LowTable) * cap);
    st->capacity = cap;
    st->size = 0;
    return st;
}

stack* push(stack* st, LowTable lt) {
    if (st->capacity <= st->size) {
        int originCap = st->capacity;
        st->capacity = st->capacity * 2 + 10;
        st->arr = (LowTable*)realloc(st->arr, sizeof(LowTable) * st->capacity);
        assert(st->arr != NULL);
    }
    st->arr[st->size] = lt;
    st->size += 1;
    return st;
}

stack* pop(stack* st) {
    st->size -= 1;
    return st;
}

int empty(stack* st) {
    return st->size == 0;
}

LowTable* top(stack* st) {
    return &(st->arr[st->size - 1]);
}

LowTable make_pair(int a, int b) {
    LowTable lt;
    lt.first = a;
    lt.second = b;
    return lt;
}

Node* push_back(Node* vertex, int dst) {
    if (vertex->capacity <= vertex->degree) {
        vertex->capacity = vertex->capacity * 2 + 10;
        vertex->edges = (int*)realloc(vertex->edges, sizeof(int) * vertex->capacity);
        assert(vertex->edges != NULL);
    }
    vertex->edges[vertex->degree] = dst;
    vertex->degree += 1;
    return vertex;
}


int total = 0;


void findArticulationPoint(int* isArticul, Node* adjList, LowTable* lt, int s, stack* st) {
    int sDegree = 0;
    push(st, make_pair(s, 0));
    lt[s].first = 0;
    lt[s].second = 0;
    int* edges;
    int e, cur;
    int idx;
    int low = -1;
    int count = 1;

    while (!empty(st)) {
        cur = top(st)->first;
        idx = top(st)->second;
        if (lt[cur].first <= low && isArticul[cur] == 0) {
            isArticul[cur] = 1;
            total++;
        }
        lt[cur].second = MIN(lt[cur].second, low);

        pop(st);
        edges = adjList[cur].edges;

        while (idx < adjList[cur].degree) {
            e = adjList[cur].edges[idx];
            if (lt[e].first == -1) {
                lt[e].first = count;
                lt[e].second = lt[cur].first;
                count++;
                if (s == cur) {
                    sDegree++;
                }
                push(st, make_pair(cur, idx + 1));
                cur = e;
                idx = 0;
                continue;
            }
            else {
                lt[cur].second = MIN(lt[e].first, lt[cur].second);
            }
            idx++;
        }
        low = lt[cur].second;
    }

    if (sDegree < 2 && isArticul[s] == 1) {
        isArticul[s] = 0;
        total--;
    }
}


int main() {
    stack* st = new_stack(110);
    LowTable* lt;
    Node* adjList;
    int* aP;

    int numNodes, numEdges;
    int s, e;
    scanf("%d %d", &numNodes, &numEdges);

    lt = (LowTable*)malloc((numNodes + 1) * sizeof(LowTable));
    memset(lt, -1, (numNodes + 1) * sizeof(LowTable));
    adjList = (Node*)calloc(numNodes + 1, sizeof(Node));
    for (int i = 1; i <= numNodes; i++) {
        adjList[i].edges = (int*)malloc(1000 * sizeof(int));
        adjList[i].capacity = 1000;
    }
    aP = (int*)calloc(numNodes + 1, sizeof(int));


    fore(0, numEdges, 1) {
        scanf("%d %d", &s, &e);
        push_back(&adjList[s], e);
        push_back(&adjList[e], s);
    }

    fore(1, numNodes + 1, 1) {
        if (lt[i].first == -1) {
            findArticulationPoint(aP, adjList, lt, i, st);
        }
    }

    printf("%d\n", total);
    fore(1, numNodes + 1, 1) {
        if (aP[i] == 1) {
            printf("%d ", i);
        }
    }

    return 0;
}