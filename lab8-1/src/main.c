#include <stdlib.h>
#include "stdio.h"
#include "priorityQueue.h"
#include "limits.h"
#include "graph.h"

void checkingBadInput(int verticesNumber, int edgesNumber, FILE * fileOut){
    if(verticesNumber == -1 || edgesNumber == -1){
        fprintf(fileOut,"bad number of lines");
        exit(0);
    }
    if(verticesNumber < 0 || verticesNumber > 5000){
        fprintf(fileOut,"bad number of vertices");
        exit(0);
    }
    if(edgesNumber < 0 || edgesNumber > verticesNumber*(verticesNumber-1)/2){
        fprintf(fileOut,"bad number of edges");
        exit(0);
    }
}

void PrimAlg(unsigned int ** adjMatrix, int verticesNumber, int * parent){
    short * indInPQ = (short*) malloc(sizeof(short)*(verticesNumber+1));
    char * visited = (char*) malloc(sizeof(char)*(verticesNumber+1));
    PriorityQ * pq = createPriorityQ(verticesNumber);

    for(int i = 0; i < verticesNumber; i++){
        *(indInPQ + i) = -1;
        *(parent + i) = -1;
        *(visited + i) = 0;
    }

    // Начинаем с 1ой вершины
    *(parent) = 0;
    *(visited) = 1;
    for(int i = 0; i < verticesNumber; i++){
        if(adjMatrix[0][i] != UINT_MAX && i != 0){
            enqueue(pq, i, (int) adjMatrix[0][i], indInPQ);
            *(parent + i) = 0;
        }
    }
    // Все остальные
    while(pq->size > 0){
        // Вытягиваем по одному элементу очереди с наименьшим весом
        PQNode currentNode = dequeue(pq, indInPQ);
        for(int i = 0; i < verticesNumber; i++){
            if(adjMatrix[currentNode.vertex][i] != UINT_MAX && i != currentNode.vertex && *(visited + i)!=1){
                if( *(indInPQ + i) == -1 ) {
                    // Вставляем новый элемент в приоритеную очередь
                    enqueue(pq, i, (int) adjMatrix[currentNode.vertex][i], indInPQ);
                    *(parent + i) = currentNode.vertex;
                } else {
                    // Понижаем значение уже встроенного в приоритетную очередь элемента pq
                    unsigned int w =  pq->heap[*(indInPQ + i)].weight;
                    if(w > adjMatrix[currentNode.vertex][i]){
                        pq->heap[*(indInPQ + i)].weight = (int) adjMatrix[currentNode.vertex][i];
                        increaseNode(pq, *(indInPQ + i), indInPQ);
                        *(parent + i) = currentNode.vertex;
                    }
                }
            }
        }
        *(visited + currentNode.vertex) = 1;
    }
    free(visited);
    free(indInPQ);
    cleanPriorityQ(pq);
}

int main(void) {
    FILE *fileIn;
    FILE *fileOut;
    int verticesNumber = 0;
    int edgesNumber = 0;

    fileIn = fopen("in.txt", "r");
    fileOut = fopen("out.txt", "w");

    if(fscanf(fileIn,"%d", &verticesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }
    if(fscanf(fileIn,"%d", &edgesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }

    checkingBadInput(verticesNumber, edgesNumber, fileOut);
    unsigned int ** adjMatrix = createAdjMatrix(verticesNumber);
    int * parent = (int*)malloc(sizeof(int)*(verticesNumber+1));

    fillingList(adjMatrix, edgesNumber, verticesNumber, fileIn, fileOut);
    PrimAlg(adjMatrix, verticesNumber, parent);

    char check = 0;
    for(int i = 0; i < verticesNumber; i++){
        if( *(parent + i) == -1){
            check=1;
        }
    }
    if(check > 0 ||  (edgesNumber == 0 && verticesNumber == 0) ){
        fprintf(fileOut, "no spanning tree");
    } else if (check == 0){
        for(int i = 1; i < verticesNumber; i++){
            int prnt = *(parent + i);
            fprintf(fileOut, "%d %d\n", prnt+1, i+1);
        }
    }

    fclose(fileIn);
    fclose(fileOut);
    for (int i = 0; i < verticesNumber; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    free(parent);

    return EXIT_SUCCESS;
}
