#include <stdlib.h>
#include "stdio.h"
#include "tree.h"

Node * balance(Node * n, int key){
    updateHeight(n);

    int balanceF = getBalanceFactor(n);

    if(balanceF > 1){
        if(key < n->left->key){
            // LL
            return rightR(n);
        } else {
            // LR
            n->left = leftR(n->left);
            return rightR(n);
        }
    } else if (balanceF < -1){
        if(key >= n->right->key){
            // RR
            return leftR(n);
        } else {
            // Rl
            n->right = rightR(n->right);
            return leftR(n);
        }
    }

    return n;
}

Node * insertKeysIntoTree(Node * n, int key){
    /// Если дерево пустое просто добавляем элемент
    if(n == NULL){
        n = createNode(key);
        return n;
    }

    // Вставляем key в дерево
    if(key < n->key)
        n->left = insertKeysIntoTree(n->left, key);
    else
        n->right = insertKeysIntoTree(n->right, key);


    return balance(n, key);
}

Node * fillingTree(int N, Node * root, FILE * file){
    int scannedN = 0;
    int key;
    for(int i = 0; i < N; i++){
        scannedN += fscanf(file,"%d", &key);
        root = insertKeysIntoTree(root, key);
        updateHeight(root);
    }
    if(scannedN < 0)
        printf("unreal");

    return root;
}

int main(void) {
    FILE * file;
    int N;
    Node * root = NULL;
    int scannedN = 0;

    file = fopen("in.txt", "r");

    scannedN = fscanf(file,"%d", &N);
    if(scannedN < 0)
        printf("unreal");


    root = fillingTree(N, root, file);
    fclose(file);

    file = fopen("out.txt", "w");
    fprintf(file, "%d", height(root));
    fclose(file);

    clearTree(root);

    return EXIT_SUCCESS;
}
