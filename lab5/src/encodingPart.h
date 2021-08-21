#ifndef LAB5_ENCODINGPART_H
#define LAB5_ENCODINGPART_H

#include <stdio.h>
#include "codingTable.h"
#include "codingHeap.h"

void calculateFrequency(Node * symbols, char * text, int scannedSymb);
void initiateSymbFreqTable(Node * symbFreqTable);
void fillSymbFreqTable(char * buffer, Node * symbFreqTable, int * textLength, FILE * fileIn);
void sortSymbFreqTable(Node * symbFreqTable);

Heap * initiateHeap(Node * symbols);
void buildHuffmanTree(Heap * cHeap);
Node * getHuffmanTree(Heap * cHeap);

void resetBytePattern(unsigned char * byte, int* posInByte);
void put1Bit(unsigned char * byte, int* posInByte, unsigned char bit, FILE * fileOut);
void putASCIISymbol(unsigned char symb, unsigned char * byte, int* posInByte, FILE * fileOut);

void writeMessageLength(int * length, FILE* fileOut);
void encodeTree(Node * HuffmanTree, int * posInByte, unsigned char * byte, FILE * fileOut);
void encodeMessage(char * buffer, codingTable * cTable, int * posInByte, int * posInSymbCode, unsigned char * byte, FILE * fileOut, FILE * fileIn);

void clearCTable(codingTable * cTable);
void clearEncodingStuff(Heap * cHeap, char * buffer, unsigned char * binaryCodeBuff, codingTable * cTable);

void encode(FILE * fileIn, FILE * fileOut);

#endif //LAB5_ENCODINGPART_H
