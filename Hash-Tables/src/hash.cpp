/*
 * Data Structures and Algorithms II Assignment #1: Hash Tables
 * George Ho, Fall 2017
 * 
 * This code implements a hash table class with linear probing and rehashing.
 */

#include <iostream>
#include "hash.h"

// Hash table constructor.
HashTable::HashTable(int size) {
    int tableSize = getPrime(size);
    this->capacity = tableSize;
    this->filled = 0;

    HashItem empty;
    empty.key = "";
    empty.isOccupied = false;
    empty.isDeleted = false;
    empty.pv = nullptr;

    this->data.resize(tableSize, empty);
}

// Insert an item into the hash table.
int HashTable::insert(const std::string &key, void *pv) {
    int currentPos = hash(key) % this->capacity;

    // Terminates either at the next non-occupied element,
    // or the position of the specified key.
    while (this->data.at(currentPos).isOccupied &&
            this->data.at(currentPos).key != key) {
        currentPos++;
        if (currentPos == this->capacity) {
            currentPos = 0;
        }
    }

    if (!this->data.at(currentPos).isDeleted &&
            this->data.at(currentPos).key == key) {
        return 1;
    }
    else {
        HashItem &item = this->data.at(currentPos);
        item.key = key;
        item.isOccupied = true;
        item.isDeleted = false;
        item.pv = pv;
        (this->filled)++;
    }

    if (2*(this->filled) > this->capacity) {
        if (!this->rehash()) {
            return 2; 
        }
    }

    return 0;
}

// Check if the hash table contains an item.
bool HashTable::contains(const std::string &key) {
    if (this->findPos(key) == -1) {
        return false;
    }

    return true;
}

// Get the pointer associated with a certain key.
void * HashTable::getPointer(const std::string &key, bool *b) {
    int pos = this->findPos(key);
    
    if (b != NULL && pos == -1) {
        *b = false;
        return NULL;
    }
    else {
        *b = true;
    }

    return this->data.at(pos).pv;
}

// Changes the pointer associated with a certain key.
int HashTable::setPointer(const std::string &key, void *pv) {
    int pos = this->findPos(key);

    if (pos == -1) {
        return 1;
    }
    else {
        this->data.at(pos).pv = pv;
    }

    return 0;
}

// Lazily deletes an entry from the hash table.
bool HashTable::remove(const std::string &key) {
    int pos = this->findPos(key);

    if (pos == -1) {
        return false;
    }

   this->data.at(pos).isDeleted = true;
   return true;
}

// Fowler-Noll-Vo hash function
// https://www.programmingalgorithms.com/algorithm/fnv-hash?lang=C%2B%2B
unsigned int HashTable::hash(const std::string &key) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    unsigned int len = key.length();

    for (i = 0; i < len; i++) {
        hash *= fnv_prime;
        hash ^= (key[i]);
    }

    return hash;
}

// Member function to find the position of a certain key in a hash table.
// Used by several public member functions.
int HashTable::findPos(const std::string &key) {
    int currentPos = hash(key) % this->capacity;

    // Terminates either at the next non-occupied element,
    // or the position of the specified key.
    while (this->data.at(currentPos).isOccupied &&
            this->data.at(currentPos).key != key) {
        currentPos++;
        if (currentPos == this->capacity) {
            currentPos = 0;
        }
    }

    // If item is not deleted and keys match, success.
    if (!this->data.at(currentPos).isDeleted &&
            this->data.at(currentPos).key == key) {
        return currentPos;
    }

    // Else, failure.
    return -1;
}

// Rehashes the hash table.
bool HashTable::rehash() {
    int oldCapacity = this->capacity;
    this->capacity = this->getPrime(2*oldCapacity);

    // If none of the primes are large enough, failure.
    if (this->capacity == 0) {
        return false;
    }

    std::vector<HashItem> dataCopy = this->data;
    this->data.resize(this->capacity);

    // If memory allocation does not proceed as expected, failure.
    if (this->data.size() != this->capacity) {
        return false;
    }

    // Set all elements of data to an empty HashItem
    // std::vector::resize would merely initialize the NEW items to empty
    for (int i = 0; i < this->capacity; i++) {
        HashItem &item = this->data.at(i);
        item.key = "";
        item.isOccupied = false;
        item.isDeleted = false;
        item.pv = nullptr;
    }
 
    this->filled = 0;

    for (int i = 0; i < oldCapacity; i++) {
        HashItem temp = dataCopy.at(i);

        if (temp.isOccupied && !temp.isDeleted) {
            this->insert(temp.key, temp.pv);
        }
    }

    return true;
}

// Returns a prime number larger than the number fed in.
// Used by the rehash member function.
// http://planetmath.org/sites/default/files/texpdf/33327.pdf
int HashTable::getPrime(int size) {
    const static std::vector<int> primes = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 16291469, 2582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
    };

    int i = 0;

    // If larger prime not available, failure.
    if (size > primes[25]) {
        return 0;
    }

    while (primes[i] < size) {
        i++;
    }

    return primes[i];
}
