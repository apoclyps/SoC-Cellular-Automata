/**
 * Cellular_Automata
 * Creates a 2 dimensional grid of type boolean
 * initilises a shape based on user input from menu
 * runs on a continious basis
 * prints to file each time a new shape is selected
 * size is adjustable.
 * @ "Kyle Harrison"
 * @ (7/11/2011)
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

bool menu();
void setupparentGeneration();
void printparentGeneration();
void printparentGeneration2();
void updateparentGeneration();
void writeToFile();
void findNextCellState(int i,int j);
void sort();

// VARIABLES
const int WIDTH = 17;
vector < vector <bool> > parentGeneration(WIDTH+2, vector<bool>(WIDTH+2));
vector < vector <bool> > childGeneration(WIDTH+2, vector<bool>(WIDTH+2));
int lives;
char shape;
ofstream myfile;

int main()
{
	bool menuExit;

	do
	{
		menuExit = menu();

		myfile.open ("ConwaysGameOfLife.txt");
		cout << " Enter number of generations" << endl;
		cout << " : ";
		cin >> lives;

		for(int d=0; d < WIDTH+2;d++)
		{
			for(int e=0; e < WIDTH+2;e++)
			{
				parentGeneration.at(d).at(e)=0;
				childGeneration.at(d).at(e)=0;
			}
		}

		setupparentGeneration();
		cout << " Initial Table" << endl;
		//printparentGeneration();
		printparentGeneration2();

		for (int c = 0; c < lives; c++)
		{
			updateparentGeneration();
			writeToFile();

			for(int i = 1; i <= WIDTH; ++i)
				{
					for(int j = 1; j <= WIDTH; ++j)
					{
						parentGeneration.at(i).at(j) = childGeneration.at(i).at(j);
					}
				}
		   // printparentGeneration();
			printparentGeneration2();
		}

		myfile.close();
	}while(menuExit!=true);

	return 0;
}

// The setupparentGeneration function creates an initial state for the cellular autonoma
void setupparentGeneration()
{
	for(int i = 0; i < WIDTH+2; ++i)
	{
		for(int j = 0; j < WIDTH+2; ++j)
		{
			if(i != (ceil(WIDTH/(double)2)))
			{
				if(j != ((WIDTH/2)))
				{
						if(parentGeneration.at(i).at(j)!=1)
						{
							parentGeneration.at(i).at(j) = 0;
						}
				}
			}

			if(i == (ceil(WIDTH/(double)2)))
			{
				//cout << ceil(WIDTH/2) << endl;
				if(j == (ceil(WIDTH/(double)2)))
				{
						// GLIDER
						if(shape=='g')
						{
							// top left
							parentGeneration.at(i-1).at(j-1) = 0;
							// top middle
							parentGeneration.at(i-1).at(j) = 1;
							// top right
							parentGeneration.at(i-1).at(j+1) = 0;

							// middle left
							parentGeneration.at(i).at(j-1) = 0;
							// center middle
							parentGeneration.at(i).at(j) = 0;
							// middle right
							parentGeneration.at(i).at(j+1) = 1;

							// bottom left
							parentGeneration.at(i+1).at(j-1) = 1;
							// bottom middle
							parentGeneration.at(i+1).at(j) = 1;
							// bottom right
							parentGeneration.at(i+1).at(j+1) = 1;
						}
						// small exploder
						else if(shape=='s')
						{
							// top left
							parentGeneration.at(i-1).at(j-1) = 0;
							// top middle
							parentGeneration.at(i-1).at(j) = 1;
							// top right
							parentGeneration.at(i-1).at(j+1) = 0;

							// middle left
							parentGeneration.at(i).at(j-1) = 1;
							// center middle
							parentGeneration.at(i).at(j) = 1;
							// middle right
							parentGeneration.at(i).at(j+1) = 1;

							// bottom left
							parentGeneration.at(i+1).at(j-1) = 1;
							// bottom middle
							parentGeneration.at(i+1).at(j) = 1;
							// bottom right
							parentGeneration.at(i+1).at(j+1) = 1;

							parentGeneration.at(i+2).at(j) = 1;
						}
						// large exploder
						else if(shape=='b')
						{
							parentGeneration.at(i-1).at(j-1) = 0;
							parentGeneration.at(i-1).at(j) = 0;
							parentGeneration.at(i-1).at(j+1) = 0;
							parentGeneration.at(i).at(j-1) = 0;
							parentGeneration.at(i).at(j) = 0;
							parentGeneration.at(i).at(j+1) = 0;
							parentGeneration.at(i+1).at(j-1) = 0;
							parentGeneration.at(i+1).at(j) = 0;
							parentGeneration.at(i+1).at(j+1) = 0;
							parentGeneration.at(i-2).at(j-2) = 1;
							parentGeneration.at(i-2).at(j) = 1;
							parentGeneration.at(i-2).at(j+2) = 1;
							parentGeneration.at(i).at(j-2) = 1;
							parentGeneration.at(i+1).at(j-2) = 1;
							parentGeneration.at(i-1).at(j-2) = 1;
							parentGeneration.at(i).at(j+2) = 1;
							parentGeneration.at(i+1).at(j+2) = 1;
							parentGeneration.at(i-1).at(j+2) = 1;
							parentGeneration.at(i+2).at(j-2) = 1;
							parentGeneration.at(i+2).at(j) = 1;
							parentGeneration.at(i+2).at(j+2) = 1;
							parentGeneration.at(i-2).at(j) = 1;
							parentGeneration.at(i+2).at(j) = 1;
						}
				}
			}

		}
	}
}

// The printparentGeneration function outputs the state of the parentGeneration to the user.  For all
// cells that are 0, it outputs a space (" "), for all cells that are 1, it
// outputs a star ("*")
void printparentGeneration()
{
	for(int i = 0; i < (WIDTH+2); ++i)
	{
		for(int j = 0; j < (WIDTH+2); ++j)
		{
			if(parentGeneration.at(i).at(j) == 0)
			{
				cout << "[ ]";
			}
			else if(parentGeneration.at(i).at(j) == 1)
			{
				if((i==0)||(i==(WIDTH+1))||(j==0)||(j==(WIDTH+1)))
				{
					cout << "[x]";
				}
				else
				{
					cout << "[+]";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printparentGeneration2()
{
	for(int i = 1; i <= (WIDTH); ++i)
	{
		for(int j = 1; j <= (WIDTH); ++j)
		{
			if(parentGeneration.at(i).at(j) == 0)
			{
				cout << "[ ]";
			}
			else if(parentGeneration.at(i).at(j) == 1)
			{
				if((i==0)||(i==(WIDTH+1))||(j==0)||(j==(WIDTH+1)))
				{
					cout << "[x]";
				}
				else
				{
					cout << "[+]";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

// The updateparentGeneration function updates the contents of the parentGeneration after calculating
// the next states using the findNextCellState function
void updateparentGeneration()
{
	for(int i = 0; i < (WIDTH+2); i++)
	{
		for(int j = 0; j < (WIDTH+2); j++)
		{
			// CORNERS
			if((i==0 && j==0) || (i==0 && j==(WIDTH+1)) || (i==(WIDTH+1) && j==0) || (i==(WIDTH+1) && j==(WIDTH+1)) )
			{
				//cout << " CIRCLES 0 " << i << j << endl;
			}
			else if( ((i>0) || (i<WIDTH)) && ((j>0) || (j<WIDTH)) )
			{
				if(i>0 && ((j==0) || (j==WIDTH+1)))
				{
					if( (i==(WIDTH+1)) || (j==(WIDTH+1)) )
					{
							if(i==(WIDTH+1))
							{
								parentGeneration.at(i).at(j)=parentGeneration.at(i-WIDTH).at(j);
							}
							else if(j==(WIDTH+1))
							{
								parentGeneration.at(i).at(j)=parentGeneration.at(i).at(j-WIDTH);
							}
					}
					else if((i==0)||(j==0))
					{
						if(i==0)
						{
								parentGeneration.at(i).at(j)=parentGeneration.at(i+1).at(j);
						}
						else if(j==0)
						{
								parentGeneration.at(i).at(j)=parentGeneration.at(i).at(j+1);
						}
					}
				}
				else if (j>0 && ((i==0) || (i==WIDTH+1)))
				{
					if( (i==(WIDTH+1)) || (j==(WIDTH+1)) )
					{
						if(i==(WIDTH+1))
						{
							parentGeneration.at(i).at(j)=parentGeneration.at(i-WIDTH).at(j);
						}
						else if(j==(WIDTH+1))
						{
							parentGeneration.at(i).at(j)=parentGeneration.at(i).at(j-WIDTH);
						}
					}
					else if((i==0)||(j==0))
					{
						if(i==0)
						{
							parentGeneration.at(i).at(j)=parentGeneration.at(i+1).at(j);
						}
						else if(j==0)
						{
							parentGeneration.at(i).at(j)=parentGeneration.at(i).at(j+1);
						}
					}
				}
			}

		}
	}
	cout << endl;

	// SENDS from 1,1 to 3,3
	for(int i = 0; i < (WIDTH+2); i++)
	{
		for(int j = 0; j < (WIDTH+2); j++)
		{
			if(((i>0)&&(i<(WIDTH+1)))&&((j>0)&&(j<(WIDTH+1))) )
			{
							findNextCellState(i,j);
			}
		}
	}

}

// The states for this are:
//
// 111 110 101 100 011 010 001 000
//  0   0   0   1   1   1   1   0

void findNextCellState(int i,int j)
{
				int alive_count = 0;

				//This code counts how many neighbours are alive
				alive_count += parentGeneration.at(i-1).at(j-1);
				alive_count += parentGeneration.at(i-1).at(j);
				alive_count += parentGeneration.at(i-1).at(j+1);
				alive_count += parentGeneration.at(i).at(j-1);
				alive_count += parentGeneration.at(i).at(j+1);
				alive_count += parentGeneration.at(i+1).at(j-1);
				alive_count += parentGeneration.at(i+1).at(j);
				alive_count += parentGeneration.at(i+1).at(j+1);

				if( (alive_count == 2 && parentGeneration.at(i).at(j)) || (alive_count == 3))
				{
					childGeneration.at(i).at(j) = 1;
				}
				else
				{
					childGeneration.at(i).at(j) = 0;
				}
}
void writeToFile()
{
	  for(int i = 0; i < (WIDTH+2); ++i)
	  	{
	  		for(int j = 0; j < (WIDTH+2); ++j)
	  		{
	  			if(parentGeneration.at(i).at(j) == 0)
	  			{
	  				myfile << "[ ]";
	  			}
	  			else if(parentGeneration.at(i).at(j) == 1)
	  			{
	  				if((i==0)||(i==(WIDTH+1))||(j==0)||(j==(WIDTH+1)))
	  				{
	  					myfile << "[x]";
	  				}
	  				else
	  				{
	  					myfile << "[+]";
	  				}
	  			}
	  		}
	  		myfile << endl;
	  	}
	  	myfile << endl;
}

bool menu()
{
			char userChoice;
			cout << "\n<---------------------------------------------->" << endl;
			cout << ""<<"		   MAIN MENU" << endl;
			cout << "<---------------------------------------------->" << endl;
			cout << "\n Press :" << endl;
			cout << "  G - Glider" << endl;
			cout << "  S - Small Exploder" << endl;
			cout << "  B - Big Exploder" << endl;
			cout << "  E - Exit" << endl;

			// asking for input from command line
			cout << "" << "\n   Enter character : " ;
			cin >> userChoice;

			cout << "\n <---------------------------------------------->" << endl;

			// Converts upper case charachters to lower
			userChoice = tolower(userChoice);

			// Executes case depending on user input
			switch (userChoice)
			{
				//Insert element into hash table
			 	 case 'g':
				{
					cout << "\n<---------------------------------------------->" << endl;
					cout << ""<<"		   Glider" << endl;
					cout << "<---------------------------------------------->" << endl;

					shape='g';
					break;
				}

				// Delete element from hash table
				 case 's':
				{
					cout << "\n<---------------------------------------------->" << endl;
					cout << ""<<"		   Small Exploder" << endl;
					cout << "<---------------------------------------------->" << endl;

					shape='s';
					break;
				}

				// look up element from hash table
				 case 'b':
				{
					cout << "\n<---------------------------------------------->" << endl;
					cout << ""<<"		   Large Exploder" << endl;
					cout << "<---------------------------------------------->" << endl;

					shape='b';
					break;
				}
				case 'e':
				{
					cout << "\n<---------------------------------------------->" << endl;
					cout << ""<<"		   EXIT" << endl;
					cout << "<---------------------------------------------->" << endl;
					return true;
					// Returns true to exit the menu ending the program
					break;
				}
				default:
				   {
					// If no case is selected, input did not match a case and was invalid
					cout << "\n Invalid Choice, Please try again" << endl;
					break;
				    }
			} // end switch
			return false;

}


