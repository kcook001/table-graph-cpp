//table.cpp
//Keith Cook 6/11/2014
//Implementation file for an adjacency list for a graph.

#include "table.h"

//Contructor
adjlist::adjlist(int s)
{
     //
     size = s;
     adjacencylist = new vertex[size];
     
     for(int i = 0; i < size; ++i)
     {
          adjacencylist[i].intersection = NULL;
          adjacencylist[i].head = NULL;
          adjacencylist[i].visited = false;
     }
     return;
}

//Destructor
adjlist::~adjlist()
{
     //
     for(int i = 0; i < size; ++i)
     {
          if(adjacencylist[i].head)
          {
               removeall(adjacencylist[i].head);
          }
          delete [] adjacencylist[i].intersection;
     }
     delete [] adjacencylist;
     return;
}

//Remove all nodes from a LLL.  Used by the destructor.
void adjlist::removeall(node *& head)
{
     if(!head) return;
     
     removeall(head->next);
     
     head->adj = NULL;
     
     if(head->roadway) delete [] head->roadway;
     head->roadway = NULL;
     
     delete head;
     head = NULL;
     
     return;
}

//Load vertex data from a specified external file.
int adjlist::loadvertices(char * filename)
{
     //Attempt to open external file.
     ifstream file_in;
     file_in.open(filename);
     if(!file_in)
     {
         return 0;   //Abort if file not found.
     }
     
     //Variables
     int size = 25;
     char v1name[size];
     
     int success = 0;
     
     //Import first vertex (prime the pump)
     file_in.get(v1name, size, '\n');
     file_in.ignore(100, '\n');
     
     //While there is still data to import...
     while(file_in)
     {  
          //Add the last vertex to the list.
          if(insertvertex(v1name))
          {
               ++success;
          }
          
          //Attempt to import next vertex.
          file_in.get(v1name, size, '\n');
          file_in.ignore(100, '\n');
     }
     
     //Close file
     file_in.close();
     file_in.clear();
     
     return success;
}

//Load edge data from an external file.
int adjlist::loadedges(char * filename)
{
     //Attempt to open external file.
     ifstream file_in;
     file_in.open(filename);
     if(!file_in)
     {
         return 0;   //Abort if file not found.
     }
     
     //Variables
     int size = 25;
     char v1name[size];
     char ename[size];
     char v2name[size];
     
     int success = 0;
     
     //Import first of edge data (prime the pump)
     file_in.get(v1name, size, ';');
     file_in.ignore(100, ';');
     
     //While there is still data to import...
     while(file_in)
     {
          //Import edge data.
          file_in.get(ename, size, ';');
          file_in.ignore(100, ';');

          file_in.get(v2name, size, '\n');
          file_in.ignore(100, '\n');
  
          //Add the edge to the list.
          if(insertedge(v1name, v2name, ename))
          {
               ++success;
          }
          
          //Attempt to import next edge data.
          file_in.get(v1name, size, ';');
          file_in.ignore(100, ';');

     }
     
     //Close file
     file_in.close();
     file_in.clear();
     
     return success;
}

//Insert a vertx into the list.
bool adjlist::insertvertex(char * vname)
{
     //Check if the value is aleady in the list, return if it is.
     if(findvertex(vname) > -1)
     {
          return false;
     }
     for(int i = 0; i < size; ++i)
     {
          if(adjacencylist[i].intersection == NULL)
          {
               adjacencylist[i].intersection = new char[strlen(vname) + 1];
               strcpy(adjacencylist[i].intersection, vname);
               return true;
          }
     }
     
     return false;
}

//Check if a particular vertex in is the list.  Returns the index if it is.
int adjlist::findvertex(char * vname)
{
     //Return -1 if the value is not in the table.
     int index = -1;
     
     for(int i = 0; i < size; ++i)
     {
          if(adjacencylist[i].intersection)
          {
               if(strcmp(vname, adjacencylist[i].intersection) == 0)
               {
                    index = i;
               }
          }
     }
     
     return index;
}

//Insert an edge into the list.
bool adjlist::insertedge(char * fromname, char * toname, char * ename)
{
     
     int fromindex = findvertex(fromname);
     int toindex = findvertex(toname);
     
     //Make sure both vertices are in the list already.
     if(fromindex < 0 || toindex < 0)
     {
          return false;
     }
     
     node * temp = new node;
     
     temp->adj = &adjacencylist[toindex];
     
     temp->roadway = new char[strlen(ename) + 1];
     strcpy(temp->roadway, ename);
     
     temp->next = adjacencylist[fromindex].head;
     
     adjacencylist[fromindex].head = temp;
     
     return true;     
}

//Display all adjacent vertices to the specified vertex.
bool adjlist::displayalladjacent(char * center)
{
     
     node * adjhead = NULL;
     int centerindex = findvertex(center);
     
     if(centerindex < 0)
     {
          return false;
     }
     
     node * source = adjacencylist[centerindex].head;
     
     copyadj(source, adjhead);
     
     if(!adjhead) return false;
     
     LLLdisplayall(adjhead);
     
     return true;
}

//Copies a list of adjacencies to a LLL (for displayin').
void adjlist::copyadj(node * source, node *& dest)
{
     
     if(!source) return;
     
     dest = new node;
     
     dest->adj = source->adj;
     
     dest->roadway = new char[strlen(source->roadway) + 1];
     strcpy(dest->roadway, source->roadway);
     
     dest->next = NULL;
     
     copyadj(source->next, dest->next);
     return;
}

//Displays all nodes in a LLL.  Needed in other display functions.
void adjlist::LLLdisplayall(node * head)
{
     while(head)
     {
          cout << head->roadway << " to " << head->adj->intersection << "." << endl;
          head = head->next;
     }
     return;
}

//Displays a full route to Portland from a starting vertex.  Depth-first traversal.
bool adjlist::displayroute(char * start)
{
     //
     node * routehead = NULL;
     int startindex = findvertex(start);
     
     if(startindex < 0)
     {
          return false;
     }
     
     buildroute(adjacencylist[startindex], routehead);
     
     for(int i = 0; i < size; ++i)
     {
          adjacencylist[i].visited = false;
     }
     
     if(!routehead) return false;
     
     LLLdisplayall(routehead);
     
     return true;
}

//Builds the route from a starting vertex to Portland.  Used by displayroute, modifies the supplied node pointer.
void adjlist::buildroute(vertex currentvertex, node *& head)
{
     node * current = currentvertex.head;
     //Stopping conditions: run out of routes (shouldn't happen), or reach Portland.
     if(!current) return;
     if(strcmp(current->adj->intersection, "Portland") == 0)
     {
          node * temp = new node;
          temp->adj = current->adj;
          temp->roadway = new char[strlen(current->roadway) + 1];
          strcpy(temp->roadway, current->roadway);
          temp->next = head;
          head = temp;
          return;
     }
     
     //Set visited flag to true, and move along.
     currentvertex.visited = true;
     while(current && current->adj->visited == true)
     {
          current = current->next;
     }
     //Roundabout workaround.  I REALLY hate this, but I can't figure out how to do it better.
     buildroute(adjacencylist[findvertex(current->adj->intersection)], head);
     
     //Otherwise, add route to the list.
     node * temp = new node;
     temp->adj = current->adj;
     temp->roadway = new char[strlen(current->roadway) + 1];
     strcpy(temp->roadway, current->roadway);
     temp->next = head;
     head = temp;
     
     
     return;
}

//Displays all items in the adjacency list.  Initially added for debugging, decided to make it a feature.
void adjlist::displayall()
{
     node * current = NULL;
     
     for(int i = 0; i < size; ++i)
     {
          if(adjacencylist[i].intersection)
          {
               cout << "From " << adjacencylist[i].intersection << ":"<< endl;
               if(adjacencylist[i].head)
               {
                    current = adjacencylist[i].head;
                    while(current)
                    {
                         cout << "You can take " << current->roadway << " to " << current->adj->intersection << "." << endl;
                         current = current->next;
                    }
               } else {
                    cout << "There are no adjacent routes." << endl;
               }
               cout << endl;
          }
     }
     return; 
}
