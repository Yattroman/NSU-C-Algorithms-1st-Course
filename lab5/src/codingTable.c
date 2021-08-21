#include "codingTable.h"
#include "codingHeap.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_SYMB_NUM 256

codingTable * createCodingTable(){
    codingTable * cTable = (codingTable*) malloc(sizeof(codingTable)*(MAX_SYMB_NUM+1) );
    for(int i = 0; i < 256; i++){
        cTable[i].length = 0;
        cTable[i].binaryCode = NULL;
    }
    return cTable;
}

void fillCodingTable(codingTable * cTable, Node * root, int ind, unsigned char * binaryCodeBuf, short * maxBinaryLength){
    if(root->left){
        binaryCodeBuf[ind] = '0';
        fillCodingTable(cTable, root->left, ind+1, binaryCodeBuf, maxBinaryLength);
    }
    if(root->right){
        binaryCodeBuf[ind] = '1';
        fillCodingTable(cTable, root->right, ind+1, binaryCodeBuf, maxBinaryLength);
    }
    if(isLeaf(root)){
        unsigned char * binaryCode = (unsigned char*) malloc (sizeof(unsigned char)*(ind+1));
        for(int i=0; i<ind; i++){
            binaryCode[i] = binaryCodeBuf[i];
        }
        cTable[root->symbol].binaryCode = binaryCode;;
        cTable[root->symbol].length = ind;
        *(maxBinaryLength) = ( *maxBinaryLength<ind ) ? ind : *maxBinaryLength;
    }
}
