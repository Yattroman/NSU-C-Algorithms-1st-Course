#include "priorityQueue.h"
#include "stdio.h"
#include "malloc.h"

PriorityQ * createPriorityQ(int capacity){
    PriorityQ * pq = (PriorityQ*)malloc(sizeof(PriorityQ));
    PQNode * heap = (PQNode*)malloc(sizeof(PQNode)*(capacity+1));
    pq->size = 0;
    pq->capacity = capacity;
    pq->heap = heap;
    return pq;
}

void createPQNode(int vertex, int weight, PriorityQ * pq, short * indInPQ){
    int inIndex = pq->size;
    PQNode pqNode;
    pqNode.vertex = vertex;
    pqNode.weight = weight;

    *(pq->heap + inIndex) = pqNode;
    ++pq->size;

    *(indInPQ + vertex) = inIndex;
}

void swap(PQNode *a, PQNode *b){
    PQNode box = *b;
    *b = *a;
    *a = box;
}

void heapify(PriorityQ * pq, int i, int N, short * indInPQ){
    int root = i;
    int leftChild = i*2+1;
    int rightChild = i*2+2;
    PQNode rootNode = *(pq->heap+root);
    int constRootVertex = rootNode.vertex;

    if(leftChild < N){
        PQNode lcNode = *(pq->heap+leftChild);
        if(lcNode.weight < rootNode.weight){
            root = leftChild;
            rootNode = *(pq->heap+root);
            *(indInPQ + lcNode.vertex) = i;
            *(indInPQ + constRootVertex) = root;
        }
    }
    if(rightChild < N){
        PQNode rcNode = *(pq->heap+rightChild);
        if(rcNode.weight < rootNode.weight){
            root = rightChild;
            *(indInPQ + rcNode.vertex) = i;
            *(indInPQ + rootNode.vertex) = root;
        }
    }
    if(root != i){
        swap( &(pq->heap[i]), &(pq->heap[root]) );
        heapify(pq, root, pq->size, indInPQ);
    }
}

void increaseNode(PriorityQ * pq, short i, short * indInPQ){
    while( (i+1)/2 > 0 && pq->heap[(i+1)/2-1].weight > pq->heap[i].weight){
        *(indInPQ + pq->heap[(i+1)/2-1].vertex) = i;
        *(indInPQ + pq->heap[i].vertex) = (i+1)/2-1;
        swap( &(pq->heap[(i+1)/2-1]), &(pq->heap[i]) );
        i = (i+1)/2-1;
    }
}

void enqueue(PriorityQ * pq, int vertex, int weight, short * indInPQ){
    if(pq->capacity != pq->size){
        createPQNode(vertex, weight, pq, indInPQ);
        increaseNode(pq, pq->size-1, indInPQ);
    }
}

PQNode dequeue(PriorityQ * pq,  short * indInPQ){
    PQNode minimal = *(pq->heap);
    *(pq->heap) = *(pq->heap + pq->size-1);
    *(indInPQ + minimal.vertex) = -1;
    pq->size--;
    heapify(pq, 0, pq->size, indInPQ);
    return minimal;
}

void cleanPriorityQ(PriorityQ * pq){
    free(pq->heap);
    free(pq);
}
