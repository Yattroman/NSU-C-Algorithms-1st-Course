//
// Created by machl on 29.03.2020.
//

#ifndef LAB6_TREE_H
#define LAB6_TREE_H

#include "stdio.h"

typedef struct Node{
    int key;
    int height;
    struct Node * left;
    struct Node * right;
} Node;

int height(Node * node);
Node * createNode(int key);
Node * rightR(Node * a);
Node * leftR(Node * a);
void updateHeight(Node * node);
int getBalanceFactor(Node * node);
void printTree(Node * root, int floor, FILE * file);
void clearTree(Node * root);

#endif //LAB6_TREE_H
