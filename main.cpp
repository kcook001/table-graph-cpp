//main.cpp
//CS 163 Assignment 5
//Keith Cook 6/11/2014
//The purpose of this file is to utilize a graph ADT to

#include <iostream>
using namespace std;
#include "table.h"

//Client program functions
void displayintro();
void choices();
bool again(char);

int main()
{
     //Variables
     adjlist portlandroads(20);
     
     char choice;
     int numberofvertices = 0;
     int numberofedges = 0;
     
     const int size = 25;
     char * tempvname = new char[size];
     
     node * adjtodisplay = NULL;
     
     //Display the introduction for the program.
     displayintro();
     
     //Load data into the list from external files.
     cout << "Loading data from external files..." << endl;
     numberofvertices = portlandroads.loadvertices("vertices.txt");
     if(numberofvertices <= 0)
     {
          cout << "ERROR: No location data could be loaded." << endl;
     } else {
          cout << numberofvertices << " locations loaded." << endl;
          numberofedges = portlandroads.loadedges("edges.txt");
     }
     
     if(numberofedges <= 0)
     {
          cout << "ERROR: No roadway data could be loaded." << endl << endl;
     } else {
          cout << numberofedges << " roadways loaded." << endl << endl;
     }
     
     //Main program loop.
     do {
          //Display the available choices and prompt for input.
          choices();
          //Validate user input.
          do {
               cin >> choice;
               cin.ignore(100, '\n');
               if(choice != '1' && choice != '2' && choice != '3' && choice != '4')
               {
                    cout << "Please enter a valid option." << endl;
               }
          } while(choice != '1' && choice != '2' && choice != '3' && choice != '4');
          
          //Display all adjacent vertices and edge names from the provided vertex.
          if(choice == '1')
          {
               //
               cout << "Please enter your starting point." << endl;
               cin.get(tempvname, size, '\n');
               cin.ignore(100, '\n');
               
               
               cout << "Here are the routes leading out from " << tempvname << ":" << endl;
               
               if(!portlandroads.displayalladjacent(tempvname))
               {
                    cout << "There are no routes to display." << endl << endl;
               }
          }
          
          //Find and display a route to Portland from the provided vertex.
          if(choice == '2')
          {
               //
               cout << "Please enter your starting point." << endl;
               cin.get(tempvname, size, '\n');
               cin.ignore(100, '\n');
               
               cout << "Here's how to get to Portland from " << tempvname << ":" << endl;
               if(!portlandroads.displayroute(tempvname))
               {
                    cout << "I can't tell you how to get to Portland from there." << endl;
               }
               cout << endl;
          }
          
          //Display all data in the table.
          if(choice == '3')
          {
               portlandroads.displayall();
          }
          
     } while(again(choice));  //Loop again at user's discretion.
     
     //Clean-up
     delete [] tempvname;
     
     return 1;
}

//Displays the introduction to the program.
void displayintro()
{
     cout << "Welcome!  This program allows you to find and view transit routes" << endl;
     cout << "to Portland, Oregon from a variety of nearby locales." << endl << endl;
     return;
}

//Displays the choices availble to the user.
void choices()
{
     cout << "*******************************************" << endl;
     cout << "* Here are your options:                  *" << endl;
     cout << "* 1. Display all available nearby routes. *" << endl;
     cout << "* 2. Find a route to Portland.            *" << endl;
     cout << "* 3. Display ALL route options.           *" << endl;
     cout << "* 4. Exit the program.                    *" << endl;
     cout << "********************************************" << endl;
     cout << "Please enter the number of your choice." << endl;
     return;
}

//Allows for the repetition of the main program loop.
bool again(char choice)
{
     //Immediate exit if the user so desired.
     if(choice == '4') return false;
     
     char again;
          
     cout << "Would you like to continue? (y/n)";
     cin >> again;
     cin.ignore(100, '\n');
     if(again == 'Y' || again == 'y')
     {
          return true;
     } else if (again == 'N' || again == 'n')
     {
          return false;
     }
     cout << "I'll take that as a 'no'." << endl;
     return false;
}
