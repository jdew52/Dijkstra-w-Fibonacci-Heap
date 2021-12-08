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
    this->children = newNode;
	this->deg++;
}
void HeapNode::addChildren(HeapNode *newNode) {
    HeapNode* temp = this->children;
	if(this->children == nullptr){
		setChildren(newNode);
	}
	else{
		this->children = newNode;
		newNode->setNext(temp);
		temp->setPrev(newNode);
		this->deg++;
	}
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
    
	if (this->getMin() == temp) {  // Only 1 node left
        this->min = nullptr;
        this->updateMin(nullptr);
        return 1;
    }

	int minChildCount = 0;
	
	if(min->getChildren() != nullptr){
		HeapNode* it = this->min->getChildren();
		HeapNode* currentChild = it->getPrev();;
		for(int d = this->min->getDegree(); d > 0; d--) {
			cout << it->getValue() << endl;
			//cout<<"loop 1\n";
			it->setPrev(temp);
			temp->setNext(it);
			it->setParent(nullptr);
			temp = it;
			it = currentChild;
			if(it != nullptr)
				currentChild = it->getNext();
		}
		temp->setNext(this->min->getNext());
		temp->getNext()->setPrev(temp);	
	}
	
	else{
		temp->setNext(this->min->getNext());
		temp->getNext()->setPrev(temp);
	}
	
	this->updateMin(temp);
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
	
	temp = this->min;
	
	do{
		minChildCount++;
		//cout<<"loop 2\n";
		//cout<<temp->getValue()<<endl;
		temp = temp->getNext();
	}while(temp != this->min);
	
	HeapNode* cons[minChildCount];
	temp = this->min;

	for (int i = 0; i < minChildCount; i++)
	{
		cons[i] = nullptr;
	}
	this->displayRoots();
	//this->min->getPrev()->setNext(nullptr);
	//this->min->setPrev(nullptr);
	
    if (minChildCount != 0) {
    	do {
			int degree = temp->getDegree();
			
			if(cons[degree] == temp){
				break;
			}
			
			cout<<"Inside Loop"<<endl;
			cout<<"Current root node value: "<<temp->getValue()<<endl;
			cout<<"Degree: "<<degree<<endl;
			
    		if (cons[degree] == nullptr) {
				cout<<"Inside IF"<<endl;
    			cons[degree] = temp;
    			temp = temp->getNext();
				cout<<temp->getValue();
    		}
			
    		else {
				cout<<"Inside Else"<<endl;
				
    			cons[degree]->getNext()->setPrev(cons[degree]->getPrev());
    			cons[degree]->getPrev()->setNext(cons[degree]->getNext());
				cons[degree]->setNext(nullptr);
   				cons[degree]->setPrev(nullptr);

				//cout<<cons[degree]->getValue()<<endl;
				
    			if (cons[degree]->getValue() >= temp->getValue()) {
					
					cout<<"Inside If 2"<<endl;
    				
    				temp->addChildren(cons[degree]);
					cons[degree]->setParent(temp);
					
    			}
    			else {
					cout<<"Inside Else 2"<<endl;
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
