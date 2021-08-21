#ifndef LAB5_CODINGHEAP_H
#define LAB5_CODINGHEAP_H

typedef struct Node {
    struct Node * left;
    struct Node * right;
    int weight;
    unsigned char symbol;
} Node;

typedef struct Heap {
    int size;
    int capacity;
    Node ** heap;
    // 2 поля, которые нужны для хранения Nodes в одном цельном куске памяти, так как выделять память 1000 раз - не эффективное решение
    short indInNodesBox;
    Node * nodesBox;
} Heap;

Heap * createHeap(int capacity);
void createNode(Heap * heap, unsigned char symbol, int weight, Node * left, Node * right);
void swap(Node * a, Node * b);
void heapify(Heap * heap, int N, int root);
Node * extract(Heap * heap);
void insert(Heap * heap, unsigned char symbol, int weight, Node * left, Node * right);
int compareNodes(const void * a, const void * b);
void sortNodes(Node * nodeList, int size);
char isLeaf(Node * node);

#endif //LAB5_CODINGHEAP_H
