#include "graph.h"

void graph::loadGraph(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::string vertex1, vertex2, cost;
    node *pVertex1, *pVertex2;
    bool inHashTable;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> vertex1 >> vertex2 >> cost;

        // If this is the first time we're seeing either node, push them onto
        // the list and hash table
        if (!this->nodeHash.contains(vertex1)) {
            node newNode = {.name = vertex1,
                            .d = INT_MAX,
                            .p = nullptr,
                            .known = false,
                            .adjacency = {}};
            this->graphNodes.push_back(newNode);
            this->nodeHash.insert(vertex1, &newNode); // FIXME is it &newNode?
        }

        if (!this->nodeHash.contains(vertex2)) {
            node newNode = {.name = vertex2,
                            .d = INT_MAX,
                            .p = nullptr,
                            .known = false,
                            .adjacency = {}};
            this->graphNodes.push_back(newNode);
            this->nodeHash.insert(vertex2, &newNode); // FIXME is it &newNode?
        }

        // Add the edge to vertex1's adjacency list
        pVertex1 = static_cast<node *>(this->nodeHash.getPointer(vertex1,
                    &inHashTable));
        pVertex2 = static_cast<node *>(this->nodeHash.getPointer(vertex2,
                    &inHashTable));
        edge newEdge = {.dest = pVertex2,
                        .cost = stoi(cost)};
        pVertex1->adjacency.push_back(newEdge);
    }
}

void graph::dijkstra(std::string startingVertex) {
    heap edgeHeap(graphNodes.size());

    node *pStartingVertex
        = static_cast<node *>(this->nodeHash.getPointer(startingVertex));
    pStartingVertex->d = 0;

    for (edge startingEdge : pStartingVertex->adjacency) {
        edgeHeap.insert(startingEdge.dest->name, startingEdge.cost, &startingEdge);
    }

    std::string *pId;
    int *pKey;
    node *pData;
    void *ppData;

    while (!edgeHeap.deleteMin(pId, pKey, ppData)) {
        pData = static_cast<node *>(ppData); 
        pData->known = true;

        for (edge adjacentEdge : pData->adjacency) {
            // TODO finish Dijkstra main loop
        }
    }
}
