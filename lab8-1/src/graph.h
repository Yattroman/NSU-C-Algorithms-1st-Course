#ifndef LAB8_1_GRAPH_H
#define LAB8_1_GRAPH_H
#include "stdio.h"

void fillingList(unsigned int** adjMatrix, int edgesNumber, int verticesNumber, FILE * fileIn, FILE * fileOut);
unsigned int** createAdjMatrix(int size);

#endif //LAB8_1_GRAPH_H
