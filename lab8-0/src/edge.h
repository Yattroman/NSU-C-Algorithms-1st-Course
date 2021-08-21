#ifndef LAB8_0_EDGE_H
#define LAB8_0_EDGE_H
#include "stdio.h"

typedef struct Edge {
    int toV;
    int fromV;
    int weight;
} Edge;

void pushEdge(Edge * edge, int toV, int fromV, int weight);
void fillingEdgesList(Edge* edgesList, int edgesNumber, int verticesNumber, FILE * fileIn, FILE * fileOut);
int edgesCompare(const void* edge1, const void* edge2);

#endif //LAB8_0_EDGE_H
