
// Avery Rapson & Aaron Brown
// April 29, 2016
// main.cpp

/* ------------- */

/*     Lab 4     */

/* ------------- */

//  * Visualization of maze algorithm

//  Created by Denise Byrnes on 3/13/16.
//  Copyright © 2016 Denise Byrnes. All rights reserved.


#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "Maze.h"
#include <iostream> //For Debugging

using namespace std;

Maze *maze = new Maze(); //Maze object

int mazeWindow;          //Display window


//Initializes background color
void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
}


//Reshape callback: Allows the window to be resized, but maze
//will still work only on original size
void reshape(int w, int h) {
    
    glViewport(0, 0, maze->W_WIDTH, maze->W_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, maze->W_WIDTH,0.0, maze->W_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

//Display Maze Callback
void displayMaze()
{
   //nothing to do here
}


//Maze Menu Callback: Simple menu attached to right button
//Supports reset maze with all walls, construct maze with
//walls removed, find path through maze, and quit option

void maze_menu(int id)
{
    //Reset the array and randomly populate
    if(id == 1) {
        maze->~Maze();
        maze = new Maze();;
        maze->drawInitWalls();
        glutPostRedisplay();
    }
    else if(id ==2) {
        maze->drawMaze();
        glutPostRedisplay();
    }
    else if (id ==3){
        maze->drawPath();
        glutPostRedisplay();
    }
    //Exit the program
    else if(id == 4) exit(0);
}


//Creates window and menu, enters event loop
int main(int argc, char **argv) {
    {
        glutInit(&argc, argv);
        
        //Window initialization for maze
        glutInitWindowSize(maze->W_WIDTH, maze->W_HEIGHT);
        glutInitWindowPosition(maze->OFFSET, maze->OFFSET);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
        mazeWindow = glutCreateWindow("Maze Visualization");
        init();
        
        //Menu initialization for maze
        glutCreateMenu(maze_menu);
        glutAddMenuEntry("Reset Maze",1);
        glutAddMenuEntry("Create Maze",2);
        glutAddMenuEntry("Draw Path",3);
        glutAddMenuEntry("Quit",4);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        
        glutReshapeFunc(reshape);
        glutDisplayFunc(displayMaze);
        
        glutMainLoop();
        
        return 0;
    }
    
}






