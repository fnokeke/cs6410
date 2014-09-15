//Fabian Okeke
//Sept 1st, 2014
//CS 6410: Adv Sys
//Code adapted from Runnable.com
//Link: http://runnable.com/UwQvQY99xW5AAAAQ/john-conway-s-game-of-life-for-c%2B%2B-nested-for-loops-and-2-dimensional-arrays

//DESCRIPTION
//A very simple C++ implementation of John Conway's Game of Life.
//This implementation uses several nested for loops as well as two-dimensional
//arrays to create a grid for the cells in the simulation to interact.
//The array that is displayed to the user is ROW-2 x COL-2 (e.g 50 x 100), but actual size
//of the array is ROW x COL(52 x 102).  The reason for this is to make the
//calculations easier for the cells on the outermost "frame" of the grid.

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
//#include <thread>
#include <time.h>
#include "vec2d.h"

using namespace std;

//array dimensions
#define ROW 10
#define COL 10
#define ARRAY_LIMIT 10000


//Copies one vec2d array to another.
//copy(source, destination)
void copy(vec2d& src, vec2d& dest)
{	
    for(int j = 0; j < ROW; j++)
    {
        for(int i = 0; i < COL; i++)
            dest[j][i] = src[j][i];
    }
}


//The life function is the most important function in the program.
//It counts the number of cells surrounding the center cell, and
//determines whether it lives, dies, or stays the same.
void life(vec2d& array, char choice)
{
    //Copies the main array to a temp array so changes can be entered into a grid
    //without affecting the other cells and the calculations being performed on them.
	//vec2d temp(ROW, std::vector<int>(COL));
    vec2d temp(ROW, COL);
    copy(array, temp);
    for(int j = 1; j < ROW-1; j++)
    {
        for(int i = 1; i < COL-1; i++)
        {
            if(choice == 'm')
            {
                //The Moore neighborhood checks all 8 cells surrounding the current cell in the array.
                int count = 0;
                count = array[j-1][i] +
                        array[j-1][i-1] +
                        array[j][i-1] +
                        array[j+1][i-1] +
                        array[j+1][i] +
                        array[j+1][i+1] +
                        array[j][i+1] +
                        array[j-1][i+1];
                //The cell dies.
                if(count < 2 || count > 3)
                    temp[j][i] = 0;
                //The cell stays the same.
                if(count == 2)
                    temp[j][i] = array[j][i];
                //The cell either stays alive, or is "born".
                if(count == 3)
                    temp[j][i] = 1;
            }

            else if(choice == 'v')
            {
                //The Von Neumann neighborhood checks only the 4 surrounding cells in the array,
                //(N, S, E, and W).
                int count = 0;
                count = array[j-1][i] +
                        array[j][i-1] +
                        array[j+1][i] +
                        array[j][i+1];
                //The cell dies.
                if(count < 2 || count > 3)
                    temp[j][i] = 0;
                //The cell stays the same.
                if(count == 2)
                    temp[j][i] = array[j][i];
                //The cell either stays alive, or is "born".
                if(count == 3)
                    temp[j][i] = 1;
            }
        }
    }
    //Copies the completed temp array back to the main array.
    copy(temp, array);
}

//Checks to see if two arrays are exactly the same.
//This is used to end the simulation early, if it
//becomes stable before the 100th generation. This
//occurs fairly often in the Von Neumann neighborhood,
//but almost never in the Moore neighborhood.
bool compare(vec2d& array1, vec2d& array2)
{
    int count = 0;
    for(int j = 0; j < ROW; j++)
    {
        for(int i = 0; i < COL; i++)
        {
            if(array1[j][i]==array2[j][i])
                count++;
        }
    }
    //Since the count gets incremented every time the cells are exactly the same,
    //an easy way to check if the two arrays are equal is to compare the count to
    //the dimensions of the array multiplied together.
    if(count == ROW*COL)
        return true;
    else
        return false;
}

//print vec2d array
void print(vec2d& array)
{
    for(int j = 0; j < array.get_row_len(); j++)
    {
        for(int i = 0; i < array.get_col_len(); i++)
        {
            if(array[j][i] == 1)
                cout << '*';
            else
                cout << '-';
        }
        cout << endl;
    }
}

int main()
{	
    //vec2d gen0(ROW,COL);
    vec2d todo(ROW,COL);
    vec2d backup(ROW,COL);
    int limit;
    char neighborhood;
    char again;
    char cont;
    bool comparison;
    string decoration;
    string sequence;
    //spawn threads
    //thread first(print);
    //thread second(life);
    //thread third(copy);
    //first.join(); 
    //pauses until first finishes

	/*cout << todo.get_row_len() << "x"<<todo.get_col_len() << endl << "TESTER!!!\n\n" ;
	int count = 1;
	for(int j = 0; j < todo.get_row_len(); j++)
    {
        for(int i = 0; i < todo.get_col_len(); i++)
        {
			todo.set_index(j,i);
			todo[j][i] = count;
			count++;
		}
	}
	
	todo.resize();
	
	cout << todo.get_row_len() << "x"<<todo.get_col_len() << endl << "TESTER22!!!\n\n" ;
	for(int j = 0; j < todo.get_row_len(); j++)
    {
        for(int i = 0; i < todo.get_col_len(); i++)
        {
			todo.set_index(j,i);
			cout << todo[j][i] << endl;
		}
	}
	
	exit(0);
    */
    //Instructions on how the program is used, along with the rules of the game.
    cout << endl << "This program is a C++ implementation of John Conway's Game of Life."
         << endl << "With it, you can simulate how \"cells\" interact with each other." << endl
         << endl << "There are two types of neighborhoods you can choose, the"
         << endl << "Moore, and the Von Neumann.  The Moore neighborhood checks"
         << endl << "all 8 surrounding cells, whereas the Von Neumann checks"
         << endl << "only the 4 cardinal directions: (N, S, E, and W)." << endl
         << endl << "The rules of the \"Game of Life\" are as follows:" << endl
         << endl << "1. Any live cell with fewer than two live neighbors dies, as if caused by under-population."
         << endl << "2. Any live cell with two or three live neighbors lives on to the next generation."
         << endl << "3. Any live cell with more than three live neighbors dies, as if by overcrowding."
         << endl << "4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction." << endl
         << endl << "The initial configuration (Generation 0) of the board is determined randomly."
         << endl << "Every hundred Generations you will get the option to end or continue the simulation."
         << endl << "If a system becomes \"stable\" (meaning the system does not change from one"
         << endl << "generation to the next), the simulation will end automatically." << endl << endl;
    //Loop to check if user wants to keep simulating.
    do
    {
        //Loop to check for proper inputs.
        do
        {
            cout << "Which neighborhood would you like to use (m or v): ";
            cin >> neighborhood;
            cout << "Which sequence random(r) or gliders(g): ";
            cin >> sequence;
            cout << "What is your simulation limit(10, 20, 50, 100, 1000): ";
            cin >> limit;
        }
        while(neighborhood != 'm' && neighborhood != 'v');
        //Clears the screen so the program can start fresh.
        system("clear");
        int i = 0;
        //Loop that does the bulk of the simulation.
        do
        {	
			//set initial board configuration
			if (i==0)
				set_sequence(todo, sequence);
            //Determines how big the decoration should be.
            if(i < 10)
                decoration = "#############";
            else if(i >= 10 && i < 100)
                decoration = "##############";
            else if(i >= 100 && i < 1000)
                decoration = "###############";
            else if(i >= 1000 && i < 10000)
                decoration = "################";
            else
                decoration = "#################";
            //Prints the generation.  If i == 0, the gen0 array is copied to the
            //todo array, and is printed before any functions act upon it.
            cout << decoration << endl << "Generation " << i
                 << ":" << endl << decoration << endl;
            //Initializes the arrays by copying the gen0 array to the todo array.
           // if(i == 0) {
             //   copy(gen0, todo);
			//}
            copy(todo, backup);
            print(todo);
            life(todo, neighborhood);
            i++;
            //Pauses the system for 1/10 of a second in order to give the screen
            //time to refresh.
            system("sleep .1");
            //Checks whether the generation is a multiple of limit to ask
            //the user if they want to continue the simulation. If they
            //wish to end, the program breaks out of the loop to ask if
            //the user wishes to run another simulation.
            if(i % limit == 1 && i != 1)
            {
                cout << endl;
                //Loop to check for proper inputs.
                do
                {
                    cout << "Would you like to continue this simulation? (y/n): ";
                    cin >> cont;
                }
                while(cont != 'y' && cont != 'n');
                if(cont == 'n')
                    break;
            }
            //Compares the current generation with a backup generation.
            //If they aren't the same (they usually aren't) the system
            //clears the screen and repeats the process until they are
            //the same or the user chooses to quit.
            comparison = compare(todo, backup);
           // if(comparison == false) 
               // system("clear");
             //  cout << endl << endl;
			
            //expand all arrays when previous and current states are same
            if(corner_flag_set(todo)) {
			/*	cout << "Corner_flag_set(b4):" << todo.get_size() << endl;
				cout << "Current todo:" << endl;
				print(todo);
				cout << endl;
				todo.resize();
				backup.resize();
				set_sequence(todo, sequence);
				cout << "Corner_flag_set(after):" << todo.get_size() << endl;
				cout << "After resize todo:" << endl;
				print(todo);
				*/
             }
             if (comparison == true) {
				cout << "Comparison(b4):" << todo.get_size() << endl;
				todo.resize();
				backup.resize();
				set_sequence(todo, sequence);
				cout << "Comparison expanded todo.size:" << todo.get_size() << endl;	
				comparison=false;			 
			 }
			 
       
        }
		while(todo.get_size() <= ARRAY_LIMIT);
		//while(comparison == false);
		
        //Loop to check for proper inputs.
        do
        {
            cout << "Would you like to run another simulation? (y/n): ";
            cin >> again;
        }
        while(again != 'y' && again != 'n');
    }
    while(again == 'y');
    return 0;
}

