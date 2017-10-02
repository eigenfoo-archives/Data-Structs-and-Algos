/*
 * Data Structures and Algorithms II Assignment #2: Heaps
 * George Ho, Fall 2017
 * 
 * This code implements a priority queue using a binary heap implementation
 */

#include "heap.h"

// Heap constructor
heap::heap(int capacity) {
    this->capacity = capacity;
    this->size = 0;

    node empty;
    empty.id = "";
    empty.key = 0;
    empty.pData = nullptr;

    this->data.resize(capacity+1, empty);
    mapping = hashTable(2*capacity);
}

// Inserts a node into the heap
int heap::insert(const std::string &id, int key, void *pv) {
    if (this->size >= this->capacity) {
        return 1;
    }
    else if ((this->mapping).contains(id)) {
        return 2;
    }

    node newNode;
    newNode.id = id;
    newNode.key = key;
    newNode.pData = pv;

    // Order of the next 2 lines matter: we ignore data.at(0)!
    this->size++;
    this->data.at(size) = newNode;

    node *ptr = &(this->data.at(size));
    mapping.insert(id, ptr);
    this->percolateUp(getPos(ptr));

    return 0;
}

// Sets key of the node associated with the unique string id
int heap::setKey(const std::string &id, int key) {
    bool b = true;
    node *pNode = static_cast<node *>(this->mapping.getPointer(id, &b));

    if (!b) {
        return 1;
    }

    int oldKey = pNode->key;
    pNode->key = key;

    int index = this->getPos(pNode);
    if (oldKey < key) {
        this->percolateDown(index);
    }
    else if (oldKey > key) {
        this->percolateUp(index);
    }

    return 0;
}

// Deletes node associated with the minimum key
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
        *(static_cast<void **> (ppData)) = minNode.pData;
    }

    this->data.at(1) = this->data.at(this->size);
    this->size--;
    this->percolateDown(1);

    this->mapping.remove(minNode.id);

    return 0;
}

// Removes node associated with the given string id
int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool b = true;
    node *pNode = static_cast<node *>(mapping.getPointer(id, &b));

    if (!b) {
        return 1;
    }

    if (pKey != NULL) {
        *pKey = pNode->key;
    }

    if (ppData != NULL) {
        ppData = pNode->pData;
    }

    int oldKey = pNode->key;

    *pNode = this->data.at(this->size);
    this->size--;

    int newKey = pNode->key;

    if (newKey > oldKey) {
        this->percolateDown(getPos(pNode));
    }
    else {
        this->percolateUp(getPos(pNode));
    }

    this->mapping.remove(id);

    return 0;
}

// Percolates node up to preserve the heap order property
void heap::percolateUp(int currentPos) {
    int parent = 0;
    node temp = this->data.at(currentPos);

    while (currentPos > 1) {
        parent = currentPos/2;    // C++ integer division 

        // If parent is larger than temp
        if (temp.key < this->data.at(parent).key) {
            // Bring parent down to hole
            this->data.at(currentPos) = this->data.at(parent);
            // Update hash table pointer
            this->mapping.setPointer(this->data.at(currentPos).id,
                    &(this->data.at(currentPos)));
        }
        else {
            // Hole is in the right place
            break;
        }

        // Move hole up to where the parent used to be
        currentPos = parent;
    }

    // Either the parent is less than or equal to temp, or we are at
    // the root. Either way, currentPos is where temp should go.
    this->data.at(currentPos) = temp;
    this->mapping.setPointer(this->data.at(currentPos).id,
            &(this->data.at(currentPos)));
}

// Percolates node down to preserve the heap order property
void heap::percolateDown(int currentPos) {
    int child = 0;
    node temp = this->data.at(currentPos);

    while (2*currentPos <= this->size) {
        child = 2*currentPos;

        // If there is another child, check if it is smaller.
        // If so, use it for the comparison.
        if (child < this->size
                && this->data.at(child).key > this->data.at(child+1).key) {
            child++;
        }

        // If smaller child is smaller than temp
        if (temp.key > this->data.at(child).key) {
            // Bring smaller child up to hole
            this->data.at(currentPos) = this->data.at(child);
            // Update hash table pointer
            this->mapping.setPointer(this->data.at(currentPos).id,
                    &(this->data.at(currentPos)));
        }
        else {
            // Hole is in the right place
            break;
        }

        // Move hole down to where the smaller child used to be
        currentPos = child;
    }

    // Either the smaller child is greater than or equal to temp,
    // or there are no children at all. Either way, currentPos is 
    // where temp should go.
    this->data.at(currentPos) = temp;
    this->mapping.setPointer(this->data.at(currentPos).id,
            &(this->data.at(currentPos)));
}

// Gets index position of given node
int heap::getPos(node *pNode) {
    int pos = pNode - &(this->data)[0];
    return pos;
}
