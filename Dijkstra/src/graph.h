#ifndef GRAPH_H
#define GRAPH_H

#include <climits>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include "hash.h"
#include "heap.h"

class graph {
    struct edge;

    public:
        void loadGraph(std::string fileName);
        void dijkstra(std::string startingVertex);
        void outputDijkstra(std::string startingVertex,
                std::string fileName);
        bool isValidVertex(std::string vertexName);

    private:
        struct node {
            std::string name;
            int d;
            node *p;
            bool known;
            std::list<edge> adjacency;
        };

        struct edge {
            node *dest;
            int cost;
        };

        std::list<node> graphNodes;
        hashTable nodeHash;
};

#endif // GRAPH_H
