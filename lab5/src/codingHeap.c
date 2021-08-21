#include "codingHeap.h"
#include "malloc.h"
#include <stdlib.h>
#include <stdio.h>

Heap * createHeap(int capacity){
    if(capacity != 0){
        Heap * cHeap = (Heap*) malloc(sizeof(Heap));
        cHeap->heap = (Node**) malloc(sizeof(Node*)*(capacity+1));
        cHeap->indInNodesBox = 0;
        cHeap->nodesBox = (Node*) malloc(sizeof(Node)*(capacity+1)*2);
        cHeap->capacity = capacity;
        cHeap->size = 0;
        return cHeap;
    } else {
        exit(0);
    }

}

void createNode(Heap * cHeap, unsigned char symbol, int weight, Node * left, Node * right){
    Node * node = cHeap->nodesBox + cHeap->indInNodesBox;
    node->symbol = symbol;
    node->weight = weight;
    node->left = left;
    node->right = right;
    cHeap->indInNodesBox++;

    cHeap->heap[cHeap->size] = node;
}

void swap(Node *a, Node *b){
    Node box = *b;
    *b = *a;
    *a = box;
}

int compareNodes(const void * a, const void * b){
    Node * n1 = (Node*) a;
    Node * n2 = (Node*) b;

    return n1->weight-n2->weight > 0 ? -1 : ( (n1->weight-n2->weight < 0) ? 1:0);
}

void sortNodes(Node * nodeList, int size){
    qsort(nodeList, size, sizeof(Node), &compareNodes);
}

void heapify(Heap * cHeap, int N, int root){
    int minimal = root;
    int left = root*2+1;
    int right = root*2+2;

    if( left < N && cHeap->heap[minimal]->weight > cHeap->heap[left]->weight){
        minimal = left;
    }
    if( right < N && cHeap->heap[minimal]->weight > cHeap->heap[right]->weight){
        minimal = right;
    }
    if(minimal != root){
        swap(cHeap->heap[root], cHeap->heap[minimal]);
        heapify(cHeap, N, minimal);
    }
}

void insert(Heap * cHeap, unsigned char symbol, int weight, Node * left, Node * right){
    if(cHeap->capacity > cHeap->size){
        createNode(cHeap, symbol, weight, left, right);
        cHeap->size += 1;
        int i = cHeap->size-1;
        while( (i+1)/2 > 0 && cHeap->heap[(i+1)/2-1]->weight > cHeap->heap[i]->weight){
            swap( (cHeap->heap[(i+1)/2-1]), (cHeap->heap[i]) );
            i = (i+1)/2-1;
        }
    }
}

Node * extract(Heap * cHeap){
    Node * minimal = cHeap->heap[0];
    cHeap->heap[0] = cHeap->heap[cHeap->size-1];
    cHeap->size--;
    heapify(cHeap, cHeap->size, 0);

    return minimal;
}

char isLeaf(Node * node){
    return !(node->right) && !(node->left) ? 1 : 0;
}


