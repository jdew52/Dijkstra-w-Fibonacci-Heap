#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include "fibheap.h"

using namespace std;

// Data structure for an outgoing edge
struct Edge {
    Edge(int dst, int weight) {
        this->dst = dst;
        this->weight = weight;
    }
    int dst;
    int weight;
};


class Graph {
public:
    Graph(int size);
    ~Graph();

    // Generates a directed graph with N nodes, which is worst case for Dijkstra's algorithm
    static Graph generateWorstCaseGraph(int n);

    // Adds a directed edge to the graph
    void addEdge(int u, int v, int weight);

    // Auxiliary function to print graph with edge weights
    void printGraph();

    // Getx all adjacent nodes of another
    vector<Edge> getAdj(int u);

    // Getx pointer to the ith node's corresponding heap node
    HeapNode* getNode(int i);

    // Setx pointer to the ith node's corresponding heap node
    void setNode(int i, HeapNode* node);

    // Initializex a PQ for given source
    Heap* initPQ(int source);

    // Printx distance values for all nodes in graph
    void printSpanningTree();

private:
    int size;                   // # Nodes in graph.
    vector<Edge>* adjacenyList; // Outgoing edges for each node of graph.
    HeapNode** nodes;           // Pointers to corresponding HeapNodes in PQ
};


// NOTE: This implementation assumes that the graph source is node 0
void dijkstra(Graph* graph, bool debugEnabled);

#endif // GRAPH_H
