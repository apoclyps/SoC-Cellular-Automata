#include <iostream>
#include <cstdlib>

using namespace std;

void setupparentGeneration();
void printparentGeneration();
void updateparentGeneration();
int findNextCellState(int left_neighbor, int cell, int right_neighbor);

const int WIDTH = 31;
int parentGeneration[WIDTH];
int i = 0;
int childGeneration[WIDTH];
int lives;

int main()
{
	cout << " Enter number of generations :" << endl;
	cin >> lives;

	setupparentGeneration();
    printparentGeneration();

	//cout << " TABLE" << endl;
    for (int i = 0; i < lives; i++)
    {
        updateparentGeneration();
        printparentGeneration();
    }

	return 0;
}

// The setupparentGeneration function creates an initial state for the cellular autonoma
void setupparentGeneration()
{
	for(i = 0; i < WIDTH; ++i)
	{
		if(i != ((WIDTH/2)))
		{
			parentGeneration[i] = 0;
		}

		if(i == ((WIDTH/2)))
		{
			parentGeneration[i] = 1;
		}
	}
}

// The printparentGeneration function outputs the state of the parentGeneration to the user.  For all
// cells that are 0, it outputs a space (" "), for all cells that are 1, it
// outputs a star ("*")
void printparentGeneration()
{
	for(i = 0; i < WIDTH; ++i)
	{
		if(parentGeneration[i] == 0)
		{

			cout << "[ ]";
			//cout << "   ";
		}

		if(parentGeneration[i] == 1)
		{

			cout << "[+]";
		}
	}
	cout << endl;
}

// The updateparentGeneration function updates the contents of the parentGeneration after calculating
// the next states using the findNextCellState function
void updateparentGeneration()
{
	parentGeneration[WIDTH] = findNextCellState((WIDTH-1), parentGeneration[WIDTH], parentGeneration[0]);
	parentGeneration[WIDTH] = findNextCellState((WIDTH), parentGeneration[0], parentGeneration[1]);

	for(i = 0; i < WIDTH; ++i)
	{
		childGeneration[i] = findNextCellState(parentGeneration[i-1], parentGeneration[i], parentGeneration[i+1]);

	}
	for(i = 0; i < WIDTH; ++i)
	{
		parentGeneration[i] = childGeneration[i];
	}
}

// The states for this are:
//
// 111 110 101 100 011 010 001 000
//  0   0   0   1   1   1   1   0

int findNextCellState(int left_neighbor, int cell, int right_neighbor)
{
	// 111
	if (left_neighbor==1 && cell==1 && right_neighbor==1)
	{
		return 0;
	}
	else if (left_neighbor==1 && cell==1 && right_neighbor==0)
	{
		return 0;
	}
	else if (left_neighbor==1 && cell==0 && right_neighbor==1)
	{
		return 0;
	}
	else if (left_neighbor==1 && cell==0 && right_neighbor==0)
	{
		return 1;
	}
	else if (left_neighbor==0 && cell==1 && right_neighbor==1)
	{
		return 1;
	}
	else if (left_neighbor==0 && cell==1 && right_neighbor==0)
	{
		return 1;
	}
	else if (left_neighbor==0 && cell==0 && right_neighbor==1)
	{
		return 1;
	}
	else if (left_neighbor==0 && cell==0 && right_neighbor==0)
	{
		return 0;
	}

}

