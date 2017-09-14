#include "hash.hpp"

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

unsigned int HashTable::getPrime(int size) {
    // Primes from akrowne
    // http://planetmath.org/sites/default/files/texpdf/33327.pdf
    const static unsigned int primes[] = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 16291469, 2582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
    };

    int i = 0;
    while (primes[i] < 2*size) {
        i++;
    }

    return primes[i];
}
