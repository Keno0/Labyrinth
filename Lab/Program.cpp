#include "Lab.h"

// Driver program to test above functions
int main()
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z

	Labyrinth labyrinth;
	fstream infile;
	int a = 20;
	int b = 20;
	infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Labirint\\Lab\\test5.txt");
	infile << a << " " << b << endl;
	int random = 0;
	for (int i = 0; i < a; i++)
	{
	for (int j = 0; j < 2*b; j++)
	{
	random = std::rand()%6;
	switch (random)
	{
	case 1:
	infile << "C" << " ";
	break;
	case 2:
	infile << "M" << " ";
	break;
	default:
	infile << "W" << " ";
	break;
	}

	}
	infile << endl;
	}
	infile.close();

	return 0;
}