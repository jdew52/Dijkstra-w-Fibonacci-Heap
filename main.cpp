#include "fibheap.h"
#include "graph.h"
#include <iostream>
#include <stdio.h> // Needed for command line args

int main(int argc, char* argv[]) {
    cout << "---------------- Testing Merge Operation ----------------" << endl;
    Heap* heap1 = Heap::generateHeap(5);
    Heap* heap2 = Heap::generateHeap(5);
    Heap* heap3 = Heap::generateHeap(3);
    heap1->insert(new HeapNode(13, 1));

    heap1->displayRoots();
    heap2->displayRoots();
    heap3->displayRoots();

    // Merging heap 1 and 2
    Heap* mergeHeap = Heap::merge(heap1, heap2);
    mergeHeap->displayRoots();

    // Merging new heap and heap 3
    mergeHeap = Heap::merge(mergeHeap, heap3);
    mergeHeap->displayRoots();

    cout << "---------------- Testing deleteMin ----------------" << endl;
    // Test deletion of all nodes
    for (int i = 0; i < 14; i++) {
        cout << "Delete count " << i+1 << endl;
        mergeHeap->deleteMin();
        if (mergeHeap->getMin() != nullptr) {
            cout << "New min: " << mergeHeap->getMin()->getValue() << endl;
        }
        mergeHeap->displayRoots();
    }
    // TODO: Test deleteMin with heap that contains children

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
