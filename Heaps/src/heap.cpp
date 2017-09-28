/*
 * Data Structures and Algorithms II Assignment #2: heaps
 * George Ho, Fall 2017
 * 
 * This code implements a priority queue using a binary heap implementation
 */

#include "heap.h"

heap::heap(int capacity) {
    this->capacity = capacity;
    this->size = 0;

    node empty;
    empty.id = "";
    empty.key = 0;
    empty.pData = nullptr;

    this->data.resize(capacity+1, empty);
    mapping = HashTable(2*capacity);
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (this->size >= this->capacity) {
        return 1;
    }
    else if ((this->mapping).contains(id)) {
        return 2;
    }

    node n;
    n.id = id;
    n.key = key;
    n.pData = pv;

    // Order of the next 2 lines matter: we ignore data.at(0)!
    this->size++;
    this->data.at(size) = n;

    node *ptr = &(this->data.at(size));
    mapping.insert(id, ptr);
    percolateUp(getPos(ptr));

    return 0;
}

int heap::setKey(const std::string &id, int key) {
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (this->size == 0) {
        return 1;
    }

    node minNode = this->data.at(1);

    if (pId != NULL) {
        *pId = minNode.id;
    }

    if (pKey != NULL) {
        *pKey = minNode.key;
    }
    
    if (ppData != NULL) {
        ppData = &minNode.pData;
    }

    minNode = this->data.at(this->size);
    this->size--;
    percolateDown(1);

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool *b = nullptr;
    node *pNode = static_cast<node *>(mapping.getPointer(id, b));

    if (!*b) {
        return 1;
    }

    if (pKey != NULL) {
        *pKey = pNode->key;
    }

    if (ppData != NULL) {
        ppData = pNode->pData;
    }

    node lastNode = this->data.at(this->size);
    pNode->id = lastNode.id;
    pNode->key = lastNode.key;
    pNode->pData = lastNode.pData;
    this->size--;

    int pos = getPos(pNode);
    if (pNode->key > this->data.at(2*pos).key
            || pNode->key > this->data.at(2*pos+1).key) {
        percolateUp(getPos(pNode));
    }
    else {
        percolateDown(getPos(pNode));
    }

    mapping.remove(id);

    return 0;
}

void heap::percolateUp(int currentPos) {

}

void heap::percolateDown(int currentPos) {

}

int heap::getPos(node *pNode) {
    int pos = pNode - &(this->data)[0];
    return pos;
}
