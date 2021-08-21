#include "node.h"
#include <malloc.h>

Node * pushNode(Node* vertex, int index, Node * next){
    vertex->index = index;
    vertex->next = next;

    return vertex;
}
