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

int HashTable::insert(const std::string &key, void *pv) {
    return 0;
}

bool HashTable::contains(const std::string &key) {
    return true;
}

void * HashTable::getPointer(const std::string &key, bool *b) {
    return nullptr;
}

int HashTable::setPointer(const std::string &key, void *pv) {
    return 0;
}

unsigned int HashTable::hash(const std::string &key) {
    // Fowler-Noll-Vo hash function
    // https://www.programmingalgorithms.com/algorithm/fnv-hash?lang=C%2B%2B
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

int HashTable::findPos(const std::string &key) {
    unsigned int currentPos = hash(key);

    // Terminates either at the next non-occupied element,
    // or the position of the specified key.
    while (this->data.at(currentPos).isOccupied &&
            this->data.at(currentPos).key != key) {
        currentPos++;
        if (currentPos >= this->capacity) {
            currentPos -= this->capacity;
        }
    }

    // If non-occupied or deleted, return -1
    if (!this->data.at(currentPos).isOccupied ||
            this->data.at(currentPos).isDeleted) {
        return -1;
    }

    // Otherwise, return the position found
    return currentPos;
}

bool HashTable::rehash() {
    return true;
}

unsigned int HashTable::getPrime(int size) {
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
