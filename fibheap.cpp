#include <iostream>
#include <vector>
using namespace std;

/*
	Test your implementations
	If you can, test other features as well
*/

class HeapNode {
	int value; //data in node
	bool marked; // flag to check if a node has had children removed
	HeapNode *prev, *next; // List Pointers
	HeapNode *parent;
	vector<HeapNode *> children;
public:
	HeapNode(int newVal){
		value = newVal;
		prev = nullptr;
		next = nullptr;
		parent = nullptr;
	}
	int getValue(){
		return value;
	}
	HeapNode * getNext(void){
		return next;
	}
	HeapNode * getPrev(void){
		return prev;
	}
	HeapNode * getParent(void){
		return parent;
	}
	vector<HeapNode *> getChildren(void){
		return children;
	}
	void setNext(HeapNode *newNode){
		next = newNode;
	}
	void setPrev(HeapNode *newNode){
		prev = newNode;
	}
	void setParent(HeapNode *newNode){
		parent = newNode;
	}
};

/*
	Required Functions:
	*	findMin
		deleteMin
	*	insert
		decreaseKey
	*	merge
*/
class Heap {
	HeapNode *min; // min functions as the root node of the Fibonacci Heap

public:
	Heap(void){ // Constructor
		min = nullptr; // Heap starts out empty
	}

	// Check if the Fib Heap is empty or not
	bool isEmpty(void){ // Check if heap is empty
		return min == nullptr; 
	}

	// Insert a node into the Fib Heap
	// Node inserted will be a new root in the list of roots
	void insert(HeapNode *node){ // Insert a node into the heap
		if (isEmpty()){
			node->setNext(node);
			node->setPrev(node);
			min = node;
		} else {
			node->setNext(min->getNext());
			node->setPrev(min);
			node->getNext()->setPrev(node);
			min->setNext(node);
			if (node->getValue() < min->getValue()){
				min = node;
			}
		}
	}
	
	// Returns the min value in the Fib Heap
	int findMin(void){
		return min->getValue();
	}
	
	// TODO - Delete Min
	// Div
	// Delete the node with the minimum value and reorganize Fib Heap
	void deleteMin(void){ // TODO
		// Connect the children
		HeapNode *temp = min->getPrev();
		for (auto it = min->getChildren().begin(); it != min->getChildren().end(); it++){
			cout << (*it)->getValue() << endl;
			(*it)->setPrev(temp);
			temp->setNext(*it);
			temp = (*it);
		}
		temp->setNext(min->getNext());
		temp->getNext()->setPrev(temp);
		// Get rid of A and 
	}
	
	// TODO - Decrease Key
	// Jack
	// Decrease the key of a node and change tree if needed
	
	
	// TODO - Merge
	// Maybe done - Drew
	// Merge two Fib Heaps
	
	
	// Getter for the node with the minimum value
	HeapNode * getMin(){
		return min;
	}
	
	// Update the minimum node in the tree to a new node
	void updateMin(HeapNode *newMin){
		min = newMin;
	}
};

int main(void){
	//Little test for insert
	Heap* heap = new Heap();
	heap->insert(new HeapNode(5));
	heap->insert(new HeapNode(3));
	heap->insert(new HeapNode(2));
	heap->insert(new HeapNode(4));
	heap->insert(new HeapNode(1));
	HeapNode *trav = heap->getMin();
	for (int i = 0; i < 10; i++){
		printf("%d\n", trav->getValue());
		trav = trav->getNext();
	}
	return 0;
}