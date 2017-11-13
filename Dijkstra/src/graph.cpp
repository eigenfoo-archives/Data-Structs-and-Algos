/*
 * Data Structures and Algorithms II Assignment #3: Dijkstra
 * George Ho, Fall 2017
 * 
 * This code implements a graph class for the purposes of running Dijkstra's
 * algorithm.
 */

#include <iostream>
#include "graph.h"

// Reads text file and constructs graph
void graph::loadGraph(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::string vertex1, vertex2, cost;
    node *pVertex1, *pVertex2;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> vertex1 >> vertex2 >> cost;

        // If this is the first time we're seeing either node, push them onto
        // the list and hash table, in the order they appear
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

        // Add edge.dest to vertex1's adjacency list
        pVertex1 = static_cast<node *>(this->nodeHash.getPointer(vertex1));
        pVertex2 = static_cast<node *>(this->nodeHash.getPointer(vertex2));
        edge newEdge = {.dest = pVertex2,
                        .cost = stoi(cost)};
        pVertex1->adjacency.push_back(newEdge);
    }

    infile.close();
}

// Run Dijkstra's algorithm
void graph::dijkstra(std::string startingVertex) {
    node *pStartingVertex
        = static_cast<node *>(this->nodeHash.getPointer(startingVertex));
    pStartingVertex->d = 0;
    pStartingVertex->p = pStartingVertex;

    // Build heap of unknown vertices
    heap unknownHeap(this->graphNodes.size());
    for (std::list<node>::iterator it = this->graphNodes.begin();
            it != this->graphNodes.end(); it++) {
        unknownHeap.insert(it->name, it->d, &(*it));
    }

    std::string currentName = "";
    int currentCost = 0;
    node *pCurrentNode = nullptr;

    while (!unknownHeap.deleteMin(&currentName, &currentCost, &pCurrentNode)) {
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

// Output results of Dijkstra's algorithm to an output text file
void graph::outputDijkstra(std::string startingVertex, std::string fileName) {
    std::ofstream outfile(fileName);
    std::string line = "";
    std::string path = "";
    node currentNode = *this->graphNodes.begin();

    // Attempt to find a path from each node to the starting node
    for (node graphNode : this->graphNodes) {
        currentNode = graphNode;
        path = graphNode.name; 
        while (currentNode.name != startingVertex) {
            // If any node along this attempted path does not point to a node,
            // there is no path from the starting vertex to the given node
            if (currentNode.p != nullptr) {
                currentNode = *currentNode.p;
                path = currentNode.name + ", " + path;
            }
            else {
                path = "NO PATH\n";
                break;
            }
        }

        // Form line to output to file
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

// Helper function to test if a vertex is in a graph
bool graph::isValidVertex(std::string vertexName) {
    return this->nodeHash.contains(vertexName);
}
