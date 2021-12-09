/******************************************************************************
    * Authors:
        - Drew Dunkelberger: ddunkelberge2018@my.fit.edu
        - John Dewey:        jdewey2018@my.fit.edu
        - Divyansh Gupta:    dgupta2019@my.fit.edu
    * Date: 12/10/21
    * Decription:
        - Fibonacci heap implementation to investigate the time complexity as a
        priority queue for Dijkstra's shortest path algorithm using a general
        worst case graph.
    * References:
        - https://ir.canterbury.ac.nz/bitstream/handle/10092/13567/vickers_report_1986.pdf?sequence=1&isAllowed=y
            Explains an algorithm for Dijkstra's worst case graph generation as
            implemented by Graph::generateWorstCaseGraph(int n)
******************************************************************************/

#include "fibheap.h"
#include "graph.h"
#include <iostream>
#include <chrono>
#include <stdio.h> // Needed for command line args

/* Command line args
    - 1) Graph size: int specifying size of graph to generate
    - 2) Debug flag (optional): int specifying whether to print graph and minimum
        spanning tree. 1 for yes, else no
*/

int main(int argc, char* argv[]) {
    bool debugFlag = false;

    // Generate worst cast graph of size N
    if (argc < 2) {
        cout << "Please provide size of graph as command line argument" << endl;
    }
    else {
        if (argc == 3 && atoi(argv[2]) == 1) {
            debugFlag = true;
        }

        // Generate worst cast graph of size N
        cout << "Creating graph of size " << argv[1] << "..." << endl;
        Graph G = Graph::generateWorstCaseGraph(atoi(argv[1]));

        // Print graph for verification
        if (debugFlag) {
            cout << "\nGenerated Graph:" << endl;
            G.printGraph();
        }

        cout << "---------------- Testing Dijkstra's ----------------" << endl;

        typedef std::chrono::high_resolution_clock Clock;
        Clock::time_point begin_t = std::chrono::time_point_cast<std::chrono::nanoseconds>(Clock::now());
        dijkstra(&G, debugFlag);
        Clock::time_point end_t = std::chrono::time_point_cast<std::chrono::nanoseconds>(Clock::now());

        // Print Spanning tree for verification
        if (debugFlag) {
            cout << "\nMinimum Spanning Tree (MST):" << endl;
            G.printSpanningTree();
        }
        // Calculate time spent in seconds. (CLOCKS_PER_SEC = 1000000)
        cout << "\nruntime: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - begin_t).count() << endl;
    }

	return 0;
}
