#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Labyrinth
{
private:
	int k = 0;
	int n = 0;

	char labyrinthValues[500][1000];
	int ** labyrinthStepValues;

public:


	void ReadDimensions()
	{
		cin >> k;
		cin >> n;
	}

	void ReadDimensionFromFile()
	{
		ifstream infile;
		string line = "";
		infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Labirint\\Lab\\test1.txt");
		getline(infile, line);
		k = 5;
		n = 6;

		labyrinthStepValues = new int*[k];
		for (int i = 0; i < k; ++i)
			labyrinthStepValues[i] = new int[n * 2];
		for (int i = 0; i < k; i++)
		{
			getline(infile, line);

			for (int j = 0; j < n * 2; j++)
			{

				labyrinthValues[i][j] = line[j * 2];
				labyrinthStepValues[i][j] = -1;
			}
		}
	}

	void ReadLabyrinth()
	{
		string line = "";
		getline(cin, line);
		labyrinthStepValues = new int*[k];
		for (int i = 0; i < k; ++i)
			labyrinthStepValues[i] = new int[n*2];
		for (int i = 0; i < k; i++)
		{
			getline(cin, line);
			
			for (int j=0; j < n * 2; j++)
			{
				
				labyrinthValues[i][j] = line[j*2];
				labyrinthStepValues[i][j] = -1;
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

		cout << endl; 
		cout << endl;
	}

	void PrintOutLabStepValues()
	{
		for (int i = 0; i < k; i++)
		{

			for (int j = 0; j < n; j++)
			{

				cout << labyrinthStepValues[i][j];
				cout << "   ";
			}

			cout << endl;
			cout << "  ";
			for (int j = n; j < n * 2; j++)
			{

				cout << labyrinthStepValues[i][j];
				cout << "   ";
			}

			cout << endl;
		}

		cout << endl;
		cout << endl;
	}

	void  Check()
	{
		CheckWalls();
		CheckEscapePoints();
		CheckCloseLoop();
	}

	void CheckWalls()
	{
		for (int i = 0; i < k; i++)
		{	

			for (int j = 0; j < n * 2; j++)
			{

				if (labyrinthValues[i][j] == 'W')
				{
					labyrinthStepValues[i][j] = 0;
				}
			}
		}
	}

	void CheckEscapePoints()
	{
		for (int j = 0; j < n * 2; j++)
		{

			if (labyrinthValues[0][j] == 'C' || labyrinthValues[0][j] == 'M')
			{
				labyrinthStepValues[0][j] = 1;
			}
		}

		for (int j = 0; j < n * 2; j++)
		{

			if (labyrinthValues[k-1][j] == 'C' || labyrinthValues[k - 1][j] == 'M')
			{
				labyrinthStepValues[k - 1][j] = 1;
			}
		}

		for (int j = 0; j <k; j++)
		{

			if (labyrinthValues[j][0] == 'C' || labyrinthValues[j][0] == 'M')
			{
				labyrinthStepValues[j][0] = 1;
			}
		}

		for (int j = 0; j <k; j++)
		{

			if (labyrinthValues[j][2*n-1] == 'C' || labyrinthValues[j][2 * n - 1] == 'M')
			{
				labyrinthStepValues[j][2 * n - 1] = 1;
			}
		}
	}

	void CheckCloseLoop()
	{
		for (int i = 1; i < k; i++)
		{

			for (int j = 1; j < n * 2; j++)
			{
				if (j < n)
				{
					if (labyrinthValues[i - 1][j] == 'W'
						&& labyrinthValues[i + 1][j] == 'W'
						&& labyrinthValues[i - 1][j + n] == 'W'
						&& labyrinthValues[i - 1][j + n - 1] == 'W'
						&& labyrinthValues[i][j + n] == 'W'
						&& labyrinthValues[i][j + n - 1] == 'W')
					{
						labyrinthStepValues[i][j] = 0;
					}
				}
				else
				{
					if (labyrinthValues[i - 1][j] == 'W'
						&& labyrinthValues[i + 1][j] == 'W'
						&& labyrinthValues[i][j - n] == 'W'
						&& labyrinthValues[i][j - n + 1] == 'W'
						&& labyrinthValues[i+1][j - n] == 'W'
						&& labyrinthValues[i+1][j - n + 1] == 'W')
					{
						labyrinthStepValues[i][j] = 0;
					}
				}
				
			}
		}
	}

	int NoWall_Monitor(int current, int oddLeftDownValue, char oddLeftDownType)
	{

	}

	void CalculateSteps()
	{
		for (int i = 0; i < k; i++)
		{

			for (int j = 0; j < n * 2; j++)
			{
				if (labyrinthStepValues[i][j] != 0)
				{
					//1.sor elso fele
					if (i == 0 && j < n)
					{
						if (labyrinthValues[i][j] == 'M')
						{
							if (j != 0)
							{
								if (labyrinthValues[i][j + n - 1] != 'W')
								{
									if (labyrinthStepValues[i][j + n - 1] == -1)
									{
										labyrinthStepValues[i][j + n - 1] = 2;
									}
									else
									{
										if (labyrinthStepValues[i][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n - 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}
							}
							if (labyrinthValues[i][j + n ] != 'W')
							{
								if (labyrinthStepValues[i][j + n ] == -1)
								{
									labyrinthStepValues[i][j + n ] = 2;
								}
								else
								{
									if (labyrinthStepValues[i][j + n ] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j + n ] = labyrinthStepValues[i][j] + 1;
									}
								}

							}

							if (labyrinthValues[i+1][j] != 'W')
							{
								if (labyrinthStepValues[i+1][j] == -1)
								{
									labyrinthStepValues[i+1][j] = 2;
								}
								else
								{
									if (labyrinthStepValues[i+1][j] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i+1][j] = labyrinthStepValues[i][j] + 1;
									}
								}

							}
						}
						else
						{
							if (j != 0)
							{
								if (labyrinthValues[i][j + n - 1] != 'W')
								{
									if (labyrinthStepValues[i][j + n - 1] == -1)
									{
										labyrinthStepValues[i][j + n - 1] = 1;
									}
									else
									{
										if (labyrinthStepValues[i][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n - 1] = labyrinthStepValues[i][j];
										}
									}

								}
							}

							if (labyrinthValues[i][j + n] != 'W')
							{
								if (labyrinthStepValues[i][j + n] == -1)
								{
									labyrinthStepValues[i][j + n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i][j + n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j + n] = labyrinthStepValues[i][j];
									}
								}

							}

							if (labyrinthValues[i + 1][j] != 'W')
							{
								if (labyrinthStepValues[i + 1][j] == -1)
								{
									labyrinthStepValues[i + 1][j] = 1;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] ;
									}
								}

							}
						}
					} 
					//1.sor masodik fele
					else if (i == 0 && j >= n)
					{
						if (labyrinthValues[i][j] == 'M') {
							if (j != n - 1)
							{
								if (labyrinthValues[i + 1][j - n + 1] != 'W')
								{
									if (labyrinthStepValues[i + 1][j - n + 1] == -1)
									{
										labyrinthStepValues[i + 1][j - n + 1] = 2;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}
							}
							if (labyrinthValues[i + 1][j - n] != 'W')
							{
								if (labyrinthStepValues[i + 1][j - n] == -1)
								{
									labyrinthStepValues[i + 1][j - n] = 2;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j] + 1;
									}
								}

							}

							if (labyrinthValues[i + 1][j] != 'W')
							{
								if (labyrinthStepValues[i + 1][j] == -1)
								{
									labyrinthStepValues[i + 1][j] = 2;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] + 1;
									}
								}

							}
						}

						else
						{
							if (j != n - 1)
							{
								if (labyrinthValues[i + 1][j - n + 1] != 'W')
								{
									if (labyrinthStepValues[i][j - n + 1] == -1)
									{
										labyrinthStepValues[i][j - n + 1] = 1;
									}
									else
									{
										if (labyrinthStepValues[i][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j];
										}
									}

								}
							}

							if (labyrinthValues[i + 1][j - n] != 'W')
							{
								if (labyrinthStepValues[i + 1][j - n] == -1)
								{
									labyrinthStepValues[i + 1][j - n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j];
									}
								}

							}

							if (labyrinthValues[i + 1][j] != 'W')
							{
								if (labyrinthStepValues[i + 1][j] == -1)
								{
									labyrinthStepValues[i + 1][j] = 1;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j];
									}
								}

							}
						}

					}
					//bal oldal, kiveve az elso sort
					else if (j == 0)
					{
						if (labyrinthValues[i][j] == 'M')
						{
							if (labyrinthValues[i][j + n] != 'W')
							{
								if (labyrinthStepValues[i][j + n ] == -1)
								{
									labyrinthStepValues[i][j + n] = 2;
								}
								else
								{
									if (labyrinthStepValues[i][j + n ] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j + n ] = labyrinthStepValues[i][j] + 1;
									}
								}
							}

							if (labyrinthValues[i-1][j + n] != 'W')
							{
								if (labyrinthStepValues[i-1][j + n] == -1)
								{
									labyrinthStepValues[i-1][j + n] = 2;
								}
								else
								{
									if (labyrinthStepValues[i-1][j + n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i-1][j + n] = labyrinthStepValues[i][j] + 1;
									}
								}
							}
						}
						else
						{
							if (labyrinthValues[i][j + n] != 'W')
							{
								if (labyrinthStepValues[i][j + n] == -1)
								{
									labyrinthStepValues[i][j + n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i][j + n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j + n] = labyrinthStepValues[i][j];
									}
								}
							}

							if (labyrinthValues[i - 1][j + n] != 'W')
							{
								if (labyrinthStepValues[i - 1][j + n] == -1)
								{
									labyrinthStepValues[i - 1][j + n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i - 1][j + n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i - 1][j + n] = labyrinthStepValues[i][j];
									}
								}
							}
						}
					}
					//jobb oldal, kiveve az elso sort
					else if (j == 2*n-1 && i < k-1)
					{
						if (labyrinthValues[i][j] == 'M')
						{
							if (labyrinthValues[i][j - n] != 'W')
							{
								if (labyrinthStepValues[i][j - n] == -1)
								{
									labyrinthStepValues[i][j - n] = 2;
								}
								else
								{
									if (labyrinthStepValues[i][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j] + 1;
									}
								}
							}

							if (labyrinthValues[i + 1][j - n] != 'W')
							{
								if (labyrinthStepValues[i + 1][j - n] == -1)
								{
									labyrinthStepValues[i + 1][j - n] = 2;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j] + 1;
									}
								}
							}
						}
						else
						{
							if (labyrinthValues[i][j - n] != 'W')
							{
								if (labyrinthStepValues[i][j - n] == -1)
								{
									labyrinthStepValues[i][j - n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j];
									}
								}
							}

							if (labyrinthValues[i + 1][j - n] != 'W')
							{
								if (labyrinthStepValues[i + 1][j - n] == -1)
								{
									labyrinthStepValues[i + 1][j - n] = 1;
								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j];
									}
								}
							}
						}
					}
					//belso resz lefele frissit
					else if (i < k - 1)
					{
						//elso resz
						if ( j < n)
						{
							if (labyrinthValues[i][j] == 'M')
							{
								
								if (labyrinthValues[i][j + n - 1] != 'W') //also bal 6szog
								{
									if (labyrinthStepValues[i][j + n - 1] == -1)
									{
										labyrinthStepValues[i][j + n - 1] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n - 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								
								if (labyrinthValues[i][j + n] != 'W') //also jobb 6szog
								{
									if (labyrinthStepValues[i][j + n] == -1)
									{
										labyrinthStepValues[i][j + n] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i][j + n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i-1][j + n - 1] != 'W') //felso bal 6szog
								{
									if (labyrinthStepValues[i-1][j + n - 1] == -1)
									{
										labyrinthStepValues[i-1][j + n - 1] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i-1][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i-1][j + n - 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}


								if (labyrinthValues[i-1][j + n] != 'W') //felso jobb 6szog
								{
									if (labyrinthStepValues[i-1][j + n] == -1)
									{
										labyrinthStepValues[i-1][j + n] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i-1][j + n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i-1][j + n] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i + 1][j] != 'W') //Lenti 6szog
								{
									if (labyrinthStepValues[i + 1][j] == -1)
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i - 1][j] != 'W') // Fenti hatszog
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j] + 1;
										}
									}

								}
							}
							else // Ha nincs monitor
							{
								
								if (labyrinthValues[i-1][j +n -1] != 'W' && labyrinthValues[i][j + n] != 'W') //bal felso es jobb also nem fal
								{
									if (labyrinthStepValues[i][j + n ] == -1)
									{
										labyrinthStepValues[i][j + n ] = labyrinthValues[i][j ];
									}
									else
									{
										if (labyrinthStepValues[i][j + n ] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n ] = labyrinthStepValues[i][j];
										}
									}

								}

								if (labyrinthValues[i - 1][j + n ] != 'W' && labyrinthValues[i][j + n-1] != 'W') // felso jobb es also bal nem fal
								{
									if (labyrinthStepValues[i][j + n-1] == -1)
									{
										labyrinthStepValues[i][j + n-1] = labyrinthValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i][j + n-1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j + n-1] = labyrinthStepValues[i][j];
										}
									}

								}

								if (labyrinthValues[i - 1][j] != 'W' && labyrinthValues[i+1][j] != 'W') // felso es also nem fal
								{
									if (labyrinthStepValues[i+1][j] == -1)
									{
										labyrinthStepValues[i+1][j] = labyrinthValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i+1][j ] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i+1][j ] = labyrinthStepValues[i][j];
										}
									}

								}

								
							}
						}
						//1.sor masodik fele
						//elso resz
						else if (j >= n)
						{
							if (labyrinthValues[i][j] == 'M')
							{

								if (labyrinthValues[i + 1][j - n] != 'W') //also bal 6szog
								{
									if (labyrinthStepValues[i + 1][j - n] == -1)
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j] + 1;
										}
									}

								}


								if (labyrinthValues[i + 1][j - n + 1] != 'W') //also jobb 6szog
								{
									if (labyrinthStepValues[i + 1][j - n + 1] == -1)
									{
										labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i][j - n] != 'W') //felso bal 6szog
								{
									if (labyrinthStepValues[i][j - n] == -1)
									{
										labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j] + 1;
										}
									}

								}


								if (labyrinthValues[i][j - n + 1] != 'W') //felso jobb 6szog
								{
									if (labyrinthStepValues[i][j - n + 1] == -1)
									{
										labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i + 1][j] != 'W') //Lenti 6szog
								{
									if (labyrinthStepValues[i + 1][j] == -1)
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j] + 1;
										}
									}

								}

								if (labyrinthValues[i - 1][j] != 'W') // Fenti hatszog
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j] + 1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j] + 1;
										}
									}

								}
							}
							else // Ha nincs monitor
							{

								if (labyrinthValues[i][j - n] != 'W' && labyrinthValues[i + 1][j - n + 1] != 'W') //bal felso es jobb also nem fal
								{
									if (labyrinthStepValues[i + 1][j - n + 1] == -1)
									{
										labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n + 1] == -1)
									{
										labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n + 1] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i][j - n + 1] != 'W' && labyrinthValues[i + 1][j - n] != 'W') // felso jobb es also bal nem fal
								{
									if (labyrinthStepValues[i + 1][j - n] == -1)
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i + 1][j - n] == -1)
									{
										labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j - n] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i - 1][j] != 'W' && labyrinthValues[i + 1][j] != 'W') // felso es also nem fal
								{
									if (labyrinthStepValues[i + 1][j] == -1)
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j];
										}
									}

								}

								else
								{
									if (labyrinthStepValues[i + 1][j] == -1)
									{
										labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i + 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i + 1][j] = labyrinthStepValues[i][j]+1;
										}
									}
								}
							}
						}

							
					}
					//belso resz felfele frissit
					else if (i < k - 1)
					{
						//elso resz
						if (j < n)
						{
							
							

								if (labyrinthValues[i - 1][j + n - 1] != 'W' && labyrinthValues[i][j + n] != 'W') //bal felso es jobb also nem fal
								{
									if (labyrinthStepValues[i - 1][j + n - 1] == -1)
									{
										labyrinthStepValues[i - 1][j + n - 1] = labyrinthValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i - 1][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j + n - 1] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i - 1][j + n - 1] == -1)
									{
										labyrinthStepValues[i - 1][j + n - 1] = labyrinthValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j + n - 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j + n - 1] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i - 1][j + n] != 'W' && labyrinthValues[i][j + n - 1] != 'W') // felso jobb es also bal nem fal
								{
									if (labyrinthStepValues[i - 1][j + n] == -1)
									{
										labyrinthStepValues[i - 1][j + n] = labyrinthValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i - 1][j + n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j + n] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i - 1][j + n] == -1)
									{
										labyrinthStepValues[i - 1][j + n] = labyrinthValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j + n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j + n] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i - 1][j] != 'W' && labyrinthValues[i + 1][j] != 'W') // felso es also nem fal
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j]+1;
										}
									}
								}


							
						}
						//1.sor masodik fele
						//elso resz
						else if (j >= n)
						{
							

								if (labyrinthValues[i][j - n] != 'W' && labyrinthValues[i + 1][j - n + 1] != 'W') //bal felso es jobb also nem fal
								{
									if (labyrinthStepValues[i][j - n] == -1)
									{
										labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i][j - n] == -1)
									{
										labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i][j - n] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i][j - n + 1] != 'W' && labyrinthValues[i + 1][j - n] != 'W') // felso jobb es also bal nem fal
								{
									if (labyrinthStepValues[i][j - n + 1] == -1)
									{
										labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i][j - n + 1] == -1)
									{
										labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i][j - n + 1] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i][j - n + 1] = labyrinthStepValues[i][j]+1;
										}
									}
								}

								if (labyrinthValues[i - 1][j] != 'W' && labyrinthValues[i + 1][j] != 'W') // felso es also nem fal
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j];
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j];
										}
									}

								}
								else
								{
									if (labyrinthStepValues[i - 1][j] == -1)
									{
										labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j]+1;
									}
									else
									{
										if (labyrinthStepValues[i - 1][j] > labyrinthStepValues[i][j])
										{
											labyrinthStepValues[i - 1][j] = labyrinthStepValues[i][j]+1;
										}
									}
								}
							
						}


					}
				}
			}
		}
	}
};

void main()
{
	Labyrinth labyrinth;
	//labyrinth.ReadDimensions();
	//labyrinth.ReadLabyrinth();
	labyrinth.ReadDimensionFromFile();
	labyrinth.Check();
	for(int i=0; i < 6; i++)
		labyrinth.CalculateSteps();
	labyrinth.PrintOutLab();
	labyrinth.PrintOutLabStepValues();

}