#pragma once
#include "List.h"
#include "Edge.h"
#include <string>
#include <sstream>

class AdjacencyList {

private:
	const int NO_EDGE = INT_MIN;
	List<Edge> ** arr;
	int vertices;
	bool undirected = false;

public:
	AdjacencyList(int vertex_count);
	~AdjacencyList();
	// addEdge does not perform a check whether an edge connecting 2 specified vertices already exists.
	void addEdge(int start, int end, int weight);
	void removeEdge(int start, int end);
	bool isEdge(int start, int end);
	List<Edge>& getAdjacent(int vertex);
	void convertToUndirected();
	void setUndirected();
	std::string toString();
};

