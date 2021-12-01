#include "fibheap.h"
#include "graph.h"
#include <iostream>
#include <stdio.h> // Needed for command line args

int main(int argc, char* argv[]) {
    cout << "---------------- Testing Merge Operation ----------------" << endl;
    Heap* heap1 = Heap::generateHeap(5);
    Heap* heap2 = Heap::generateHeap(5);
    heap1->displayRoots();
    heap2->displayRoots();

    // TODO: Finish merge implementation
    Heap* mergeHeap = Heap::merge(heap1, heap2);
    mergeHeap->displayRoots();

    cout << "---------------- Testing Graph Generation ----------------" << endl;
    // Generate worst cast graph of size N
    if (argc != 2) {
        cout << "Please provide size of graph as command line argument" << endl;
    }
    else {
        // Generate worst cast graph of size N
        cout << "Creating graph of size " << argv[1] << ":" << endl;
        Graph G = Graph::generateWorstCaseGraph(atoi(argv[1]));
        G.printGraph();
    }

	return 0;
}