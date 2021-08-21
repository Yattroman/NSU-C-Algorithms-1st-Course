#ifndef LAB7_NODE_H
#define LAB7_NODE_H

#include <stdio.h>

typedef struct Node {
    struct Node* next;
    int index;
} Node;

Node * pushNode(Node* node, int index, Node * next);

#endif //LAB7_NODE_H
