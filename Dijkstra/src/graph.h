#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <climits>
#include "hash.h"
#include "heap.h"

class graph {
    struct edge;

    public:
        void loadGraph(std::string fileName);
        void dijkstra(std::string startingVertex);

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
