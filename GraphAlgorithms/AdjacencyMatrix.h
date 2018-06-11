#pragma once
#include <string>
#include <sstream>
#include <List>

class AdjacencyMatrix {
private:
	const int NO_EDGE = INT_MIN;
	int ** matrix;
	int vertices;
	bool undirected = false;

public:
	AdjacencyMatrix(int vertex_count);
	~AdjacencyMatrix();
	// Adds a directed edge between vertices A(start) and B(end). If undirected flag is set, it will also add an edge between B and A resulting in an undirected edge between A and B.
	void addEdge(int start, int end, int weight);
	// Removes a directed edge between vertices A(start) and B(end). If undirected flag is set, it will also remove an edge between B and A.
	void removeEdge(int start, int end);
	// Checks whether an edge exists between vertices A(start) and B(end). This function is unaffected by undirected flag.
	bool isEdge(int start, int end);
	// Retrieves weight of a specified edge
	int getWeight(int start, int end);
	// Sets the undirected flag to TRUE, making all further operations act like the graph is an undirected graph.
	void setUndirected();
	// Converts a graph to an Undirected Graph, making all existing edges undirected.
	void convertToUndirected();
	// Returns a string representing AdjacencyMatrix that can be displayed to the User.
	std::string toString();
};

