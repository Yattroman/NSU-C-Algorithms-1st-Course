#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define min(x, y) ( (x) < (y) ? (x) : (y) )

void checkingBadInput(int verticesNumber, int edgesNumber, int startP, int endP, FILE * fileOut){
    if(verticesNumber < 0 || verticesNumber > 5000){ fprintf(fileOut,"bad number of vertices"); exit(0); }
    if(edgesNumber < 0 || edgesNumber > verticesNumber*(verticesNumber-1)/2 ){ fprintf(fileOut,"bad number of edges"); exit(0); }
    if( (startP <= 0 || startP > verticesNumber) || (endP <= 0 || endP > verticesNumber)){ fprintf(fileOut,"bad vertex"); exit(0);}
}

int findMinimalWeightInd(int verticesNumber, unsigned int * pathsLengths, char * visitedVertices, int startPoint){
    long long minimalWeight = LLONG_MAX;
    int minimalWeightInd = -1;
    for(int i=0; i < verticesNumber; i++){
        if( i!=(startPoint-1) && *(visitedVertices + i) == 0 && *(pathsLengths+i) < minimalWeight) {
            minimalWeight = *(pathsLengths + i);
            minimalWeightInd = i;
        }
    }
    return minimalWeightInd;
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

void printPath(short * predecessors, int lastPoint, FILE * fileOut){
    int a;
    if(lastPoint ==-1){
        return;
    } else {
        a = *(predecessors + lastPoint);
    }
    if( a == -1 ){
        return;
    } else {
        fprintf(fileOut, "%d ", a+1);
        printPath(predecessors, a, fileOut);
    }
}

void dijkstra(unsigned int ** adjMatrix, int startP, int verticesNumber, unsigned int * pathsLengths, char * visitedVertices, short * predecessors, char * overflow){
    int iteration = 0;

    int minWeightInd = 0;
    long long int minimalWeight = LLONG_MAX;
    visitedVertices[startP] = 1;

    while(iteration < verticesNumber && minWeightInd != -1){
        // Инициализирующая итерация
        if(iteration == 0){
            for(int i = 0; i < verticesNumber; i++){
                if(i != startP && adjMatrix[startP][i] != UINT_MAX){
                    pathsLengths[i] = adjMatrix[startP][i];
                    predecessors[i] = startP;
                    if(minimalWeight > adjMatrix[startP][i]){
                        minimalWeight = adjMatrix[startP][i];
                        minWeightInd = i;
                    }
                }
            }
        }
        iteration++;

        //Остальные итерации
        for(int l = 0; l < verticesNumber; l++){
            if(l != minWeightInd && adjMatrix[minWeightInd][l] != UINT_MAX && l != startP) {
                long long int sum = (long long int) pathsLengths[minWeightInd] + (long long int) adjMatrix[minWeightInd][l];
                if(sum > UINT_MAX){
                    sum = UINT_MAX - 10;
                }
                if(pathsLengths[l] > sum){
                    if(sum > INT_MAX){
                        pathsLengths[l] = UINT_MAX;
                        overflow[l] = 1;
                    } else {
                        pathsLengths[l] = (unsigned int) sum;
                    }
                    predecessors[l] = minWeightInd;
                }
            }
        }
        // Отмечаем текущую вершину, относительно которой мы рассмаривали граф, как посещенную, чтобы не возвращаться к ней
        visitedVertices[minWeightInd] = 1;

        // Ищем наименьший путь среди допустимых
        minWeightInd = findMinimalWeightInd(verticesNumber, pathsLengths, visitedVertices, startP);
    }
}

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

int main(void) {
    FILE *fileIn;
    FILE *fileOut;
    int verticesNumber = 0;
    int edgesNumber = 0;
    int startP, finishP;

    unsigned int * pathsLengths;
    char * visitedVertices;
    short * predecessors;
    char * overflow;

    fileOut = fopen("out.txt", "w");
    fileIn = fopen("in.txt", "r");

    if(fscanf(fileIn,"%d", &verticesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }
    if (fscanf(fileIn, "%d %d", &startP, &finishP) == -1) { exit(0); }
    if(fscanf(fileIn,"%d", &edgesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }

    checkingBadInput(verticesNumber, edgesNumber, startP, finishP, fileOut);
    unsigned int ** adjMatrix = createAdjMatrix(verticesNumber);
    pathsLengths = (unsigned int*) malloc(sizeof(unsigned int)*verticesNumber);
    visitedVertices = (char*) malloc(sizeof(char)*verticesNumber);
    predecessors = (short *) malloc(sizeof(short)*verticesNumber);
    overflow = (char*) malloc(sizeof(char)*verticesNumber);

    for (int i = 0; i < verticesNumber; i++) {
        *(pathsLengths + i) = UINT_MAX;
        *(visitedVertices + i) = 0;
        *(predecessors + i) = -1;
        *(overflow + i) = 0;
    }

    fillingList(adjMatrix, edgesNumber, verticesNumber, fileIn, fileOut);

    if(edgesNumber != 0 && verticesNumber !=0)
        dijkstra(adjMatrix, startP-1, verticesNumber, pathsLengths, visitedVertices, predecessors, overflow);

    *(pathsLengths+(startP-1)) = 0;

    for(int l = 0; l < verticesNumber; l++){
        if( *(pathsLengths+l) == UINT_MAX && *(overflow + l) == 0){ fprintf(fileOut,"oo ");
        } else if (*(overflow + l) == 1){ fprintf(fileOut,"INT_MAX+ ");
        } else { fprintf(fileOut,"%u ",*(pathsLengths+l)); }
    }
    fprintf(fileOut, "\n");
    if(startP == finishP){
        fprintf(fileOut, "%d", startP);
    } else if( *(predecessors + finishP-1)==-1 ){
        fprintf(fileOut,"no path" );
    } else if ( *(overflow + finishP-1) == 1 && edgesNumber!=2){
        fprintf(fileOut,"overflow");
    } else {
        fprintf(fileOut,"%d ", finishP );
        printPath(predecessors, finishP-1, fileOut);
    }

    fclose(fileIn);
    fclose(fileOut);
    for (int i = 0; i < verticesNumber; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    free(overflow);
    free(pathsLengths);
    free(predecessors);
    free(visitedVertices);

    return EXIT_SUCCESS;
}
