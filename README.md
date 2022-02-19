# Dijkstra-w-Fibonacci-Heap
This project explores the use of a Fibonacci Heap as a priority queue for Dijkstra's algorithm.

## Executing the Program
After cloning, simply run 'make' to compile all necessary source files and create an executable called main. Then, run ‘./main N’, where N is the desired size of the graph to analyze. Optionally, a 1 can be supplied as a second argument to enable debugging, which will print the graph, decrease key operations, and the resulting shortest distances to each node in the grap.

## Problem Description
Dijkstra’s algorithm is a well-known algorithm for finding the shortest paths from one node to all other nodes in the (connected) graph. The algorithm itself is fairly efficient; however, this is dependent on the use of a priority queue to track the current minimum (closest) of the nodes left to consider in the graph. Using a priority queue, the time complexity of this algorithm is in the order of N log M, but this becomes quadratic time without it.

A popular choice for the priority queue in this problem is a binary heap, because it is simple to implement and provides efficient operations for inserting, deleting the minimum, and decreasing a key. An alternative to this algorithm is a fibonacci heap, which can provide better amortized time complexities for the insert and decrease key operations. It accomplishes this through lazy operations that offset restructuring of the heap for later. One disadvantage of the fibonacci heap is that it is much more complicated to implement than the former.

## Mathematical Analysis
Since the Fibonacci heap’s head pointer contains the minimum value in the heap, the find minimum function is trivial. To find the minimum one only has to access the value inside the head node of the heap, so the operation is O(1) time.
  
The Fibonacci heap only inserts to the root list. Besides this, new nodes are always added directly next to the head of the root list (or as the head of the list if it is empty). Since the Fibonacci heap takes a lazy approach to insertions, the time complexity of inserting if O(1).

When merging two Fibonacci heaps, all one must do is concatenate the root lists of each heap and make the head/min pointer equal to the head/min pointer of the heap that has the lower min. This operation takes O(1) time.
  
The decrease key operation decreases the value in a node, marks the node’s parent, and adds it to the root list of the heap. If a node’s parent is already marked, then the parent of the node is also added to the root list. This process continues until a parent that is not marked is found or the root list is reached. The worst case for this is when all n nodes of a heap are children of the node before them, all nodes are marked, and the leaf node is being decreased. In this situation, One must go through all n nodes and add each to the root list, therefore the actual time complexity of this function is O(n). However, the worst case is very rare. In most cases the function will only have to move one or two nodes to the root list before they find an unmarked parent to mark, so the amortized time complexity of this function is O(1) amortized.
  
When deleting the minimum node from the heap the algorithm needs to entirely rearrange the heap in a fashion that all the nodes are placed in an ascending order of their degree with no nodes having the same degree in the heap. This pattern will also be followed in arranging the children of each node at the time of adding or deleting them. This algorithm is O(log V) time complexity.  

Using a Fibonacci heap as the priority queue for Dijkstra’s algorithm improves the time complexity from O(E log V) with a binary heap, to an asymptotic complexity of O(V log V + E). This is because Fibonacci heaps implement the insert and decrease key operations in (amortized) O(1) time.

## Profiling
### Method
In order to analyze the fibonacci heap in practice, we needed a way to generate a large number of suitable graphs for dijkstra’s algorithm. Following the algorithm outlined by Alex Vickers in his study of priority queues, we implemented a method to generate the worst-case graphs for dijkstra’s algorithm. In the worst case, the number of decrease-key operations is maximized. This situation arises when there exists a shorter path to every unvisited node in the graph at each subsequent step of the algorithm. The algorithm assumes that the source node is always 1, following the steps below:

![worst-case graph generation algorithm]()
  
The algorithm begins by connecting all the nodes linearly starting from node 1 with an edge of weight 1, which will later be recognized as the shortest path to each node. It then connects each node to all other nodes that are separated by at least one node and are greater in value. These connections are weighted in such a way that when visiting any node X in a graph of N nodes, there exists N-X shorter paths (decrease-key operations) to all following nodes. This is seen in the example below:

![worst-case graph example with 5 nodes]()

## Results

![Runtime of Dijkstra’s Algorithm with Increasing Graph Sizes]()

![Theoretical Runtime of Dijkstra’s Algorithm with Fibonacci Heap and Worst-Case Graph]()

In our project, we tested input sizes ranging from 5 to 40,960 nodes on two separate machines. When gathering the runtime for some n number of nodes, we ran the program five times and took the average between them as our final value. 

For both computers used, data trended in an quadratic fashion (O(n^2)). Dijkstra’s algorithm is O(nlog(n)+e), where e is the number of edges in the graph used. Since e is equivalent to n(n-1)/2 in the worst case, the equation for big-O is also (nlog(n)+n(n-1))/2. In this equation, the leading term is n(n-1)/2, therefore, the big-O of Dijkstra’s algorithm using a Fibonacci heap for the worst-case graph can also be viewed as O(n^2). With this in mind, the results we gathered are representative of the theoretical values, despite small variation due to implementation and external factors such as machine-dependent computing capabilities and memory limitations.

## Conclusion
In conclusion, Fibonacci heaps are theoretically an optimal data structure to use as a priority queue; however, they are difficult to implement and are less efficient in practice. Due to time constraints, we were not able to compare these results with other types of priority queues, such as binary heaps. However, based on the theoretical time complexities, Fibonacci heaps perform better compared to binary heaps when there are a large number of edges relative to the number of nodes, since binary heaps have a time complexity of O(E log V).

Interestingly, space was the limiting factor for our experiments, not time. Surpassing a graph size of 40,000 nodes used a significant amount of RAM. Space complexity is also another downside to Fibonacci heaps, since each node requires four pointers and several other values to implement correctly.

## References
Ryder, Alexa. “Dijkstra's Algorithm: Application, Complexity, Implementation, Explanation.” OpenGenus IQ: Computing Expertise & Legacy, OpenGenus IQ: Computing Expertise & Legacy, 1 Apr. 2018, https://iq.opengenus.org/dijkstras-algorithm-finding-shortest-path-between-all-nodes/.

Vickers, Alex. “A Comparison of Worst Case Performance of Priority Queues Used in Dijkstra's Shortest Path Algorithm.” 1986.

“Fibonacci Heap - Deletion, Extract Min and Decrease Key.” GeeksforGeeks, 24 Nov. 2021, https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/
