//
// Created by machl on 29.03.2020.
//
#include "tree.h"
#include "stdio.h"
#include "malloc.h"

#define max(x, y) ( (x) > (y) ? (x) : (y) )

int height(Node * node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

void updateHeight(Node * node){
    int leftH = (node->left) ? node->left->height : 0;
    int rightH = (node->right) ? node->right->height : 0;

    node->height = max(leftH, rightH) + 1;
}

Node * createNode(int key){
    Node * newNode = (Node*) malloc(sizeof(Node));
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->key = key;
    newNode->height = 1;

    return newNode;
}

Node * rightR(Node * a){
    Node * b = a->left;
    Node * subTree = b->right;
    b->right = a;
    a->left = subTree;
    updateHeight(a);
    updateHeight(b);

    return b;
}

Node * leftR(Node * a){
    Node * b = a->right;
    Node * subTree = b->left;
    b->left = a;
    a->right = subTree;
    updateHeight(a);
    updateHeight(b);

    return b;
}

void printTree(Node * n, int floor, FILE * file){
    if(n) {
        printTree(n->right, floor + 1, file);
        for(int i = 0; i < floor; i++)
            fprintf(file, " ");
        fprintf(file,"%d\n", n->key);
        printTree(n->left, floor + 1, file);
    }
}

int getBalanceFactor(Node * node){
    if(node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

void clearTree(Node * root){
    Node * removeBox = NULL;

    if(root != NULL) {
        if (root->right) {
            clearTree(root->right);
            root->right = NULL;
            clearTree(root);
        } else if (root->left) {
            clearTree(root->left);
            root->left = NULL;
            clearTree(root);
        } else {
            removeBox = root;
            free(removeBox);
        }
    }

}
