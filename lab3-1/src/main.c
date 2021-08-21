#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

int* filingMassive(int* mass, int N){
    int scannedCount = 0;
    for(int i = 0; i < N; i++){
        scannedCount = scanf("%d", &mass[i]);
    }
    if(scannedCount < -1){ printf("%s", "unreal"); }

    return mass;
}

int* quickSort(int* mass, int low, int top){
    int pivot;
    int lowEl = low;
    int topEl = top;
    int box;
    pivot = mass[(top+low)/2];;

    while(lowEl<=topEl){
        while(pivot>mass[lowEl]){ lowEl++; }
        while(pivot<mass[topEl]){ topEl--; }

        if(lowEl<=topEl) {
            box = mass[lowEl];
            mass[lowEl++] = mass[topEl];
            mass[topEl--] = box;
        }
    }

    if(low<topEl){ quickSort(mass, low, topEl); }
    if(top>lowEl){ quickSort(mass, lowEl, top); }

    return mass;
}

void printMassive(int mass[], int N){
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

    mass = (int*)malloc(N* sizeof(int));

    printMassive(quickSort(filingMassive(mass, N), 0, N-1), N);

    free(mass);

    return 0;
}
