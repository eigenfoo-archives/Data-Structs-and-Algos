#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <string>
#include "hash.h"

class Heap {
    public:
        //
        // heap - constructor allocates space for the nodes of the heap and
        // the mapping (hash table) based on the specified capacity
        //
        Heap(int capacity);

        //
        // insert - inserts a new node into the binary heap
        //
        // Inserts a node with the specified id string, key, and optionally a
        // pointer. The key is used to determin the final position of the new
        // node.
        //
        // Returns:
        //   0 on success
        //   1 if the heap is already filled to capacity
        //   2 if a note with the given id already exists (but the heap is not
        //     filled to capacity)
        //
        int insert (const std::string &id, int key, void *pv = NULL);

        //
        // setKey - set the key of the specified node to the specified value
        //
        // I have decided that the class should provide this member function
        // instead of two separate increaseKey and decreaseKey functions.
        //
        // Returns:
        //   0 on success
        //   1 if a node with the given id does not exist
        //
        int setKey(const std::string &id, int key);

        // deleteMin - return the data associated with the smallest key and
        // delete that node from the binary heap
        //
        // If pId is supplied (i.e., it is not NULL), write to that address the
        // id of the node being deleted. If pKey is supplied, write to that
        // address the key of the node being deleted. If ppData is supplied,
        // write to that address the associated void pointer.
        //
        // Returns:
        //   0 on success
        //   1 if the heap is empty
        //
        int deleteMin(std::string *pId = NULL, int *pKey = NULL,
                void *ppData = NULL);

        // remove - delete the node with the specified id from the binary heap
        //
        // If pKey is supplied, write to that address the key of the node being
        // deleted. If ppData is supplied, write to that address the associated
        // void pointer.
        //
        // Returns:
        //   0 on success
        //   1 if a node with the given id does not exist
        //
        int remove(const std::string &id, int *pKey = NULL,
                void *ppData = NULL);

    private:
        class Node {
            public:
                std::string id; // The id of this node
                int key; // They key of this node
                void *pData; // A pointer to the actual data
        };

        int capacity;
        int size;

        std::vector<Node> data; // The actual binary heap
        HashTable *mapping; // Maps ids to node pointers

        void percolateUp(int currentPos);
        void percolateDown(int currentPos);
        int getPos(Node *pn);
};

#endif //_HEAP_H_

