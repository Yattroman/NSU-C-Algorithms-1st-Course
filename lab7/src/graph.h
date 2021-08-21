#include "node.h"

#ifndef LAB7_GRAPH_H
#define LAB7_GRAPH_H

void fillingList(Node * verList[], int edgesNumber, int verticesNumber, Node * adjVertexes, FILE * fileIn, FILE * fileOut);
void checkingBadInput(int verticesNumber, int edgesNumber, FILE * fileOut);

#endif //LAB7_GRAPH_H
