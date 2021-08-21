#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

void filingMassive(int* mass, int N){
    int scannedCount = 0;
    for(int i = 0; i < N; i++){
        scannedCount = scanf("%d", &mass[i]);
    }
    if(scannedCount < -1){ printf("%s", "unreal"); }

}

void heapMake(int* mass, int N, int root){
    int maxElem;
    maxElem = root;
    int leftElem = root*2+1;
    int rightElem = root*2+2;

    if( rightElem<N && (mass[rightElem]>mass[maxElem])){
        maxElem = rightElem;
    }
    if( leftElem<N && (mass[leftElem]>mass[maxElem])){
        maxElem = leftElem;
    }

    if(maxElem != root){
        int box = mass[maxElem];
        mass[maxElem]=mass[root];
        mass[root] = box;
        heapMake(mass, N, maxElem); // Down to bottom
    }

}

void heapSort(int* mass, int N){

// Creating first heap - the biggest elem to top
    for(int g = 2*N-1; g>=0; g--){
        heapMake(mass, N, g);
    }

    for(int m = N-1; m>0; m--){
        int box = mass[m];
        mass[m] = mass[0];
        mass[0] = box;
        heapMake(mass, m, 0);
    }

}

void printMassive(int* mass, int N){
    for(int k = 0; k<N; k++){
        printf("%d ",mass[k]);
    }
}

int main(void) {

    int *mass;
    int N = -1;
    int scannedCount = scanf("%d", &N);

    if (scannedCount != 1) {
        printf("not enough input data\n");
        return 1;
    }

    if(N<0 || N>2000000){
        return 1;
    }

    mass = (int*)malloc( (N) * sizeof(int) );

    filingMassive(mass, N);
    heapSort(mass, N);
    printMassive(mass, N);

    free(mass);

    return 0;
}
