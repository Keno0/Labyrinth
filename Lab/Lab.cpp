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
	int color;
public:
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

// Class to represent a graph using adjacency list representation
class Graph
{
	

	int V; // No. of vertices’

		   // Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

	// A function used by longestPath
	void printAllPathsUtil(int, int, bool[], int[], int &);
public:
	Graph(int V); // Constructor

				  // function to add an edge to graph
	void addEdge(int u, int v, int color);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);


};



Graph::Graph(int V) // Constructor
{
	this->V = V;
	adj = new list<AdjListNode>[V];

}

void Graph::addEdge(int u, int v, int color)
{
	AdjListNode node(v, color);
	adj[u].push_back(node); // Add v to u’s list
}



// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

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

		for (int i = 0; i < path_index; i++)
		{
			cout << path[i] << " ";
		}

		cout << endl;
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

public:
	Labyrinth()
	{
		ReadDatasFromFile();
		g = new Graph(numberOfVertex);
		CreateEdges();
		int s = 1, d = 8;
		g->printAllPaths(s, d);
	}

	void ReadDatasFromFile()
	{
		ifstream infile;
		infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Labirint\\Lab\\test1.txt");
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

		//Counting the vertex
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
				if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					numberOfVertex++;		
	}

	void CreateEdges()
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < 2 * column; j++)
			{
				if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
				{
					if ( j < column) // sor elsõ fele
					{
						if(j != 0)
							if (labyrinthCharacters[i][j + column - 1] == 'C' || labyrinthCharacters[i][j + column - 1] == 'M')//bal alsó szomszéd
							{
								//Create Edge both way blue color (0)
								g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i, j + column - 1), 0);
								g->addEdge(IndexOfVertex(i, j + column - 1), IndexOfVertex(i, j ), 0);
							}
						if(i != row-1)
							if (labyrinthCharacters[i+1][j] == 'C' || labyrinthCharacters[i+1][j] == 'M')//alsó szomszéd
							{
								//Create Edge both way red color (1)
								g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j), 1);
								g->addEdge(IndexOfVertex(i+1, j), IndexOfVertex(i, j), 1);
							}
						
						if (labyrinthCharacters[i][j + column] == 'C' || labyrinthCharacters[i][j + column] == 'M')//jobb alsó szomszéd
						{
							//Create Edge both way green color (2)
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i, j + +column), 2);
							g->addEdge(IndexOfVertex(i, j + +column), IndexOfVertex(i, j), 2);
						}
					}
					else if (j >= column && i < row - 1) // sor masodik fele
					{
						if (labyrinthCharacters[i + 1][j - column] == 'C' || labyrinthCharacters[i][j - column] == 'M')//bal alsó szomszéd
						{
							//Create Edge both way blue color (0)
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j - column), 0);
							g->addEdge(IndexOfVertex(i+1, j - column), IndexOfVertex(i, j), 0);
						}

						if (labyrinthCharacters[i + 1][j] == 'C' || labyrinthCharacters[i + 1][j] == 'M')//alsó szomszéd
						{
							//Create Edge both way red color (1)
							g->addEdge(IndexOfVertex(i+1, j), IndexOfVertex(i, j ), 1);
							g->addEdge(IndexOfVertex(i, j), IndexOfVertex(i+1, j), 1);
						}

						if(j < column*2-1)
							if (labyrinthCharacters[i+1][j - column + 1] == 'C' || labyrinthCharacters[i+1][j - column + 1] == 'M')//jobb alsó szomszéd
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
};




// Driver program to test above functions
int main()
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	
	Labyrinth labyrinth;
		
		Graph g(4);

		g.addEdge(0, 1, 0);
		g.addEdge(1, 2, 0);
		g.addEdge(2, 3, 0);
		g.addEdge(0, 3, 0);


		int s = 1, d = 8;
		g.printAllPaths(s, d);


		


	return 0;
}