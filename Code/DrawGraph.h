
// Avery Rapson & Aaron Brown
// April 29, 2016
// DrawGraph.h

/* ------------- */

/*     Lab 4     */

/* ------------- */


//  Class for creating adjacency matrix for maze

//  Created by Denise Byrnes on 3/13/16.
//  Copyright © 2016 Denise Byrnes. All rights reserved.


#ifndef DrawGraph_h
#define DrawGraph_h

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class DrawGraph{
    public:
        //Creates an empty initial adjacency list, sets vertices to n*n
        DrawGraph(int n);
        //when a maze wall is removed, adds edge to adjacency list
        void addEdge(int v1, int v2);
        //Debug: dump graph for inspection
        void printGraph();
        //returns a copy of the adjacency list
        vector<vector<int> > get();
        //Perform the depth-first search of the graph
        stack<int> depthFirstSearch(int start, int end);
    
    private:
        vector<vector<int> > adjList;
        int vertices;
};

#endif /* DrawGraph_h */
