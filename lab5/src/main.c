#include <stdlib.h>
#include <stdio.h>
#include "encodingPart.h"
#include "decodingPart.h"

int main(void) {

    FILE * fileIn;
    FILE * fileOut;

    fileIn = fopen("in.txt", "rb");
    fileOut = fopen("out.txt", "wb");

    char typeOfProcess[8];
    if (fgets(typeOfProcess, 3, fileIn) == 0 || isFileEmpty(fileIn))
        fprintf(fileOut, "Error!");

    switch (typeOfProcess[0]) {
        case 'c': encode(fileIn, fileOut); fclose(fileIn); fclose(fileOut); break;
        case 'd': decode(fileIn, fileOut); fclose(fileIn); fclose(fileOut); break;
        default: fprintf(fileOut, "Error!");
    }

    return EXIT_SUCCESS;
}
