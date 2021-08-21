#include "edge.h"
#include "stdio.h"
#include "limits.h"
#include <stdlib.h>

void pushEdge(Edge * edge, int toV, int fromV, int weight){
    edge->toV = toV;
    edge->fromV = fromV;
    edge->weight = weight;
}

// Заполнение списка edges
void fillingEdgesList(Edge* edgesList, int edgesNumber, int verticesNumber, FILE * fileIn, FILE * fileOut){
    int toV, fromV;
    long long weight;
    for(int i = 0; i < edgesNumber; i++){
        int a = fscanf(fileIn, "%d %d %lld", &fromV, &toV, &weight);
        if(a == 3){
            if( (fromV<0 || fromV>verticesNumber) || (toV<0 || toV>verticesNumber) ){ fprintf(fileOut,"bad vertex"); exit(0);
            } else if(weight < 0 || weight > INT_MAX){ fprintf(fileOut,"bad length"); exit(0); }
            pushEdge(&edgesList[i],toV, fromV, (int) weight);
        } else {
            printf("bad number of lines");
            exit(0);
        }
    }
}

// Компаратор для квиксорта
int edgesCompare(const void* edge1, const void* edge2){
    Edge * e1 = (Edge*) edge1;
    Edge * e2 = (Edge*) edge2;
    return e1->weight - e2->weight;
}
