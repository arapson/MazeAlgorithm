
// Avery Rapson & Aaron Brown
// April 29, 2016
// DrawGraph.cpp

/* ------------- */

/*     Lab 4     */

/* ------------- */

//  Created by Denise Byrnes on 3/13/16.
//  Copyright © 2016 Denise Byrnes. All rights reserved.


#include "DrawGraph.h"
#include <iostream>

//Debug: dump graph for inspection
void DrawGraph::printGraph(){
    for(int j = 0; j < adjList.size(); j++){
        vector<int> temp = adjList[j];
        cout<< j << ": ";
        for(int i = 0; i < temp.size(); i++) {
            int val = temp[i];
            cout<< val << " ";
        }
        cout<<endl;
    }
}

//Construct an empty inital adjacency matrix
DrawGraph::DrawGraph(int n)
{
    adjList.resize(n*n);
}

//Return a copy of the adjacency matrix
vector<vector<int> > DrawGraph:: get()
{
    return adjList;
}

//Add a graph edge (remove wall on a cell)
void DrawGraph::addEdge(int v1, int v2)
{
    adjList[v1].push_back(v2);
}

//Perform depth-first search of graph
stack<int> DrawGraph ::depthFirstSearch(int start, int end)
{
    stack<int> S; // Inserts a new element at the top of the stack, above its current top element
    
    int trace = start;
    S.push(start);
    
    while (trace != end) {
                trace = adjList[trace].back(); // Returns a reference to the last element in the vector
                S.push(trace);
    }
    
    
    return S;
}