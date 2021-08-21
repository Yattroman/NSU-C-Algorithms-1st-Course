#include <stdlib.h>
#include "stdio.h"
#include "edge.h"
#include "subset.h"
#include "limits.h"

void checkingBadInput(int verticesNumber, int edgesNumber){
    if(verticesNumber == -1 || edgesNumber == -1){
        printf("bad number of lines");
        exit(0);
    }
    if(verticesNumber < 0 || verticesNumber > 5000){
        printf("bad number of vertices");
        exit(0);
    }
    if(edgesNumber < 0 || edgesNumber > verticesNumber*(verticesNumber-1)/2){
        printf("bad number of edges");
        exit(0);
    }
}

int Kruskal(Edge * edgesList, int verticesNumber, int edgesNumber, Edge * res){
    subSet * subsets; // like parentsList
    int resInd = 0;
    int index = 0;
    subsets = (subSet*)malloc(sizeof(subSet)*verticesNumber);

    // Отсортируем дуги по убыванию
    qsort(edgesList, edgesNumber, sizeof(Edge), edgesCompare);

    for(int i=0; i < verticesNumber; i++){
        subSet * ss = (subsets + i);
        ss->parent = i;
        ss->rank = 0;
    }

    while( resInd < verticesNumber-1 && index < edgesNumber){
        // Упорядоченное по возрастанию множество дуг, начинаем с самой маленькой дуги
        Edge edge = *(edgesList + index);
        // Объединяет подмножества только в том случае, если начало и конец дуги не принадлежат одному подмножеству
        if(merge(subsets, edge.fromV-1, edge.toV-1)){
            // Объединение произошло успешно, загружаем дугу в результирующий массив
            *(res + resInd) = edge;
            resInd++;
        }
        index++;
    }
    free(subsets);
    return resInd;
}

int main(void) {
    FILE *fileIn;
    FILE *fileOut;
    int verticesNumber = 0;
    int edgesNumber = 0;

    Edge *edgesList;
    Edge *res;

    fileIn = fopen("in.txt", "r");
    fileOut = fopen("out.txt", "w");

    if(fscanf(fileIn,"%d", &verticesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }
    if(fscanf(fileIn,"%d", &edgesNumber) == -1){ fprintf(fileOut,"bad number of lines"); exit(0); }

    checkingBadInput(verticesNumber, edgesNumber);

    edgesList = (Edge*)malloc(sizeof(Edge)*(edgesNumber));
    res = (Edge*)malloc(sizeof(Edge)*verticesNumber);

    fillingEdgesList(edgesList, edgesNumber, verticesNumber, fileIn, fileOut);

    // Получаем размер преобразованного графа
    int size = Kruskal(edgesList, verticesNumber, edgesNumber, res);
    if(size == verticesNumber-1) {
        for (int j = 0; j < size; j++) {
            Edge edge = *(res + j);
            fprintf(fileOut, "%d %d \n", edge.fromV, edge.toV);
        }
    } else {
        fprintf(fileOut, "no spanning tree");
    }

    fclose(fileIn);
    fclose(fileOut);
    free(edgesList);
    free(res);

    return EXIT_SUCCESS;
}
