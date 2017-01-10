//table.h
//CS 163 Assignment 5
//Keith Cook 6/11/2014
//Specification file for an adjacency list for a graph.

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;

struct vertex {
     bool visited;
     char * intersection;  //Name of major intersection.
     struct node * head;   //Edge list.
};

struct node {
     vertex * adj;   //Pointer to adjacent vertex.
     char * roadway; //Name of connecting roadway.
     node * next;    //Pointer to next adjacency.
};

class adjlist {
     public:
          adjlist(int);     //Contructor
          ~adjlist();       //Destructor
          int loadvertices(char * filename);         //Load vertex data from a specified external file.
          int loadedges(char * filename);            //Load edge data from an external file.
          bool insertvertex(char * vname);           //Insert a vertx into the list.
          int findvertex(char * vname);              //Check if a particular vertex in is the list.
          bool insertedge(char * fromname, char * toname, char *ename); //Insert an edge into the list.
          bool displayalladjacent(char * center);  //Display all adjacent vertices to the specified vertex.
          bool displayroute(char * start);         //Displays a full route to Portland from a starting vertex.  Depth-first.
          void displayall();
          
     private:
          vertex * adjacencylist;  //The adjacency list pointer.
          int size;               //Size of list.
          void copyadj(node * source, node *& dest); //Copies a list of adjacencies to a LLL.
          void removeall(node *& head); //Remove all nodes from a LLL.  Used by the destructor.
          void LLLdisplayall(node * head); //Display all node data in a LLL.  Used by displayalladjacent.
          void adjlist::buildroute(vertex current, node *& head);
};
