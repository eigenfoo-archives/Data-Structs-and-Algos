#include <vector>
#include "heap.h"

Heap::Heap(int capacity) {
    data.resize(capacity+1);
    mapping = new HashTable(2*capacity);
}

int Heap::insert(const std::string &id, int key, void *pv) {
    return 0;
}

int Heap::setKey(const std::string &id, int key) {
    return 0;
}


int Heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    return 0;
}

int Heap::remove(const std::string &id, int *pKey, void *ppData) {
    return 0;
}


void Heap::percolateUp(int currentPos) {

}


void Heap::percolateDown(int currentPos) {

}

int Heap::getPos(Node *pn) {
    int pos = pn - &(this->data)[0];
    return pos;
}
