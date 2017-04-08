// A C++ program to find single source longest distances in a DAG

#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#include "Lab.h"
#include <ctime>

using namespace std;


AdjListNode::AdjListNode(int _v, int _w)
{
	v = _v;
	color = _w;
}
int AdjListNode::getV()
{
	return v;
}
int AdjListNode::getWeight()
{
	return color;
}


void Graph::SetListOfMonitor(int *list, int size)
		{
			listOfMonitor = new int[size];
			numberOfMonitor = size;
			for (int i = 0; i < size; i++)
			{
				listOfMonitor[i] = list[i];
			}

		}
bool Graph::isThisVertexMonitor(int vertex)
		{
			for (int i = 0; i < numberOfMonitor; i++)
			{
				if (vertex == listOfMonitor[i])
					return true;
			}
			return false;
		}
Graph::Graph(int V) // Constructor
	{
		this->V = V;
		adj = new list<AdjListNode>[V];
		bestPaths = new int[V];
		path = new int[V];
		


		for (int i = 0; i < V; i++)
			bestPaths[i] = 100000;


	}
void Graph::addEdge(int u, int v, int color)
	{
		AdjListNode node(v, color);
		adj[u].push_back(node); // Add v to u’s list
	}
void Graph::printAllPaths(int s, int d)
	{
		// Mark all the vertices as not visited
		bool *visited = new bool[V];
		this->d = d;
		currentStartingPoint = s;

		vector < vector<size_t>> graph;

		graph.resize(V);
		for (int j = 0; j < V; j++)
		{
			list<AdjListNode>::iterator i;
			int k = 0;
			graph[j].resize(adj[j].size());
			for (i = adj[j].begin(); i != adj[j].end(); ++i)
			{
				graph[j][k] = i->getV();
				k++;
			}
		}

		dfs(s, d, graph);

		// Create an array to store paths		
		

							// Initialize all vertices as not visited
		/*for (int i = 0; i < V; i++)
			visited[i] = false;

		// Call the recursive helper function to print all paths
		printAllPathsUtil(s, visited);

		delete[] visited;*/

	}
// A recursive function to print all paths from 'u' to 'd'.
	// visited[] keeps track of vertices in current path.
	// path[] stores actual vertices and path_index is current
	// index in path[]
void Graph::printAllPathsUtil(int u, bool visited[])
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
					for (j = adj[path[i]].begin(); j != adj[path[i]].end(); ++j)
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
							else if (isThisVertexMonitor(path[i]))
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
						
						printAllPathsUtil(i->getV(), visited);

					}
				}
			
		}

		// Remove current vertex from path[] and mark it as unvisited

		path_index--;
		visited[u] = false;
	}
void Graph::dfs(size_t start, size_t end, const vector<vector<size_t> > &graph)
{

	//initialize:
	//remember the node (first) and the index of the next neighbour (second)
	typedef pair<size_t, size_t> State;
	stack<State> to_do_stack;
	vector<size_t> path; //remembering the way

	vector<bool> visited(graph.size(), false); //caching visited - no need for searching in the path-vector 

											   //start in start!
	to_do_stack.push(make_pair(start, 0));
	visited[start] = true;
	path.push_back(start);

	while (!to_do_stack.empty())
	{
		State &current = to_do_stack.top();//current stays on the stack for the time being...

		if (current.first == end || current.second == graph[current.first].size())//goal reached or done with neighbours?
		{
			if (current.first == end)
			{
				list<AdjListNode>::iterator j;

				for (int i = 0; i < path.size(); i++)
				{
					if (i < path.size() - 1)
					{
						for (j = adj[path[i]].begin(); j != adj[path[i]].end(); ++j)
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
								else if (isThisVertexMonitor(path[i]))
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

			//backtrack:
			visited[current.first] = false;//no longer considered visited
			path.pop_back();//go a step back
			to_do_stack.pop();//no need to explore further neighbours         
		}
		else {//normal case: explore neighbours
			size_t next = graph[current.first][current.second];
			current.second++;//update the next neighbour in the stack!
			if (!visited[next]) {
				//putting the neighbour on the todo-list
				to_do_stack.push(make_pair(next, 0));
				visited[next] = true;
				path.push_back(next);
			}
		}
	}
}

Labyrinth::Labyrinth()
		{
#if(READ_DATA_FROM_FILE)
			ReadDatasFromFile();
#else
			ReadDatasFromConsole();
#endif
			g = new Graph(numberOfVertex);
			g->SetListOfMonitor(monitors, numberOfMonitors);
			CreateEdges();
			FindAllPathBetweenTwoPoints();

		}
void Labyrinth::ReadDatasFromFile()
		{
			ifstream infile;
			infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Labirint\\Lab\\test5.txt");
			infile >> row;
			infile >> column;
			labyrinthCharacters = new char*[row];
			indexOfVertex = new int*[row];
			//Create 2dimansions dynamic array for lab character
			for (int i = 0; i < row; i++)
			{
				indexOfVertex[i] = new int[2 * column];
				labyrinthCharacters[i] = new char[2 * column];
			}
			
			//Read Lab Character
			for (int i = 0; i < row; i++)
				for (int j = 0; j < 2 * column; j++)
					infile >> labyrinthCharacters[i][j];

			//Counting the vertex and the Monitors
			for (int i = 0; i < row; i++)
				for (int j = 0; j < 2 * column; j++)
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						indexOfVertex[i][j] = numberOfVertex;
						numberOfVertex++;
						
					}
					if (labyrinthCharacters[i][j] == 'M')
						numberOfMonitors++;
					//Counting the endpoints
					if (i == 0 || j == 0 || j == 2 * column - 1 || i == row - 1)
					{
						if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
						{
							numberOfEndPoints++;
						}
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
							listOfEndPoints[k] = indexOfVertex[i][j];
							k++;
						}
					}
					else
					{
						if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
						{
							listOfInsidePoints[r] = indexOfVertex[i][j];
							r++;
						}
					}

					if (labyrinthCharacters[i][j] == 'M')
					{
						monitors[h] = indexOfVertex[i][j];
						h++;
					}
				}


		}
void Labyrinth::ReadDatasFromConsole()
		{			
			cin >> row;
			cin >> column;
			labyrinthCharacters = new char*[row];
			indexOfVertex = new int*[row];
			//Create 2dimansions dynamic array for lab character
			for (int i = 0; i < row; i++)
			{
				indexOfVertex[i] = new int[2 * column];
				labyrinthCharacters[i] = new char[2 * column];
			}

			//Read Lab Character
			for (int i = 0; i < row; i++)
				for (int j = 0; j < 2 * column; j++)
					cin >> labyrinthCharacters[i][j];

			//Counting the vertex and the Monitors
			for (int i = 0; i < row; i++)
				for (int j = 0; j < 2 * column; j++)
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						indexOfVertex[i][j] = numberOfVertex;
						numberOfVertex++;

					}
					if (labyrinthCharacters[i][j] == 'M')
						numberOfMonitors++;
					//Counting the endpoints
					if (i == 0 || j == 0 || j == 2 * column - 1 || i == row - 1)
					{
						if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
						{
							numberOfEndPoints++;
						}
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
							listOfEndPoints[k] = indexOfVertex[i][j];
							k++;
						}
					}
					else
					{
						if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
						{
							listOfInsidePoints[r] = indexOfVertex[i][j];
							r++;
						}
					}

					if (labyrinthCharacters[i][j] == 'M')
					{
						monitors[h] = indexOfVertex[i][j];
						h++;
					}
				}


		}
void Labyrinth::CreateEdges()
		{
			for (int i = 0; i < row; i++)
				for (int j = 0; j < 2 * column; j++)
				{
					if (labyrinthCharacters[i][j] == 'C' || labyrinthCharacters[i][j] == 'M')
					{
						if (j < column) // sor elsõ fele
						{
							if (j != 0)
								if (labyrinthCharacters[i][j + column - 1] == 'C' || labyrinthCharacters[i][j + column - 1] == 'M')//bal alsó szomszéd
								{
									//Create Edge both way blue color (0)
									g->addEdge(indexOfVertex[i][j], indexOfVertex[i][j + column - 1], 0);
									g->addEdge(indexOfVertex[i][j + column - 1], indexOfVertex[i][j], 0);
								}
							if (i != row - 1)
								if (labyrinthCharacters[i + 1][j] == 'C' || labyrinthCharacters[i + 1][j] == 'M')//alsó szomszéd
								{
									//Create Edge both way red color (1)
									g->addEdge(indexOfVertex[i][j], indexOfVertex[i + 1][j], 1);
									g->addEdge(indexOfVertex[i + 1][j], indexOfVertex[i][j], 1);
								}

							if (labyrinthCharacters[i][j + column] == 'C' || labyrinthCharacters[i][j + column] == 'M')//jobb alsó szomszéd
							{
								//Create Edge both way green color (2)
								g->addEdge(indexOfVertex[i][j], indexOfVertex[i][ j + +column], 2);
								g->addEdge(indexOfVertex[i][j + +column], indexOfVertex[i][j], 2);
							}
						}
						else if (j >= column && i < row - 1) // sor masodik fele
						{
							if (labyrinthCharacters[i + 1][j - column] == 'C' || labyrinthCharacters[i + 1][j - column] == 'M')//bal alsó szomszéd
							{
								//Create Edge both way blue color (0)
								g->addEdge(indexOfVertex[i][j], indexOfVertex[i + 1][ j - column], 0);
								g->addEdge(indexOfVertex[i + 1][j - column], indexOfVertex[i][j], 0);
							}

							if (labyrinthCharacters[i + 1][j] == 'C' || labyrinthCharacters[i + 1][j] == 'M')//alsó szomszéd
							{
								//Create Edge both way red color (1)
								g->addEdge(indexOfVertex[i + 1][ j], indexOfVertex[i][j], 1);
								g->addEdge(indexOfVertex[i][j], indexOfVertex[i + 1][j], 1);
							}

							if (j < column * 2 - 1)
								if (labyrinthCharacters[i + 1][j - column + 1] == 'C' || labyrinthCharacters[i + 1][j - column + 1] == 'M')//jobb alsó szomszéd
								{
									//Create Edge both way green color (2)
									g->addEdge(indexOfVertex[i][j], indexOfVertex[i + 1][ j - column + 1], 2);
									g->addEdge(indexOfVertex[i + 1][j - column + 1], indexOfVertex[i][j], 2);
								}
						}
					}
				}
		}
bool Labyrinth::IsItEndPoint(int index)
		{
			for (int i = 0; i < numberOfEndPoints; i++)
			{
				if (listOfEndPoints[i] == index)
					return true;
			}

			return false;
		}
void Labyrinth::FindAllPathBetweenTwoPoints()
		{
	clock_t start = clock();
	clock_t end = 0;
			int s = 0, d = 0;
			for (int i = 0; i < numberOfEndPoints; i++)
			{
				for (int j = 0; j < numberOfInsidePoints; j++)
				{
					end = (double)(clock() - start) ;
					if (end > 9000)
						break;
					g->printAllPaths(listOfInsidePoints[j], listOfEndPoints[i]);
				}
				
				if (end > 9000)
					break;
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
									cout << k + 1 << " " << j + 1 << endl;
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