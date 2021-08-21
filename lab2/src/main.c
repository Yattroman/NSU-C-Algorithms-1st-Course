#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 15

char* deleteN(char* string){
    if(string == NULL){
        return NULL;
    }

    string[strlen(string) - 1] = '\0';
    return string;
}

int checking(int lenght, char str[]){
    int value = 0;
    int repeating = 0;
    char repeatedNumber = str[0];
    for(int i = 0; i < lenght; i++){
        if(str[i] >= 48 && str[i] <= 57){ // Проверка по ASCII

            value++;
        }
        if(repeatedNumber == str[i]){
            repeating++;
        }
    }

    return (value != lenght ||  ( (repeating == lenght) && repeating!=1) ) ? 0:1;
}

char max(char* str, int length) {
    int indFirstElem = 0;
    char max = str[indFirstElem];
    for (int i = 0; i < length; i++)
    {
        if (str[i] > max)
            max = str[i];
    }
    return max;
}

void sort(char str[], int changeNumber){
    char box;
    for (int i = strlen(str) - 1; i > 0; i--)
    {
        for (int j = changeNumber; j < i; j++)
        {
            if (str[j] > str[j + 1]) {
                box = str[j];
                str[j] = str[j + 1];
                str[j + 1] = box;
            }
        }
    }
}

void swaps(char str[], int length, int n){
    char strOld[length];
    char previous, mvToEnd, mvToBeginning;
    int movedFromEndInd = -1;
    int movedFromBeginningInd = -1;

    previous = str[length-1];

    for(int i =0; i < length; i++){
        strOld[i] = str[i];
    }

    for(int i = length-2; i>=0; i--){
        if(previous > str[i]){
            mvToEnd = str[i];
            mvToBeginning = max(str, length);
            movedFromBeginningInd = i;
            movedFromEndInd = -1;
            for(int h = length-1; h > i; h--){
                if(str[h] >= mvToEnd && str[h] <= mvToBeginning){
                    mvToBeginning = str[h];
                    movedFromEndInd = h;
                }
                if(movedFromEndInd != -1){
                    str[movedFromEndInd] = mvToEnd;
                    str[i]=mvToBeginning;
                }
            }
            if(movedFromBeginningInd != -1){
                sort(str, movedFromBeginningInd+1);
            }
            break;
        } else {
            previous = str[i];
        }
    }

    if(memcmp (str, strOld, length) && n!=0) {
        printf("%s\n", str);
    }

    if(n>1){
        swaps(str, length, n-1);
    }
}

int main(void) {

    char str[BUFF_SIZE]="";
    char *readStr;
    readStr = deleteN(fgets (str, BUFF_SIZE, stdin));
    int lenght;

    int n;
    int scannedCount = 0;

    scannedCount = scanf("%d", &n);

    if(scannedCount != 1){ printf("%s", "not enough data"); }

    lenght =strlen(readStr);

    if(checking(lenght, readStr)){
        swaps(readStr, lenght, n);
    } else {
        printf("bad input");
    }

    return EXIT_SUCCESS;
}
