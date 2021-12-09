#include <iostream>
#include "fibheap.h"

/*
	Test your implementations
	If you can, test other features as well
*/

// Constructor
HeapNode::HeapNode(int newVal) {
	this->value = newVal;
	this->marked = false;
	this->prev = nullptr;
	this->next = nullptr;
	this->parent = nullptr;
	this->children = nullptr;
	this->deg = 0;
}

bool HeapNode::isMarked() {
    return this->marked;
}

int HeapNode::getDegree() {
    return this->deg;
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
HeapNode * HeapNode::getChildren() {
	return this->children;
}
void HeapNode::setValue(int newValue){
    this->value = newValue;
}
void HeapNode::setMarked() {
    this->marked = !this->marked;
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
void HeapNode::setChildren(HeapNode *newNode) {

	newNode->setNext(newNode);
	newNode->setPrev(newNode);
    this->children = newNode;
}

void HeapNode::addChildren(HeapNode *newNode){
    this->deg++;
	if (this->getChildren() == nullptr){
        setChildren(newNode);
        return;
    }
	
	newNode->setNext(this->children);
	newNode->setPrev(this->children->getPrev());
	this->children->getPrev()->setNext(newNode);
	this->children->setPrev(newNode);
	this->children = newNode;

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
}
// Destructor
Heap::~Heap() {
    this->min = nullptr;
}


Heap* Heap::merge(Heap* a, Heap* b) {
    Heap* newHeap = new Heap;
    HeapNode* a_min = a->getMin();
    HeapNode* b_min = b->getMin();

    if (a_min->getValue() < b_min->getValue()) {
        // Set new min of combined heap and make it the head
        newHeap->updateMin(a_min);
    } else {
        // Set new min of combined heap and make it the head
        newHeap->updateMin(b_min);
    }
    // Concatenate root lists
    HeapNode* temp = a_min->getPrev();
    a_min->getPrev()->setNext(b_min);
    a_min->setPrev(b_min->getPrev());
    b_min->getPrev()->setNext(a_min);
    b_min->setPrev(temp);

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
	if (this->isEmpty()) {
        node->setNext(node);
        node->setPrev(node);
		this->min = node;
	} else {
        node->setNext(min->getNext());
		node->setPrev(this->min);
		node->getNext()->setPrev(node);
		this->min->setNext(node);
		if (node->getValue() < this->min->getValue()){
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

int Heap::deleteMin() { // TODO
	// Connect the children
	HeapNode *temp = this->min->getPrev();
	
	//To Check if it is the last node
	if (this->getMin()->getNext() == this->min && this->min->getChildren() == nullptr) {  // Only 1 node left
        this->min = nullptr;
        this->updateMin(nullptr);
        return 1;
    }

	int minChildCount = 0;
	
	//Used to add children in main root heap
	HeapNode* it = this->min->getChildren();
	//Loop to add children in root list
	if(this->min->getChildren() != nullptr){
		do
		{
			temp->setNext(it);
			it->setPrev(temp);
			temp = it;
			it = it->getNext();
		}	while(it != this->min->getChildren());
	
	}
	temp->setNext(this->min->getNext());
	temp->getNext()->setPrev(temp);
	this->updateMin(temp);
	
	//Finding new Min value
	int minVal = temp->getValue();
	HeapNode* tempMin = temp;
	do {
		
		if (minVal > temp->getValue()) {
			tempMin = temp;
            minVal = tempMin->getValue();
		}

		temp = temp->getNext();
		
	} while(temp != min);
	this->updateMin(tempMin);
	
	temp = temp->getNext();;
	
	do{
		minChildCount++;
		tempMin = tempMin->getNext();
	}while(tempMin != this->min);
	
	minChildCount = 100;
	
	HeapNode* cons[minChildCount];

	for (int i = 0; i < minChildCount; i++)
	{
		cons[i] = nullptr;
	}
	
    if (minChildCount != 0) {
    	do {
			int degree = temp->getDegree();
			
			if(cons[degree] == temp){
				break;
			}
			
			if(degree != 0)
			{
				it = temp->getChildren();
				do
				{
					it = it->getNext();
				}	while(it != temp->getChildren());
			}
			
    		if (cons[degree] == nullptr) {
    			cons[degree] = temp;
    			temp = temp->getNext();
    		}
			
    		else {
    			cons[degree]->getNext()->setPrev(cons[degree]->getPrev());
    			cons[degree]->getPrev()->setNext(cons[degree]->getNext());
				cons[degree]->setNext(nullptr);
   				cons[degree]->setPrev(nullptr);

				//cout<<cons[degree]->getValue()<<endl;
				
    			if (cons[degree]->getValue() >= temp->getValue()) {
					    				
    				temp->addChildren(cons[degree]);
					cons[degree]->setParent(temp);
					
    			}
    			else {
    				cons[degree]->setNext(temp->getNext());
    				cons[degree]->setPrev(temp->getPrev());
					temp->getNext()->setPrev(cons[degree]);
					temp->getPrev()->setNext(cons[degree]);
    				temp->setNext(nullptr);
    				temp->setPrev(nullptr);
    				cons[degree]->addChildren(temp);
					temp->setParent(cons[degree]);
    				temp = cons[degree];
    			}
    			cons[degree] = nullptr;
    		}
			

    	} while(1);
		//this->min->getPrev()->setNext(this->min);
    }
	
	temp = nullptr;
	
	for(int i=0; i<minChildCount; i++){
		if(cons[i] != nullptr){
			if(temp == nullptr)
			{
				temp = cons[i];
				temp->setNext(temp);
				temp->setPrev(temp);
				tempMin = temp;
			}
			else{
				temp->setNext(cons[i]);
				cons[i]->setPrev(temp);
				tempMin->setPrev(cons[i]);
				cons[i]->setNext(tempMin);
				temp = cons[i];
			}
		}
	}
	
	
	
	return 0;
}


void Heap::moveToRoot(HeapNode *node){
    if (node->getParent() == nullptr){
        return;
    }
    // Cut off the parent and child
    // Change child ptr if needed
    if (node->getParent()->getChildren() == node){
        node->getParent()->setChildren(node->getNext());
    }
    node->setParent(nullptr); // Remove node's parent
    // Redo linking of child list
    if (node->getPrev() != nullptr) {
        node->getPrev()->setNext(node->getNext());
    }
    if (node->getNext() != nullptr) {
        node->getNext()->setPrev(node->getPrev());
    }
    // Insert node into root list
    this->insert(node);
}

// TODO - Decrease Key
// Decrease the key of a node and change tree if needed
void Heap::decreaseKey(HeapNode *node, int newValue){
    if (this->min == nullptr){
        return;
    }
    if (node == nullptr){
        return;
    }
    node->setValue(newValue);
    // if heap property is violated
    if (node->getParent() != nullptr && node->getValue() < node->getParent()->getValue()){
        HeapNode *parent = node->getParent();
        while (parent->isMarked()){
            this->moveToRoot(node);
            node = parent;
            parent = node->getParent();
        }
        this->moveToRoot(node);
        parent->setMarked();
    } else if (node->getValue() < min->getValue()){
        min = node;
    }
}


// Getter for the node with the minimum value
HeapNode* Heap::getMin() {
	return this->min;
}

// Update the minimum node in the tree to a new node
void Heap::updateMin(HeapNode *newMin) {
	this->min = newMin;
}

// Function to display roots of the heap
void Heap::displayRoots() {
    HeapNode* temp = this->getMin();

    if (this->isEmpty())
        cout << "\nThe heap is empty" << endl;
    else {
        cout << "\nThe root nodes of heap are: " << endl;
        do {
			//cout<<endl;
            cout << temp->getValue();
            temp = temp->getNext();

            if (temp != min) {
                cout << "-->";
            }
        } while (temp != min);
        cout << endl;
    }
}
