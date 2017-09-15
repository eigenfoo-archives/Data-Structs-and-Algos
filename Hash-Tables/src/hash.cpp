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
    unsigned int pos = this->findPos(key);

    // If key is already in hash table, return 1
    if (pos == -1) {
        return 1;
    }
    // Else, insert
    else {
        HashItem temp;
        temp.key = key;
        temp.isOccupied = true;
        temp.isDeleted = false;
        temp.pv = pv;

        this->data.at(pos) = temp;
    }

    // If over half full, rehash
    if (2*(this->filled) > this->capacity) {
        // If rehash fails, return 2
        if (!this->rehash()) {
            return 2;
        }
    }

    // Otherwise, insertion successful. Return 0
    return 0;
}

bool HashTable::contains(const std::string &key) {
    if (this->findPos(key) == -1) {
        return false;
    }

    return true;
}

void * HashTable::getPointer(const std::string &key, bool *b) {
    unsigned int pos = this->findPos(key);
    
    if (b != NULL && pos == -1) {
        *b = false;
        return NULL;
    }
    else {
        *b = true;
    }

    return this->data.at(pos).pv;
}

int HashTable::setPointer(const std::string &key, void *pv) {
    unsigned int pos = this->findPos(key);

    if (pos == -1) {
        return 1;
    }
    else {
        this->data.at(pos).pv = pv;
    }

    return 0;
}

bool HashTable::remove(const std::string &key) {
    unsigned int pos = this->findPos(key);

    if (pos == -1) {
        return false;
    }

   this->data.at(pos).isDeleted = true;
   return true;
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

unsigned int HashTable::findPos(const std::string &key) {
    unsigned int currentPos = hash(key) % this->capacity;

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
    unsigned int oldCapacity = this->capacity;
    unsigned int newCapacity = this->getPrime(2*oldCapacity);

    // If none of our primes are large enough, rehash fails
    if (newCapacity == 0) {
        return false;
    }

    HashItem empty;
    empty.key = "";
    empty.isOccupied = false;
    empty.isDeleted = false;
    empty.pv = nullptr;

    std::vector<HashItem> dataCopy = this->data;
    this->data.resize(newCapacity, empty);

    // If memory allocation does not proceed as expected, rehash fails
    if (this->data.size() != newCapacity) {
        return false;
    }

    for (int i = 0; i < oldCapacity; i++) {
        HashItem temp = dataCopy.at(i);

        if (temp.isOccupied && !temp.isDeleted) {
            this->insert(temp.key, temp.pv);
        }
    }

    return true;
}

unsigned int HashTable::getPrime(unsigned int size) {
    // http://planetmath.org/sites/default/files/texpdf/33327.pdf
    const static unsigned int primes[] = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 16291469, 2582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
    };

    int i = 0;

    // If we don't have a larger prime, return 0
    if (size > primes[25]) {
        return 0;
    }

    while (primes[i] < size) {
        i++;
    }

    return primes[i];
}
