#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include "fibheap.h"

using namespace std;

struct Node {
    static const int inf = 10000000;
    // Default constructor
    Node() : ref(nullptr) {};
    HeapNode* ref;  // Pointer to node in heap
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

    // Get all adjacent nodes of another
    vector<Edge> getAdj(int u);

    // Get pointer the ith node's corresponding heap node
    HeapNode* getNode(int i);

    // Set pointer the ith node's corresponding heap node
    void setNode(int i, HeapNode* node);

    // Initialize a PQ for given source
    Heap* initPQ(int source);

private:
    int size;
    vector<Edge>* adjacenyList;
    HeapNode** nodes;
};


void dijkstra(Graph* graph, int source);

#endif // GRAPH_H
