// A C++ program to find single source longest distances in a DAG

#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#include <vector>
#define NINF INT_MIN
#define READ_DATA_FROM_FILE 0

using namespace std;

// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge


class AdjListNode
{
	int v;

public:
	int color;
	AdjListNode(int _v, int _w);
	int getV();
	int getWeight();
};


// Class to represent a graph using adjacency list representation
class Graph
{

	int V; // No. of vertices’
	int prevColor = -1;
	int pathCounter = 0;
	int *listOfMonitor;
	int numberOfMonitor = 0;
	int currentStartingPoint = 0;
	int *path;
	int d = 0;
	int path_index = 0; // Initialize path[] as empty
	list < vector<size_t>> finalPath;


						// Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

	// A function used by longestPath
	void printAllPathsUtil(int, bool[]);
public:
	int *bestPaths;
	int callCounter = 0;
	Graph(int V); // Constructor

				  // function to add an edge to graph
	void addEdge(int u, int v, int color);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);

	void SetListOfMonitor(int *list, int size);

	bool isThisVertexMonitor(int vertex);

	void Graph::dfs(size_t start, size_t end, const vector<vector<size_t> > &graph);

};


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
	int **indexOfVertex;

public:
	Labyrinth();
	void ReadDatasFromFile();
	void ReadDatasFromConsole();
	void CreateEdges();
	bool IsItEndPoint(int index);
	void FindAllPathBetweenTwoPoints();
};
