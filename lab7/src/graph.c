#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/// Проверка на badInput
void checkingBadInput(int verticesNumber, int edgesNumber, FILE * fileOut){
    if(verticesNumber == -1 || edgesNumber == -1){
        fprintf(fileOut,"bad number of lines");
        exit(0);
    }
    if(verticesNumber < 0 || verticesNumber > 1000){
        fprintf(fileOut, "bad number of vertices");
        exit(0);
    }
    if(edgesNumber < 0 || edgesNumber > verticesNumber*(verticesNumber-1)/2){
        fprintf(fileOut,"bad number of edges");
        exit(0);
    }
}

void fillingList(Node * verList[], int edgesNumber, int verticesNumber, Node * adjVertexes, FILE * fileIn, FILE * fileOut){
    int toV, fromV;
    int k = 0;
    for(int i = 0; i < edgesNumber; i++){
        int a = fscanf(fileIn, "%d %d", &fromV, &toV);
        if(a == 2){
            if( (fromV<0 || fromV>verticesNumber) || (toV<0 || toV>verticesNumber) ){
                fprintf(fileOut,"bad vertex");
                exit(0);
            }
            Node * adjVertex = adjVertexes + k;
            verList[fromV-1] = pushNode( adjVertex, toV-1 ,verList[fromV-1]);
            k++;
        } else {
            fprintf(fileOut,"bad number of lines");
            exit(0);
        }
    }
}
