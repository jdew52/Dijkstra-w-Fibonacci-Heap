#include "graph.h"
#include <iostream>
#include <iterator>
#include <vector>

// Constructor
Graph::Graph(int size) {
    this->size = size;
    this->adjacenyList = new vector<Edge>[size];
    this->nodes = new HeapNode*[size];
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



HeapNode* Graph::getNode(int i) {
    return this->nodes[i];
}

void Graph::setNode(int i, HeapNode* node) {
    this->nodes[i] = node;
}

Heap* Graph::initPQ(int source) {
    // Set source node
    Heap* pq = new Heap();
    this->setNode(source, new HeapNode(source, 0));
    pq->insert(this->getNode(source));

    // Initialize PQ with ALL other nodes of graph
    for (int i = 0; i < this->size; i++)
    {
        if (i != source) {
            // Set pointer to node in heap
            this->setNode(i, new HeapNode(i, Node::inf));
            pq->insert(this->getNode(i));
        }
    }

    return pq;
}

vector<Edge> Graph::getAdj(int u) {
    return this->adjacenyList[u];
}

// Note: Node 0 is ALWAYS assumed to be start node.
void dijkstra(Graph* graph) {
    int edgeWeight = 0;
    HeapNode* v = nullptr;

    Heap* pq = graph->initPQ(0);
    // while (!pq->isEmpty()) {
    //     // Extract and delete minimum
    //     HeapNode* u = pq->extractMin();
    //
    //     // Iterate through all neighbors
    //     vector<Edge> neighbors = graph->getAdj(u->getId());
    //     for(vector<Edge>::iterator it = neighbors.begin();
    //                                it != neighbors.end(); it++) {
    //        edgeWeight = (*it).weight;
    //        v = graph->getNode((*it).dst);
    //
    //        // Perform edge relaxation where necessary
    //        if (u->getValue() + edgeWeight < v->getValue()) {
    //            // Decrease key in PQ using heapnode reference
    //            pq->decreaseKey(v, u->getValue() + edgeWeight);
    //        }
    //     }
    // }
}
