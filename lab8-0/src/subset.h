#ifndef LAB8_0_SUBSET_H
#define LAB8_0_SUBSET_H

typedef struct subSet {
    int parent;
    int rank;
} subSet;

int find(subSet * subsets, int x);
int merge(subSet * subsets, int sub1, int sub2);

#endif //LAB8_0_SUBSET_H
