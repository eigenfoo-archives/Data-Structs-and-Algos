#include "graph.h"

void graph::loadGraph(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::string vertex1, vertex2, cost;
    node *pVertex2;
    bool inHashTable;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> vertex1;
        iss >> vertex2;
        iss >> cost;

        if (!this->nodeHash.contains(vertex2)) {
            node newNode = {.name = vertex2,
                            .d = INT_MAX,
                            .p = nullptr,
                            .known = false,
                            .adjacency = {}};
            this->graphNodes.push_back(newNode);
            this->nodeHash.insert(vertex2, &newNode); // FIXME is this right?
        }

        if (!this->nodeHash.contains(vertex1)) {
            pVertex2 = static_cast<node *>(this->nodeHash.getPointer(vertex2,
                        &inHashTable));
            edge newEdge = {.dest = pVertex2,
                            .cost = stoi(cost)};
            node newNode = {.name = vertex1,
                            .d = INT_MAX,
                            .p = nullptr,
                            .known = false,
                            .adjacency = {newEdge}};
            this->graphNodes.push_back(newNode);
            this->nodeHash.insert(vertex1, &newNode); // FIXME is this right?
        }
    }

    // TODO construct edgeHeap
}

void graph::dijkstra(std::string startingVertex) {

}
