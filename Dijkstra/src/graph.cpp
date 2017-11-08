#include <iostream>
#include "graph.h"

void graph::loadGraph(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::string vertex1, vertex2, cost;
    node *pVertex1, *pVertex2;
    
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
            this->nodeHash.insert(vertex1, &this->graphNodes.back());
        }

        if (!this->nodeHash.contains(vertex2)) {
            node newNode = {.name = vertex2,
                            .d = INT_MAX,
                            .p = nullptr,
                            .known = false,
                            .adjacency = {}};
            this->graphNodes.push_back(newNode);
            this->nodeHash.insert(vertex2, &this->graphNodes.back());
        }

        // Add the edge.dest vertex1's adjacency list
        pVertex1 = static_cast<node *>(this->nodeHash.getPointer(vertex1));
        pVertex2 = static_cast<node *>(this->nodeHash.getPointer(vertex2));
        edge newEdge = {.dest = pVertex2,
                        .cost = stoi(cost)};
        pVertex1->adjacency.push_back(newEdge);
    }

    infile.close();
}

void graph::dijkstra(std::string startingVertex) {
    node *pStartingVertex
        = static_cast<node *>(this->nodeHash.getPointer(startingVertex));
    pStartingVertex->d = 0;
    pStartingVertex->p = pStartingVertex;

    // Build heap of unknown vertices
    heap unknownHeap(this->graphNodes.size());
    for (node unknownNode : this->graphNodes) {
        unknownHeap.insert(unknownNode.name, unknownNode.d); //, &unknownNode);
    }

    std::string currentName = "";
    int currentCost = 0;
    node *pCurrentNode = nullptr;

    while (!unknownHeap.deleteMin(&currentName, &currentCost)) { // , &pCurrentNode)) {
        pCurrentNode = static_cast<node *>(this->nodeHash.getPointer(currentName));
        pCurrentNode->known = true;

        for (edge outgoingEdge : pCurrentNode->adjacency) {
            if (!outgoingEdge.dest->known &&
                    pCurrentNode->d + outgoingEdge.cost < outgoingEdge.dest->d) {
                outgoingEdge.dest->d = pCurrentNode->d + outgoingEdge.cost;
                unknownHeap.setKey(outgoingEdge.dest->name,
                        pCurrentNode->d + outgoingEdge.cost);
                outgoingEdge.dest->p = pCurrentNode;
            }
        }
    }
}

void graph::outputDijkstra(std::string startingVertex, std::string fileName) {

    std::ofstream outfile(fileName);
    std::string line = "";
    std::string path = "";
    node tmp = *this->graphNodes.begin();

    for (node graphNode : this->graphNodes) {
        tmp = graphNode;
        path = graphNode.name; 
        while (tmp.name != startingVertex) {
            if (tmp.p != nullptr) {
                tmp = *tmp.p;
                path = tmp.name + ", " + path;
            }
            else {
                path = "NO PATH\n";
                break;
            }
        }

        if (path != "NO PATH\n") {
            line = graphNode.name + ": " + std::to_string(graphNode.d)
                + " [" + path + "]\n";
        }
        else {
            line = graphNode.name + ": " + path;
        }

        outfile << line;
    }

    outfile.close();
}

bool graph::isValidVertex(std::string vertexName) {
    return this->nodeHash.contains(vertexName);
}
