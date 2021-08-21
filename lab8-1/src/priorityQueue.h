#ifndef LAB8_1_PRIORITYQUEUE_H
#define LAB8_1_PRIORITYQUEUE_H

#include "stdio.h"

typedef struct PQNode {
    int vertex;
    int weight;
} PQNode;

typedef struct PriorityQ {
    int size;
    int capacity;
    PQNode * heap;
} PriorityQ;

PriorityQ * createPriorityQ(int capacity);
void cleanPriorityQ(PriorityQ * pq);
void createPQNode(int vertex, int weight, PriorityQ * pq, short * indInPQ);
void enqueue(PriorityQ * pq, int vertex, int weight, short * indInPQ);
PQNode dequeue(PriorityQ * pq, short * indInPQ);
void heapify(PriorityQ * pq, int i, int N, short * indInPQ);
void increaseNode(PriorityQ * pq, short i, short * indInPQ);

#endif //LAB8_1_PRIORITYQUEUE_H
