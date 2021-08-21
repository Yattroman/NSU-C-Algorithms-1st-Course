#ifndef LAB5_CODINGTABLE_H
#define LAB5_CODINGTABLE_H

#include "codingHeap.h"

typedef struct codingTable{
    unsigned char * binaryCode;
    short length; // Максимальная длина binaryCode - 8
} codingTable;

codingTable * createCodingTable();
void fillCodingTable(codingTable * cTable, Node * root, int ind, unsigned char * binaryCodeBuf, short * maxBinaryLength);

#endif //LAB5_CODINGTABLE_H
