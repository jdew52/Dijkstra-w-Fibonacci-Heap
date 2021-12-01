#include "graph.h"
#include <iostream>
#include <iterator>
#include <vector>

// Constructor
Graph::Graph(int size) {
    this->size = size;
    this->adjacenyList = new vector<Edge>[size];
    this->nodes = new Node[size];
}

// Destructor
Graph::~Graph() {
    // Delete all elements of adjacency lists
    for (int v = 0; v < this->size; v++)
    {
        this->adjacenyList[v].clear();
    }
}

/*
    Implements algorithm described in:
    https://ir.canterbury.ac.nz/bitstream/handle/10092/13567/vickers_report_1986.pdf?sequence=1&isAllowed=y
*/
Graph Graph::generateWorstCaseGraph(int n) {
    Graph G = Graph(n);

    int nextCost = 2;
    for (int v = 0; v < n - 1; v++) {
        G.addEdge(v, v+1, 1);
    }

    for (int i = n - 3; i >= 0; i--) {
        nextCost += 1;
        for (int j = i + 2; j < n; j++) {
            G.addEdge(i, j, nextCost);
            nextCost += 1;
        }
    }

    return G;
}

void Graph::addEdge(int u, int v, int weight)
{
    if (u < size && v < size) {
        this->adjacenyList[u].push_back(Edge(v, weight));
    }
}

void Graph::printGraph()
{
    for (int v = 0; v < this->size; v++)
    {
        cout << "\n Adjacency list of vertex " << v << "\n (head) ";

        for(vector<Edge>::iterator it = this->adjacenyList[v].begin();
                                   it != this->adjacenyList[v].end(); it++) {
            cout << " --" << (*it).weight << "-> (" << (*it).dst << ")";
        }
        printf("\n");
    }
}


// void dijkstra(Graph graph, int source) {
//     int edgeWeight;
//
//     // TODO: Initialize PQ with ALL nodes of graph. Set source node
//
//     while (!pq.empty()) {
//         // u = Pop(&pq);
//         Node u = new Node();
//
//         for(vector<Edge>::iterator it = graph.adjacenyList[u].begin();
//                                    it != graph.adjacenyList[u].end(); it++) {
//            edgeWeight = (*it).weight;
//
//            if (u.distance + edgeWeight < graph.nodes[(*it).dst].distance) {
//                // Update edge distance in map
//                graph.nodes[u].distance = graph.nodes[u].distance + edgeWeight;
//
//                // TODO: Decrease key in PQ
//            }
//         }
//     }
// }
