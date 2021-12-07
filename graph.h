#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include "fibheap.h"

using namespace std;

struct Node {
    static const int inf = 10000000;
    // Default constructor
    Node() : visited('F'), distance(inf) {}
    char visited;   // Keeps track if node has been visited (T), not visited and not in queue (F), or not visited and in queue (Q)
    int distance;   // Distance from source node
    HeapNode* ref;  // Reference to node in heap
};


struct Edge {
    Edge(int dst, int weight) {
        this->dst = dst;
        this->weight = weight;
    }
    int dst;
    int weight;
};


// NOTE: This graph data structure assumes that the graph starts at node 0
class Graph {
public:
    Graph(int size);
    ~Graph();

    // Generate a directed graph with N nodes, which is worst case for Dijkstra's algorithm
    static Graph generateWorstCaseGraph(int n);

    // Add a directed edge to the graph
    void addEdge(int u, int v, int weight);

    // Auxiliary function to print graph with edge weights
    void printGraph();

private:
    int size;
    vector<Edge>* adjacenyList;
    Node* nodes;
};


void dijkstra(Graph* graph, int source);

#endif // GRAPH_H
