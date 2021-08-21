#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fillingList(unsigned int** adjMatrix, int edgesNumber, int verticesNumber, FILE * fileIn, FILE * fileOut){
    int toV, fromV;
    long long int weight;
    for(int i = 0; i < edgesNumber; i++){
        int a = fscanf(fileIn, "%d %d %lld", &fromV, &toV, &weight);
        if(a == 3){
            if( (fromV<0 || fromV>verticesNumber) || (toV<0 || toV>verticesNumber) ){
                fprintf(fileOut,"bad vertex");
                exit(0);
            } else if(weight < 0 || weight > INT_MAX){
                fprintf(fileOut,"bad length");
                exit(0);
            }
            adjMatrix[toV-1][fromV-1] = (int)weight;
            adjMatrix[fromV-1][toV-1] = (int)weight;
        } else {
            fprintf(fileOut,"bad number of lines");
            exit(0);
        }
    }
}

unsigned int** createAdjMatrix(int size){
    unsigned int ** adjMatrix = (unsigned int**)malloc(sizeof(unsigned int*)*size);
    for(int i = 0; i < size; i++){
        adjMatrix[i] = (unsigned int*)malloc(sizeof(unsigned int)*size);
        for(int j = 0; j < size; j++){
            adjMatrix[i][j] = UINT_MAX;
        }
    }
    return adjMatrix;
}
