#include <iostream>
#include <string>

using namespace std;

class Labyrinth
{
private:
	int k = 0;
	int n = 0;

	char labyrinthValues[500][1000];

public:

	

	void ReadDimensions()
	{
		cin >> k;
		cin >> n;
	}

	void ReadLabyrinth()
	{
		string line = "";
		getline(cin, line);
		for (int i = 0; i < k; i++)
		{
			getline(cin, line);
			
			for (int j=0; j < n * 2; j++)
			{
				
				labyrinthValues[i][j] = line[j*2];
			}
		}
	}

	void PrintOutLab()
	{
		for (int i = 0; i < k; i++)
		{
			
			for (int j = 0; j < n ; j++)
			{

				cout << labyrinthValues[i][j];
				cout << " ";
			}

			cout << endl;
			cout << " ";
			for (int j = n; j < n*2; j++)
			{

				cout << labyrinthValues[i][j];
				cout << " ";
			}

			cout << endl;
		}
	}
};

void main()
{
	Labyrinth labyrinth;
	labyrinth.ReadDimensions();
	labyrinth.ReadLabyrinth();
	labyrinth.PrintOutLab();
}