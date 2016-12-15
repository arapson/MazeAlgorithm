// Avery Rapson & Aaron Brown
// April 29, 2016
// Maze.cpp

/* ------------- */

/*     Lab 4     */

/* ------------- */

/*
 --------------------------------------------------------------------------------
 
 Objective of Program:
 
 + Design and implement a GUI based C++ application to randomly construct an n X n maze 
   with a path from a start cell to an end cell.
 + Implementation of  an adjacency list, "equivalence classes", the "union-find" algorithm, 
   depth-first search of an undirected graph, and some understanding of the GUI programming.
 
 --------------------------------------------------------------------------------
 
 Requirements:
 
 + Decide on a data structure that will hold the Maze ADT.
 + Remove walls from the maze.
 + Decide on a data structure for a bidirectional undirected Graph ADT (used adjacency list).
   Construct the graph using the information stored in your Maze ADT
 + Write a Stack based depth-first search algorithm that traverses the Graph 
   ADT finding a path from the start to end cell. Store your path in the Stack.
 
 
 --------------------------------------------------------------------------------
 
 Controls:
 
 + right click to open an options menu.
 + Reset - Resets the Maze to an plain grid.
 + Create Maze - Deletes walls and creates the maze foundation.
 + Draw Path - draws a plath within the created maze from the start to the finish.
 + Quit - Quits the program.
 

 */


#include "Maze.h"
#include <iostream>

using namespace std;

//Constructs inital maze with all walls intact
Maze::Maze() {
    myGraph = new DrawGraph(NUM_CELLS_PER_SIDE);
    
    srand (time(NULL));
    buildEquivClasses();							//initial set of classes
    unionFind();									//condense classes - used to remove maze walls
}

//Maze destructor
Maze::~Maze(){
    
    
    whichClass.clear();
    
    for (int i = 0; i < STOP_CELL; i++) {
        equivalenceClasses[i].clear();
    }
    
    equivalenceClasses.clear();
    
}

//randomly select an east or south wall
int Maze::selectWall(int row,int col)
{
    //since walls are bidirectional we need only consider
    //east and south walls where east = 0 and south = 1.
    
    
    int wall = rand()%2; // generate random number between 1 and 2
    
    int vertex = (row * NUM_CELLS_PER_SIDE)+col; // vertex position
    
    
    //special case 1:
    if (row == NUM_CELLS_PER_SIDE-1) { // if the position in row equals number of cells per side ( at the edge )
        
        return vertex+1; // select east wall (add 1 to the vertex position)
    }
    
    //special case 2:
    if (col == NUM_CELLS_PER_SIDE-1) { // if position in col equals number of cells per side ( at the edge )
        
        return vertex + NUM_CELLS_PER_SIDE; // select south wall (add the number of cells in a row to the vertex position)
    }
    
    if (wall==0) // if wall is east
    {
        vertex=vertex+1; // add 1 to the vertex position (next position to the right - )
    }
    
    if(wall==1) // if wall is south
    {
        vertex = vertex+NUM_CELLS_PER_SIDE; // add the number of cells in a row to the vertex position.
    }
    
    return vertex;
}

//performs the union find algorithm - cells with adjacent walls are placed in the
//same equivalence class. This continues until a single class remains containing start
//and finish cells => maze has a path from start to finish.
void Maze::unionFind()
{
    
    for (int i = 0; i < STOP_CELL; i++) {
        
        int row = i / NUM_CELLS_PER_SIDE;
        
        int col = i % NUM_CELLS_PER_SIDE;
        
        int wall = selectWall(row, col);
        
        int original_state = (row * NUM_CELLS_PER_SIDE)+col;
        
        
        whichClass[wall]=original_state;
        
        equivalenceClasses[original_state][wall] = true;
        
        
        // randomize setup
        
        int parent = wall;
        while (equivalenceClasses[parent].empty()) {
            parent = whichClass[parent];
            
        }
        
        for (int i = 0; i<STOP_CELL; i++) {
            if (equivalenceClasses[parent][i]) {
                equivalenceClasses[original_state][i] = true;
            }
        }
        
        equivalenceClasses[wall].clear();

        
        myGraph -> addEdge(original_state, wall); // union
    
    }
    


    
}

//Constructs initial equivalence classes, each vertex in its own class

void Maze::buildEquivClasses()
{
    equivalenceClasses.resize(STOP_CELL);
    for(int i=0; i<equivalenceClasses.size(); i++){
        equivalenceClasses[i].resize(STOP_CELL);
    }
    
    //set up zero's
    for(int i=0; i < STOP_CELL; i++){
        for(int j=0; j < STOP_CELL; j++){
            equivalenceClasses[i][j] = 0;
        }
    }
    
    whichClass.resize(STOP_CELL);
    
    for (int i = 0; i < STOP_CELL; i++) {
        whichClass[i] = i;
    }
}

//Draws initial maze with no walls removed
void Maze::drawInitWalls()
{
    // horizontal lines
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i=0; i <= NUM_CELLS_PER_SIDE; i++){
        glVertex2d(OFFSET, i*CELL_WIDTH + OFFSET);
        glVertex2d(CELL_WIDTH*NUM_CELLS_PER_SIDE + OFFSET,i*CELL_WIDTH + OFFSET);
    }
    // vertical lines
    for (int i=0; i <= NUM_CELLS_PER_SIDE; i++){
        glVertex2d(i*CELL_WIDTH + OFFSET, OFFSET);
        glVertex2d(i*CELL_WIDTH + OFFSET,CELL_WIDTH*NUM_CELLS_PER_SIDE + OFFSET);
    
    }
    glEnd();
    
    //character start and finish
    glColor3f (0.0, 0.0, 0.0);
    glRasterPos2d(OFFSET - 10, NUM_CELLS_PER_SIDE*CELL_WIDTH-10 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'S');
    glRasterPos2d(NUM_CELLS_PER_SIDE*CELL_WIDTH + OFFSET + 5,
                  5 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'F');
    
    glutSwapBuffers();
    
}


//Draws  maze with  walls removed
void Maze::drawMaze()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    
    //draw outer walls
    glBegin(GL_LINES);
    glVertex2d(OFFSET, OFFSET);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET);
    glVertex2d(OFFSET, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET , OFFSET);
    glVertex2d(OFFSET, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET+ CELL_WIDTH * NUM_CELLS_PER_SIDE , OFFSET);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    
    //draw inner walls based on adjacency list
    vector<vector<int>> adjMatrix = myGraph->get();
    for (int i=0; i < adjMatrix.size(); i++) {
        
        vector<int> list = adjMatrix[i];
        for(int j = 0; j < list.size(); j++) {
            int vertex = list[j];
            int row = vertex / NUM_CELLS_PER_SIDE;
            int col = vertex % NUM_CELLS_PER_SIDE;
            
            if(vertex == (i + 1)) {//east wall removed, draw south wall
                if((row+1) % NUM_CELLS_PER_SIDE == 0) continue;
                
                int x = OFFSET + (col-1) * CELL_WIDTH;
                int y = W_HEIGHT - (OFFSET + (row+1) * CELL_WIDTH);
                int x2 = OFFSET + (col) * CELL_WIDTH;
                glVertex2d(x, y);
                glVertex2d(x2, y);
                
            }
            else {//south wall removed, draw east wall
                if((col+1) % NUM_CELLS_PER_SIDE == 0) continue;
                
                int x = OFFSET + (col+1) * CELL_WIDTH;
                int y = W_HEIGHT - (OFFSET + (row-1) * CELL_WIDTH);
                int y2 = W_HEIGHT - (OFFSET + (row) * CELL_WIDTH);
                glVertex2d(x, y);
                glVertex2d(x, y2);
                
            }
        }
    }
    
    glEnd();
    
    //character start and finish
    glColor3f (0.0, 0.0, 0.0);
    glRasterPos2d(OFFSET - 10, NUM_CELLS_PER_SIDE*CELL_WIDTH-10 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'S');
    glRasterPos2d(NUM_CELLS_PER_SIDE*CELL_WIDTH + OFFSET + 5,
                  5 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'F');
    
    glutSwapBuffers();

}

//Draws path thru maze from stack entries
void Maze::drawPath()
{
    //Clear drawing buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    //redraw maze
    drawMaze();
    
    //find path and place in depth first stack
    dfS = myGraph->depthFirstSearch(START_CELL, STOP_CELL);

    //blue boxes for path
    glColor3f (0.0, 0.0, 1.0);
    int row, col, cell;
    
    //since path in reverse order, easier to place stack
    // into a vector
    vector<int> temp;
    while(!dfS.empty()){
        cell = dfS.top();
        dfS.pop();
        temp.push_back(cell);
    }
    
    //for each cell in path
    for(int i = temp.size() - 1; i >= 0; i--){
        cell = temp[i];
        
        //find row/col for cell
        row = cell / NUM_CELLS_PER_SIDE;
        col = cell % NUM_CELLS_PER_SIDE;
        
        //draw a blue rectangle for cell in path
        glRectd(OFFSET + col * CELL_WIDTH + 2,
                W_HEIGHT - (OFFSET + row * CELL_WIDTH + 2),
                OFFSET + col * CELL_WIDTH + CELL_WIDTH - 2,
                W_HEIGHT - (OFFSET + row * CELL_WIDTH + CELL_WIDTH - 2));
        
    }
    
    //draw the new buffer contents
    glutSwapBuffers();
}



