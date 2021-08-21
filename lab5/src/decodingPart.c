#include "decodingPart.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define BUFFER_BINARY_SIZE 256
#define MAX_SYMB_NUM 256
#define BYTE_LENGTH 8

int isFileEmpty(FILE * file){
    if(file == NULL){
        return 1;
    }

    int curPosition = ftell(file);
    fseek(file, 0, SEEK_END);
    int endPosition = ftell(file);
    fseek(file, curPosition, SEEK_SET);

    return (endPosition-curPosition) ? 0 : 1;
}

int takeMessageLength(FILE * fileIn){
    unsigned char buffer[4];
    int mesLength = 0;

    int scannedSymb = fread(buffer, 1, 4, fileIn);
    if (scannedSymb == 0)
        exit(1);

    for (int i = 0; i < 4; ++i) {
        int temp = buffer[i];
        mesLength = mesLength + ( temp << (i*BYTE_LENGTH));
    }
    return mesLength;
}

void updateBuffer(unsigned char * buffer, int * posInBuffer, int * currentBufferSize, FILE* fileIn){
    *posInBuffer = 0;
    *currentBufferSize = fread(buffer, 1, BUFFER_SIZE, fileIn);
}

// Сдвигаемся по байту вправо на 1 символ
void moveCursor(unsigned char * buffer, int * posInByte, int * posInBuffer, int * currentBufferSize, FILE * fileIn){
    *posInByte += 1;
    buffer[*posInBuffer] = buffer[*posInBuffer] << 1;
    if( *posInByte > BYTE_LENGTH-1 ){
        *posInBuffer += 1;
        *posInByte = 0;
        if(*posInBuffer >= *currentBufferSize){
            updateBuffer(buffer, posInBuffer, currentBufferSize, fileIn);
        }
    }
}

unsigned char takeSymbol(unsigned char * buffer, int * posInBuffer, int * posInByte , int * currentBufferSize, FILE * fileIn){
    unsigned char symbol = 0;
    int posInSymbFactory = 0;

    while(*posInByte < BYTE_LENGTH && posInSymbFactory < BYTE_LENGTH){
        symbol <<= 1;
        symbol += buffer[*posInBuffer]/128;
        buffer[*posInBuffer] <<= 1;
        *posInByte += 1;
        posInSymbFactory += 1;
    }

    // Если posInByte дошел до 8
    if(*posInByte > BYTE_LENGTH-1){
        *posInBuffer += 1;
        *posInByte = 0;
        if(*posInBuffer >= *currentBufferSize){
            updateBuffer(buffer, posInBuffer, currentBufferSize, fileIn);
        }
        // Дозаполняем symbol
        while(posInSymbFactory < BYTE_LENGTH){
            symbol <<= 1;
            symbol += buffer[*posInBuffer]/128;
            buffer[*posInBuffer] <<= 1;
            *posInByte += 1;
            posInSymbFactory += 1;
        }
    }

    return symbol;
}

Node * takeHuffmanTree(unsigned char * buffer, int * posInBuffer, int * posInByte, int * currentBufferSize, FILE * fileIn){
    Node * HuffmanTree = (Node*)malloc(sizeof(Node));
    if(buffer[*posInBuffer]/128 == 0){
        moveCursor(buffer, posInByte, posInBuffer, currentBufferSize, fileIn);
        unsigned char symbol = takeSymbol(buffer, posInBuffer, posInByte, currentBufferSize, fileIn);

        HuffmanTree->symbol = symbol;
        HuffmanTree->weight = 8;
        HuffmanTree->left = NULL;
        HuffmanTree->right = NULL;

    } else if(buffer[*posInBuffer]/128 == 1) {
        moveCursor(buffer, posInByte, posInBuffer, currentBufferSize, fileIn);

        HuffmanTree->left = takeHuffmanTree(buffer, posInBuffer, posInByte, currentBufferSize, fileIn);
        HuffmanTree->right = takeHuffmanTree(buffer, posInBuffer, posInByte, currentBufferSize, fileIn);
        HuffmanTree->weight = 0;
        HuffmanTree->symbol = '&';
    }
    return HuffmanTree;
}

void decodeMessage(Node * HuffmanTree, unsigned char * buffer, int * posInBuffer, int * posInByte, int * currentBufferSize, FILE * fileIn, FILE * fileOut){
    Node * HTree = HuffmanTree;
    while(HTree->left || HTree->right){
        if(buffer[*posInBuffer]/128 == 0){
            HTree = HTree->left;
        } else {
            HTree = HTree->right;
        }
        moveCursor(buffer, posInByte, posInBuffer, currentBufferSize, fileIn);
    }
    fputc(HTree->symbol, fileOut);
}

void clearHuffmanTree(Node * root){
    Node * removeBox = NULL;

    if(root != NULL) {
        if (root->right) {
            clearHuffmanTree(root->right);
            root->right = NULL;
            clearHuffmanTree(root);
        } else if (root->left) {
            clearHuffmanTree(root->left);
            root->left = NULL;
            clearHuffmanTree(root);
        } else {
            removeBox = root;
            free(removeBox);
        }
    }

}

void clearDecodingStuff(unsigned char * buffer, Node * decodedHuffmanTree){
    free(buffer);
    clearHuffmanTree(decodedHuffmanTree);
}

void decode(FILE * fileIn, FILE * fileOut){
    int posInByte = 0; // Позиция в байте рассматриваемого в тексте символа
    int posInBuffer = 0; // Позиция в буфере
    int currentBufferSize = 0; // Текущее количество символов в буфере
    int putedSymbols = 0; // Количество декодированных символов
    unsigned char * buffer = (unsigned char*) malloc(sizeof(char)*BUFFER_SIZE);

    fseek(fileIn, 1, SEEK_CUR); // Перескакиваем через \n

    // Проверяем является файл пустым
    if(isFileEmpty(fileIn)){
        free(buffer);
        return;
    }
    int messageLength = takeMessageLength(fileIn);

    currentBufferSize = fread(buffer, 1, BUFFER_SIZE, fileIn);

    // Декодируем дерево Хаффмана
    Node * decodedHuffmanTree = takeHuffmanTree(buffer, &posInBuffer, &posInByte, &currentBufferSize, fileIn);

    // Пока количество декодированных символов не равно количеству символов изначального текста, не прекращаем процесс
    while(putedSymbols < messageLength){
        decodeMessage(decodedHuffmanTree, buffer, &posInBuffer, &posInByte, &currentBufferSize, fileIn, fileOut);
        putedSymbols += 1;
    }

    clearDecodingStuff(buffer, decodedHuffmanTree);
}

