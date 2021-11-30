#include <iostream>
#include <vector>
#include <iterator>
#include <stdio.h> // Needed for command line args

// NOTE: This graph data structure assumes that the graph starts at node 0
using namespace std;


struct Node {
    static const int inf = 10000000;
    // Default constructor
    Node() : visited('F'), distance(inf) {
    }
    char visited;   // Keeps track if node has been visited (T), not visited and not in queue (F), or not visited and in queue (Q)
    int distance;   // Distance from source node
};


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
    // Constructor
    Graph(int size) {
        this->size = size;
        this->adjacenyList = new vector<Edge>[size];
        this->nodes = new Node[size];
    }

    // Destructor
    ~Graph() {
        // Delete all elements of adjacency lists
        for (int v = 0; v < this->size; v++)
        {
            this->adjacenyList[v].clear();
        }
    }

    // Generate a directed graph with N nodes, which is worst case for Dijkstra's algorithm
    /*
        Implements algorithm described in:
        https://ir.canterbury.ac.nz/bitstream/handle/10092/13567/vickers_report_1986.pdf?sequence=1&isAllowed=y
    */
    static Graph generateWorstCaseGraph(int n) {
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

    // Add a directed edge to the graph
    void addEdge(int u, int v, int weight)
    {
        if (u < size && v < size) {
            this->adjacenyList[u].push_back(Edge(v, weight));
        }
    }

    // Auxiliary function to print graph with edge weights
    void printGraph()
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

private:
    int size;
    vector<Edge>* adjacenyList;
    Node* nodes;
};


// Test Graph class
int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Please provide size of graph as command line argument" << endl;
    }
    else {
        // Generate worst cast graph of size N
        cout << "Creating graph of size " << argv[1] << endl;
        Graph G = Graph::generateWorstCaseGraph(atoi(argv[1]));
        G.printGraph();
    }

    return 0;
}
