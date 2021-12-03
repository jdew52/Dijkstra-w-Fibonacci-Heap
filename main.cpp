#include "fibheap.h"
#include "graph.h"
#include <iostream>
#include <stdio.h> // Needed for command line args

int main(int argc, char* argv[]) {
    Heap *heap = new Heap();
    heap->insert(new HeapNode(1));
    heap->getMin()->setChildren(new HeapNode(2));
    heap->getMin()->getChildren()->setChildren(new HeapNode(3));
    heap->decreaseKey(heap->getMin()->getChildren()->getChildren(), -1);
    std::cout << heap->getMin()->getValue();
	return 0;
}
