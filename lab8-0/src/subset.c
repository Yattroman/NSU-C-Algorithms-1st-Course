#include "edge.h"
#include "subset.h"

// Поиск элемента, с сокращением дороги до него
int find(subSet * subsets, int x){
    subSet * ss = (subsets + x);
    if(ss->parent != x)
        ss->parent = find(subsets, ss->parent);
    return ss->parent;
}

int merge(subSet * subsets, int sub1, int sub2){
    int result = 0;
    // Ищем корни sub1 и sub2
    int sub1R = find(subsets, sub1);
    int sub2R = find(subsets, sub2);
    subSet * s1 = (subsets + sub1R);
    subSet * s2 = (subsets + sub2R);

    // Если корни совпадают, ничего не делаем, то есть элементы принадлежат одному подмножеству, подаем сигнал, что объединение не произошло
    if(sub1R == sub2R)
        return 0;

    if(s1->rank > s2->rank) {
        // Если размеры одного подмножества больше другого, то присоединяем к нему это меньшее подмножество
        s2->parent = sub1R;
        result = 1;
    } else if(s1->rank < s2->rank) {
        // Если размеры одного подмножества больше другого, то присоединяем к нему это меньшее подмножество
        s1->parent = sub2R;
        result = 1;
    } else {
        // Подмножества совпадают по размерам, просто присоединяем s2 к s1
        s1->rank += 1;
        s2->parent = sub1R;
        result = 1;
    }

    return result;
}

