#include "encodingPart.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define BUFFER_BINARY_SIZE 256
#define MAX_SYMB_NUM 256
#define BYTE_LENGTH 8

void calculateFrequency(Node * symbols, char * text, int scannedSymb){
    for(int i = 0; i < scannedSymb; i++){
        symbols[(unsigned char)text[i]].weight++;
    }
}

Heap * initiateHeap(Node * symbols){
    // Считаем, сколько разных символов есть в тексте
    int diffSymbolsNum = 0;
    for(int k = 0; k < MAX_SYMB_NUM; k++){
        if(symbols[k].weight > 0)
            (diffSymbolsNum) = (diffSymbolsNum) + 1;
    }
    // Создаем heap в соответсвии c количеством разных смволов
    Heap * cHeap = createHeap(diffSymbolsNum);

    // Загружаем символы и их частоты в cHeap, формируя кучу
    for(int i = 0; i < MAX_SYMB_NUM; i++){
        if(symbols[i].weight > 0){
            insert(cHeap, symbols[i].symbol, symbols[i].weight, NULL, NULL);
        } else {
            break;
        }
    }

    free(symbols);
    return cHeap;
}

void buildHuffmanTree(Heap * cHeap){
    // Создаем дерево Хаффмана, пока только просто дерево без 0 и 1
    while(cHeap->size != 1){
        Node * left = extract(cHeap);
        Node * right = extract(cHeap);
        if(left!=NULL && right!=NULL) {
            insert(cHeap, '&', left->weight + right->weight, left, right);
        } else {
            exit(0);
        }
    }
}

void initiateSymbFreqTable(Node * symbFreqTable){
    // Изначально у всех символов weight = 0
    for(int i = 0; i < 256; i++) {
        symbFreqTable[i].weight = 0;
        symbFreqTable[i].symbol = (unsigned char) i;
    }
}

void fillSymbFreqTable(char * buffer, Node * symbFreqTable, int * textLength, FILE * fileIn){
    // Читаем входной текст и посчитаем количество повторений для каждого символа, заодно и количество символов в тексте
    int scannedSymb = fread(buffer, 1, BUFFER_SIZE, fileIn);
    *textLength+=scannedSymb;
    while (scannedSymb){
        calculateFrequency(symbFreqTable, buffer, scannedSymb);
        scannedSymb = fread(buffer, 1, BUFFER_SIZE, fileIn);
        *textLength+=scannedSymb;
    }
}

void sortSymbFreqTable(Node * symbFreqTable){
    // Отсортируем массив частот символов по возрастанию
    sortNodes(symbFreqTable, MAX_SYMB_NUM);
}

Node * getHuffmanTree(Heap * cHeap){
    buildHuffmanTree(cHeap);
    return cHeap->heap[0];
}

void resetBytePattern(unsigned char * byte, int* posInByte){
    *byte = 0;
    *posInByte = 0;
}

void put1Bit(unsigned char * byte, int* posInByte, unsigned char bit, FILE * fileOut){
    *byte <<= 1;
    *byte += bit;
    *posInByte += 1;
    if(*posInByte > BYTE_LENGTH-1){
        fputc(*byte, fileOut);
        resetBytePattern(byte, posInByte);
    }
}

void putASCIISymbol(unsigned char symb, unsigned char * byte, int* posInByte, FILE * fileOut){
    int indInSymb = 0;

    while(indInSymb<BYTE_LENGTH && *posInByte<BYTE_LENGTH){
        *byte <<= 1;
        *byte += symb/128; // добавили самый левый бит ASCII-записи символа
        symb <<= 1;
        *posInByte += 1;
        indInSymb += 1;
    }
    if(*posInByte > BYTE_LENGTH-1){
        fputc(*byte, fileOut);
        resetBytePattern(byte, posInByte);
        while(indInSymb < BYTE_LENGTH){
            *byte <<= 1;
            *byte += symb/128;
            symb <<= 1;
            *posInByte += 1;
            indInSymb += 1;
        }
    }
}

void encodeTree(Node * HuffmanTree, int * posInByte, unsigned char * byte, FILE * fileOut){
    if(HuffmanTree->left != NULL || HuffmanTree->right != NULL){
        put1Bit(byte, posInByte, 1, fileOut);
        encodeTree(HuffmanTree->left, posInByte, byte, fileOut);
        encodeTree(HuffmanTree->right, posInByte, byte, fileOut);
    } else {
        put1Bit(byte, posInByte, 0, fileOut);
        putASCIISymbol(HuffmanTree->symbol, byte, posInByte, fileOut);
    }
}

void encodeMessage(char * buffer, codingTable * cTable, int * posInByte, int * posInSymbCode, unsigned char * byte, FILE * fileOut, FILE * fileIn){
    int posInBuffer = 0;
    int scannedNum = fread(buffer, 1, BUFFER_SIZE, fileIn);
    while (scannedNum){
        while(posInBuffer < scannedNum){
            while(*posInSymbCode < cTable[(unsigned char)buffer[posInBuffer]].length && *posInByte < BYTE_LENGTH){
                *byte <<= 1;
                *byte += (cTable[(unsigned char)buffer[posInBuffer]].binaryCode[*posInSymbCode] - '0');
                *posInByte += 1;
                *posInSymbCode += 1;
            }
            if( *posInByte == BYTE_LENGTH ){
                fputc(*byte, fileOut);
                resetBytePattern(byte, posInByte);
            } else {
                posInBuffer += 1;
                *posInSymbCode = 0;
            }
        }
        posInBuffer = 0;
        scannedNum = fread(buffer, 1, BUFFER_SIZE, fileIn);
    }

    // Если символы в буфере закончились, а байт остался недозаполненным, то заполняем пустоту нулями
    if(*posInByte > 0){
        while(*posInByte < BYTE_LENGTH){
            *byte <<= 1;
            *posInByte += 1;
        }
        fputc(*byte, fileOut);
        resetBytePattern(byte, posInByte);
    }
}

void writeMessageLength(int * length, FILE* fileOut) {
    fwrite(length, 1, 4, fileOut);
}

void clearCTable(codingTable * cTable){
    for(int i = 0; i < 256; i++){
        if(cTable[i].binaryCode != NULL){
            free(cTable[i].binaryCode);
        }
    }
    free(cTable);
}

void clearEncodingStuff(Heap * cHeap, char * buffer, unsigned char * binaryCodeBuff, codingTable * cTable){
    free(cHeap->nodesBox);
    free(cHeap->heap);
    free(cHeap);
    free(buffer);
    clearCTable(cTable);
    free(binaryCodeBuff);
}

void encode(FILE * fileIn, FILE * fileOut){
    int posInByte = 0;
    int posInSymbCode = 0;
    unsigned char byte = 0;

    int textLength = 0;
    fseek(fileIn, 1, SEEK_CUR);
    int savePos = ftell(fileIn);
    char * buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);

    Node * symbFreqTable = (Node*) malloc(sizeof(Node)*(MAX_SYMB_NUM+1));
    initiateSymbFreqTable(symbFreqTable);
    fillSymbFreqTable(buffer, symbFreqTable, &textLength, fileIn);
    sortSymbFreqTable(symbFreqTable);

    Heap * cHeap = initiateHeap(symbFreqTable);
    Node * HuffmanTree = getHuffmanTree(cHeap);

    short maxBinaryLength = 0;
    codingTable * cTable = createCodingTable();
    unsigned char * binaryCodeBuff = (unsigned char*) malloc (sizeof(unsigned char)*(BUFFER_BINARY_SIZE));
    fillCodingTable(cTable, HuffmanTree, 0, binaryCodeBuff, &maxBinaryLength);

    fseek(fileIn, savePos, 0);
    writeMessageLength( &textLength, fileOut );
    encodeTree(HuffmanTree, &posInByte, &byte, fileOut);
    fseek(fileIn, savePos, 0);
    encodeMessage( buffer, cTable, &posInByte, &posInSymbCode, &byte, fileOut, fileIn );

    clearEncodingStuff(cHeap, buffer, binaryCodeBuff, cTable);
}

