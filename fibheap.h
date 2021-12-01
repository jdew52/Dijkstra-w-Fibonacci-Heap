#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <vector>

using namespace std;

class HeapNode {
public:
    // Constructor
	HeapNode(int newVal);

	int getValue();
	HeapNode * getNext();
	HeapNode * getPrev();
	HeapNode * getParent();
	vector<HeapNode *> getChildren();
	void setNext(HeapNode *newNode);
	void setPrev(HeapNode *newNode);
	void setParent(HeapNode *newNode);

private:
    int value;   // data in node
    bool marked; // flag to check if a node has had children removed
    HeapNode *prev, *next; // List Pointers
    HeapNode *parent;
    vector<HeapNode *> children;
};


class Heap {
public:
	Heap();
    ~Heap();

    // Generate a random heap of a size
    static Heap* generateHeap(int size);

    // TODO: Merge two Fib Heaps
    static Heap* merge(Heap* a, Heap* b);

	// Check if the Fib Heap is empty or not
	bool isEmpty();

	// Insert a node into the Fib Heap
	void insert(HeapNode* node);

	// Returns the min value in the Fib Heap
	int findMin();

	// Delete the node with the minimum value and reorganize Fib Heap
	void deleteMin();

	// TODO - Decrease Key
	// Jack
	// Decrease the key of a node and change tree if needed
    void decreaseKey();

	// Getter for the node with the minimum value
	HeapNode* getMin();

	// Update the minimum node in the tree to a new node
	void updateMin(HeapNode *newMin);

    // Function to display roots of the heap
    void displayRoots();

private:
    HeapNode *min;  // min functions as the root node of the Fibonacci Heap
};

#endif // FIB_HEAP_H
