#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <vector>

using namespace std;

class HeapNode {
public:
    // Constructor
	HeapNode(int id, int newVal);
    bool isMarked();
    int getId();
	int getValue();
    int getDegree();
	HeapNode* getNext();
	HeapNode* getPrev();
	HeapNode* getParent();
	HeapNode* getChildren();
	void setValue(int newValue);
	void setMarked();
	void setNext(HeapNode* newNode);
	void setPrev(HeapNode* newNode);
	void setParent(HeapNode* newNode);

    // Sets child pointer of a node
	void setChildren(HeapNode* newNode);

    // Appends child to "end" of child list
	void addChildren(HeapNode* newNode);

private:
    int id;                 // id in graph
    int value;              // data in node
    int deg;                // number of childern
    bool marked;            // flag to check if a node has had children removed
    HeapNode *prev, *next;  // list Pointers
    HeapNode* parent;       // sole parent
    HeapNode* children;     // first child
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
    // Node inserted will be a new root in the list of roots
	void insert(HeapNode* node);

	// Returns the min value in the Fib Heap
	int findMin();

	// Delete/return the node with the minimum value and reorganize Fib Heap
	HeapNode* extractMin();

    // Moves a node to the root list of the heap
    void moveToRoot(HeapNode* node);

	// Decrease the key of a node and change tree if needed
    void decreaseKey(HeapNode* node, int newValue);

	// Getter for the node with the minimum value
	HeapNode* getMin();

	// Update the minimum node in the tree to a new node
	void updateMin(HeapNode* newMin);

    // Function to display roots of the heap
    void displayRoots();

private:
    HeapNode* min;  // functions as the root node of the Fibonacci Heap
};

#endif // FIB_HEAP_H
