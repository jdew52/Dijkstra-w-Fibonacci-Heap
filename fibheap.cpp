#include <iostream>
#include "fibheap.h"

/*
	Test your implementations
	If you can, test other features as well
*/

// Constructor
HeapNode::HeapNode(int newVal){
	this->value = newVal;
	this->prev = nullptr;
	this->next = nullptr;
	this->parent = nullptr;
}

int HeapNode::getValue() {
	return this->value;
}
HeapNode* HeapNode::getNext() {
	return this->next;
}
HeapNode* HeapNode::getPrev() {
	return this->prev;
}
HeapNode* HeapNode::getParent() {
	return this->parent;
}
vector<HeapNode *> HeapNode::getChildren() {
	return this->children;
}
void HeapNode::setNext(HeapNode *newNode) {
	this->next = newNode;
}
void HeapNode::setPrev(HeapNode *newNode) {
	this->prev = newNode;
}
void HeapNode::setParent(HeapNode *newNode) {
	this->parent = newNode;
}


/*
	Required Functions:
	*	findMin
		deleteMin
	*	insert
		decreaseKey
	*	merge
*/
Heap::Heap() { // Constructor
	this->min = nullptr; // Heap starts out empty
    this->head = nullptr;
}
// Destructor
Heap::~Heap() {
    this->min = nullptr;
    this->head = nullptr;
}

// TODO: Merge two Fib Heaps
Heap* Heap::merge(Heap* a, Heap* b) {
    Heap* newHeap = new Heap;
    HeapNode* a_min = a->getMin();
    HeapNode* b_min = b->getMin();

    if (a_min->getValue() < b_min->getValue()){
        // Set new min of combined heap and make it the head
        newHeap->updateMin(a_min);
        newHeap->updateHead(a_min);
    } else{
        // Set new min of combined heap and make it the head
        newHeap->updateMin(b_min);
        newHeap->updateHead(b_min);
    }
    // Concatenate root lists
    // b_min->getNext()->setNext(a_min->getNext());
    // a_min->getNext()->setPrev(b_min->getNext());
    // a_min->setNext(b_min);

    // Cleanup memory associated with previous heaps.
    delete a;
    delete b;

    return newHeap;
}


// Generate a random heap of a size
Heap* Heap::generateHeap(int size) {
    Heap* heap = new Heap();

    for (int i = 0; i < size; i++) {
        heap->insert(new HeapNode(rand() % 25));
    }
    return heap;
}

// Check if the Fib Heap is empty or not
bool Heap::isEmpty() { // Check if heap is empty
	return this->min == nullptr;
}

// Insert a node into the Fib Heap
// Node inserted will be a new root in the list of roots
void Heap::insert(HeapNode* node) { // Insert a node into the heap
	if (this->isEmpty()){
        cout << "Heap is empty. Making node " << node->getValue() << " the min and head" << endl;
		this->min = node;
		this->head = node;
	} else {
		node->setNext(head);
		this->head->setPrev(node);
		this->head = node;
		if (node->getValue() < this->min->getValue()){
            cout << "The minimum was updated to " << node->getValue() << endl;
			this->min = node;
		}
	}
}

// Returns the min value in the Fib Heap
int Heap::findMin() {
	return this->min->getValue();
}

// TODO - Delete Min
// Div
// Delete the node with the minimum value and reorganize Fib Heap
void Heap::deleteMin() { // TODO
	// Connect the children
	HeapNode *temp = this->min->getPrev();
	for (auto it = this->min->getChildren().begin(); it != this->min->getChildren().end(); it++){
		// cout << (*it)->getValue() << endl;
		(*it)->setPrev(temp);
		temp->setNext(*it);
		temp = (*it);
	}
	temp->setNext(this->min->getNext());
	temp->getNext()->setPrev(temp);
	// Get rid of A and
}

// TODO - Decrease Key
// Jack
// Decrease the key of a node and change tree if needed


// Getter for the node with the minimum value
HeapNode* Heap::getMin() {
	return this->min;
}

// Getter for head node
HeapNode* Heap::getHead() {
	return this->head;
}

// Update the minimum node in the tree to a new node
void Heap::updateMin(HeapNode *newMin) {
	this->min = newMin;
}

// Update the head node in Fib Heap to a new node
void Heap::updateHead(HeapNode *newHead) {
	this->head = newHead;
}

// Function to display roots of the heap
void Heap::displayRoots() {
    HeapNode* temp = this->getHead();

    if (this->isEmpty())
        cout << "\nThe heap is empty" << endl;
    else {
        cout << "\nThe root nodes of heap are: " << endl;
        do {
            cout << temp->getValue();
            temp = temp->getNext();

            if (temp != nullptr) {
                cout << "-->";
            }
        } while (temp != nullptr);
        cout << endl;
    }
}
