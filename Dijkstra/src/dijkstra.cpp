#include <chrono>
#include <iostream>
#include "graph.h"

std::chrono::time_point<std::chrono::system_clock> startTimer();
float stopTimer(std::chrono::time_point<std::chrono::system_clock> startTime);

int main() {
    std::string filename = "";
    std::cout << "Enter name of graph file: ";
    std::cin >> filename;

    graph theGraph;
    theGraph.loadGraph(filename);

    std::string vertexName = "";
    bool validVertex = false;
    while (!validVertex) {
        std::cout << "Enter a valid vertex id for the starting vertex: ";
        std::cin >> vertexName;
        if (theGraph.isValidVertex(vertexName)) {
            validVertex = true;
        }
    }

    std::chrono::time_point<std::chrono::system_clock> startTime = startTimer();
    theGraph.dijkstra(vertexName);
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: "
        << stopTimer(startTime) << std::endl;

    std::cout << "Enter name of output file: ";
    std::cin >> filename;

    theGraph.outputDijkstra(vertexName, filename);

    return 0;
}

// Returns time point
std::chrono::time_point<std::chrono::system_clock> startTimer() {
    return std::chrono::system_clock::now();
}

// Returns time elapsed in seconds
float stopTimer(std::chrono::time_point<std::chrono::system_clock> startTime) {
    std::chrono::time_point<std::chrono::system_clock> endTime =
        std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}
