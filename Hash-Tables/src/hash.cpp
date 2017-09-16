#include "hash.h"

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
    // If key is already in hash table, failure.
    if (contains(key)) {
        return 1;
    }
    else {
        int pos = this->hash(key) % this->capacity;

        // If position is occupied, linearly probe until 
        // unoccupied position is found.
        while (this->data.at(pos).isOccupied) {
            pos++;
            if (pos > this->capacity) {
                pos = pos % this->capacity;
            }
        }

        HashItem &item = this->data.at(pos);
        item.key = key;
        item.isOccupied = true;
        item.isDeleted = false;
        item.pv = pv;
        (this->filled)++;

        // If over half full, attempt rehash.
        if (2*(this->filled) > this->capacity) {
            if (!this->rehash()) {
                return 2; 
            }
        }
    }

    // Success.
    return 0;
}

bool HashTable::contains(const std::string &key) {
    if (this->findPos(key) == -1) {
        return false;
    }

    return true;
}

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

bool HashTable::remove(const std::string &key) {
    int pos = this->findPos(key);

    if (pos == -1) {
        return false;
    }

   this->data.at(pos).isDeleted = true;
   return true;
}

unsigned int HashTable::hash(const std::string &key) {
    // Fowler-Noll-Vo hash function from
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
    int currentPos = hash(key) % this->capacity;

    // Terminates either at the next non-occupied element,
    // or the position of the specified key.
    while (this->data.at(currentPos).isOccupied &&
            this->data.at(currentPos).key != key) {
        currentPos++;
        if (currentPos >= this->capacity) {
            currentPos -= this->capacity;
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

bool HashTable::rehash() {
    int oldCapacity = this->capacity;
    this->capacity = this->getPrime(2*oldCapacity);

    // If none of the primes are large enough, failure.
    if (this->getPrime(2*oldCapacity) == 0) {
        return false;
    }

    HashItem empty;
    empty.key = "";
    empty.isOccupied = false;
    empty.isDeleted = false;
    empty.pv = nullptr;

    std::vector<HashItem> dataCopy = this->data;
    this->data.resize(this->capacity, empty);

    // If memory allocation does not proceed as expected, failure.
    if (this->data.size() != this->capacity) {
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

int HashTable::getPrime(int size) {
    // Primes from http://planetmath.org/sites/default/files/texpdf/33327.pdf
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
