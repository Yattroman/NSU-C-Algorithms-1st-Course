#include <stdio.h>
#include <stdlib.h>
#include "codingHeap.h"

#ifndef LAB5_DECODINGPART_H
#define LAB5_DECODINGPART_H

int isFileEmpty(FILE * file);

void updateBuffer(unsigned char * buffer, int * posInBuffer, int * currentBufferSize, FILE* fileIn);
void moveCursor(unsigned char * buffer, int * posInByte, int * posInBuffer, int * currentBufferSize, FILE * fileIn);
unsigned char takeSymbol(unsigned char * buffer, int * posInBuffer, int * posInByte , int * currentBufferSize, FILE * fileIn);

int takeMessageLength(FILE * fileIn);
Node * takeHuffmanTree(unsigned char * buffer, int * posInBuffer, int * posInByte, int * currentBufferSize, FILE * fileIn);
void decodeMessage(Node * HuffmanTree, unsigned char * buffer, int * posInBuffer, int * posInByte, int * currentBufferSize, FILE * fileIn, FILE * fileOut);

void clearHuffmanTree(Node * root);
void clearDecodingStuff(unsigned char * buffer, Node * decodedHuffmanTree);

void decode(FILE * fileIn, FILE * fileOut);

#endif //LAB5_DECODINGPART_H
