// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#define NINF INT_MIN
#define READ_DATA_FROM_FILE 1
using namespace std;

// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode
{
	int v;
	
public:
	int color;
	AdjListNode(int _v, int _w)
	{
		v = _v;
		color = _w;
	}
	int getV()
	{
		return v;
	}
	int getWeight()
	{
		return color;
	}
};

class Result
{
public:
	int startIndex = 0;
	int endIndex = 0;
	int length = 0;
};

// Class to represent a graph using adjacency list representation
class Graph
{
	
	list<Result> *result;
	int V; // No. of vertices�
	int prevColor = -1;
	int pathCounter = 0;
	int *listOfMonitor;
	int numberOfMonitor = 0;
	int currentStartingPoint = 0;
	

		   // Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

	// A function used by longestPath
	void printAllPathsUtil(int, int, bool[], int[], int &);
public:
	int *bestPaths;
	Graph(int V); // Constructor

				  // function to add an edge to graph
	void addEdge(int u, int v, int color);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);

	void SetListOfMonitor(int *list, int size)
	{
		listOfMonitor = new int[size];
		numberOfMonitor = size;
		for (int i = 0; i < size; i++)
		{
			listOfMonitor[i] = list[i];
		}

	}

	bool isThisVertexMonitor(int vertex)
	{
		for (int i = 0; i < numberOfMonitor; i++)
		{
			if (vertex == listOfMonitor[i])
				return true;
		}
		return false;
	}


};



Graph::Graph(int V) // Constructor
{
	this->V = V;
	adj = new list<AdjListNode>[V];
	bestPaths = new int[V];


	for(int i =0; i<V; i++)
		bestPaths[i]= 100000;


}

void Graph::addEdge(int u, int v, int color)
{
	AdjListNode node(v, color);
	adj[u].push_back(node); // Add v to u�s list
}



// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	currentStartingPoint = s;

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

						// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited, path, path_index);
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
	int path[], int &path_index)
{
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	

	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{
		list<AdjListNode>::iterator j;

		for (int i = 0; i < path_index; i++)
		{
			if (i < path_index - 1)
			{
				for ( j = adj[path[i]].begin(); j != adj[path[i]].end(); ++j)
				{
					if (j->getV() == path[i + 1])
					{
						if (prevColor != j->color && isThisVertexMonitor(path[i]))
						{
							pathCounter++;
							prevColor = j->color;
						}
						else if (prevColor != j->color)
						{
							pathCounter++;
							prevColor = j->color;
						}
						else if (isThisVertexMonitor(path[i ]))
						{
							pathCounter++;
						}
						
					}
				}
			}
			//cout << path[i] << " ";

		}
		prevColor = -1;
		//cout <<"Path length:" << pathCounter<< endl;
		if (bestPaths[currentStartingPoint] > pathCounter)
		{
			bestPaths[currentStartingPoint] = pathCounter;
		}
		pathCounter = 0;
	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current vertex
		list<AdjListNode>::iterator i;

		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (!visited[i->getV()])
			{
				printAllPathsUtil(i->getV(), d, visited, path, path_index);
			}
		}
	}

	// Remove current vertex from path[] and mark it as unvisited

	path_index--;
	visited[u] = false;
}


class Labyrinth
{
	Graph *g;
	int row = 0;
	int column = 0;
	int numberOfVertex = 0;
	char **labyrinthCharacters;
	int numberOfEndPoints = 0;
	int numberOfInsidePoints = 0;
	int numberOfMonitors = 0;
	int *listOfEndPoints;
	int *listOfInsidePoints;
	int *monitors;

public:
	Labyrinth()
	{
		ReadDatasFromFile();
		g = new Graph(numberOfVertex);
		g->SetListOfMonitor(monitors, numberOfMonitors);
		CreateEdges();
		FindAllPathBetweenTwoPoints();
		
	}

	void ReadDatasFromFile()
	{
		ifstream infile;
		infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Labirint\\Lab\\test2.txt");
		infile >> row;
		infile >> column;
		labyrinthCharacters = new char*[row];
		//Create 2dimansions dynamic array for lab character
		for (int i = 0; i < row; i++)
			labyrinthCharacters[i] = new char[2 * column];
		//Read Lab Character
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
				infile >> labyrinthCharacters[i][j];

		//Counting the vertex and the Monitors
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
			{
				if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					numberOfVertex++;
				if (labyrinthCharacters[i][j] == 'M')
					numberOfMonitors++;
			}
		
		//Counting the endpoints
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
				if (i == 0 || j == 0 || j == 2*column-1 || i==row-1)
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						numberOfEndPoints++;
					}
				}
		//Store endpoint vertex index
		numberOfInsidePoints = numberOfVertex - numberOfEndPoints;
		listOfEndPoints = new int[numberOfEndPoints];
		listOfInsidePoints = new int[numberOfInsidePoints];
		monitors = new int[numberOfMonitors];
		int k = 0;
		int r = 0;
		int h = 0;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
			{
				if (i == 0 || j == 0 || j == 2 * column - 1 || i == row - 1)
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						listOfEndPoints[k] = IndexOfVertex(i, j);
						k++;
					}
				}
				else
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						listOfInsidePoints[r] = IndexOfVertex(i, j);
						r++;
					}
				}

				if (labyrinthCharacters[i][j] == 'M')
				{
					monitors[h] = IndexOfVertex(i, j);
					h++;
				}
			}

		
	}

	void CreateEdges()
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
			{
				if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
				{
					if ( j < column) // sor els� fele
					{
						if(j != 0)
							if (labyrinthCharacters[i][j + column - 1] == 'C' || labyrinthCharacters[i][j + column - 1] == 'M')//bal als� szomsz�d
							{
								//Create Edge both way blue color (0)
								g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i, j + column - 1), 0);
								g->addEdge(IndexOfVertex(i, j + column - 1), IndexOfVertex(i, j ), 0);
							}
						if(i != row-1)
							if (labyrinthCharacters[i+1][j] == 'C' || labyrinthCharacters[i+1][j] == 'M')//als� szomsz�d
							{
								//Create Edge both way red color (1)
								g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j), 1);
								g->addEdge(IndexOfVertex(i+1, j), IndexOfVertex(i, j), 1);
							}
						
						if (labyrinthCharacters[i][j + column] == 'C' || labyrinthCharacters[i][j + column] == 'M')//jobb als� szomsz�d
						{
							//Create Edge both way green color (2)
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i, j + +column), 2);
							g->addEdge(IndexOfVertex(i, j + +column), IndexOfVertex(i, j), 2);
						}
					}
					else if (j >= column && i < row - 1) // sor masodik fele
					{
						if (labyrinthCharacters[i + 1][j - column] == 'C' || labyrinthCharacters[i+1][j - column] == 'M')//bal als� szomsz�d
						{
							//Create Edge both way blue color (0)
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j - column), 0);
							g->addEdge(IndexOfVertex(i+1, j - column), IndexOfVertex(i, j), 0);
						}

						if (labyrinthCharacters[i + 1][j] == 'C' || labyrinthCharacters[i + 1][j] == 'M')//als� szomsz�d
						{
							//Create Edge both way red color (1)
							g->addEdge(IndexOfVertex(i+1, j), IndexOfVertex(i, j ), 1);
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j), 1);
						}

						if(j < column*2-1)
							if (labyrinthCharacters[i+1][j - column + 1] == 'C' || labyrinthCharacters[i+1][j - column + 1] == 'M')//jobb als� szomsz�d
							{
								//Create Edge both way green color (2)
								g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j - column + 1), 2);
								g->addEdge(IndexOfVertex(i+1, j - column + 1), IndexOfVertex(i, j), 2);
							}
					}
				}
			}
	}

	int IndexOfVertex(int row, int column)
	{
		int index = 0;
		for (int i = 0; i < this->row; i++)
			for (int j = 0; j < this->column*2; j++)
			{
				if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
				{
					index++;					
				}

				if (i == row && j == column)
					return index - 1;

			}

		return index-1;
	}

	bool IsItEndPoint(int index)
	{
		for (int i = 0; i < numberOfEndPoints; i++)
		{
			if (listOfEndPoints[i] == index)
				return true;
		}

		return false;
	}

	void FindAllPathBetweenTwoPoints()
	{
		int s = 0, d = 0;
		for (int i = 0; i < numberOfEndPoints; i++)
		{
			for (int j = 0; j < numberOfInsidePoints; j++)
			{
				
				g->printAllPaths( listOfInsidePoints[j], listOfEndPoints[i]);
			}
		}

		int counterOfHighest = 0;
		int highestValue = 0;
		for (int i = 0; i < numberOfVertex; i++)
		{
			//cout << i<<" "<< g->bestPaths[i] << endl;
			if (!IsItEndPoint(i) && g->bestPaths[i] != 100000)
			{
				if (g->bestPaths[i] > highestValue)
					highestValue = g->bestPaths[i];
			}

		}

		for (int i = 0; i < numberOfVertex; i++)
		{
			if (g->bestPaths[i] == highestValue)
				counterOfHighest++;
		}

		cout << counterOfHighest << " " << highestValue << endl;
		int letterCounter = 0;

		for (int i = 0; i < numberOfVertex; i++)
		{
			if (g->bestPaths[i] == highestValue)
			{
				for (int k = 0; k < row; k++)
				{
					for (int j = 0; j < column * 2; j++)
					{
						if (labyrinthCharacters[k][j] == 'C' || labyrinthCharacters[k][j] == 'M')
						{
							
							if (letterCounter == i)
							{
								cout << k+1 << " " << j+1 << endl;
								k = row;
								j = column * 2;
								
							}
							letterCounter++;
						}
					}
				}

				letterCounter = 0;
			}
		}

		
	}
};




// Driver program to test above functions
int main()
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	
	Labyrinth labyrinth;

	return 0;
}