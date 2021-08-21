#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "graph.h"

const char WHITE = '0';
const char GREY = '1';
const char BLACK = '2';

void DFS(Node * verList[], char* colors, int currentV, int * stack, int * curStackInd, FILE * file){

    if(colors[currentV] == GREY){
        fprintf(file,"impossible to sort"); exit(0);
    } else if (colors[currentV] == BLACK) {
        return;
    }

    *(colors + currentV) = GREY;

    for(Node * runnerHead = verList[currentV]; runnerHead != NULL; runnerHead = runnerHead->next){
        int subVertInd = runnerHead->index;
        if( verList[subVertInd] != NULL)
            DFS(verList, colors, subVertInd, stack, curStackInd, file);
    }

    /// Отмечаем элемент черным цветом
    colors[currentV] = BLACK;

    /// Загоняем в стэк отмеченные цветом 2 вершины
    stack[*curStackInd] = currentV;
    *(curStackInd) += 1;

}

void printResults(int * curStackInd, int * verticesNumber, int * stack, char * colors, FILE * fileOut){
    // Вывод "стэка"
    for(int i = *curStackInd - 1; i >= 0; i--)
        fprintf(fileOut,"%d ", stack[i] + 1);

    // Выводим все одиночные вершины, у которых нет смежных
    for (int i = 0; i < *verticesNumber; i++) {
        if (colors[i] == WHITE) // ~ ( verList[i] == NULL)
            fprintf(fileOut, "%d ", i + 1);
    }
}

int main(void) {
    FILE *fileOut;
    FILE *fileIn;
    int verticesNumber;
    int edgesNumber;
    int curStackInd = 0;

    fileIn = fopen("in.txt", "r");
    fileOut = fopen("out.txt", "w");

    if(fscanf(fileIn,"%d", &verticesNumber) == -1){
        fprintf(fileOut,"bad number of lines");
        exit(0);
    }
    if(fscanf(fileIn,"%d", &edgesNumber) == -1){
        fprintf(fileOut,"bad number of lines");
        exit(0);
    }

    checkingBadInput(verticesNumber, edgesNumber, fileOut);

    Node * verList[verticesNumber];
    char * colors = (char *) malloc(sizeof(char)*verticesNumber);
    int * stack = (int *) malloc(sizeof(int)*verticesNumber);
    Node * adjVertexes = (Node *) malloc(( sizeof(Node)*(edgesNumber)) );

    for (int i = 0; i < verticesNumber; ++i)
        verList[i] = NULL;

    for (int i = 0; i < verticesNumber; ++i)
        colors[i] = WHITE;

    fillingList(verList, edgesNumber, verticesNumber, adjVertexes, fileIn, fileOut);

    // Прогон алгоритма для всех вершин, у которых есть смежные
    for(int i = 0; i < verticesNumber; i++){
        if( verList[i] != NULL)
            DFS(verList, colors, i, stack, &curStackInd, fileOut);
    }

    printResults(&curStackInd, &verticesNumber, stack, colors, fileOut);

    fclose(fileIn);
    fclose(fileOut);
    free(adjVertexes);
    free(colors);
    free(stack);

    return EXIT_SUCCESS;
}
