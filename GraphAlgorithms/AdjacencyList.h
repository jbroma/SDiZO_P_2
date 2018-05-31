#pragma once
#include "List.h"
#include "Vertex.h"
class AdjacencyList {

private:
	const int NO_EDGE = INT_MIN;
	List<Vertex> ** arr;
	int vertices;
	bool undirected = false;

public:
	AdjacencyList(int vertex_count);
	~AdjacencyList();
	// addEdge does not perform a check whether an edge connecting 2 specified vertices already exists.
	void addEdge(int start, int end, int weight);
	void removeEdge(int start, int end);
	bool isEdge(int start, int end);
	void convertToUndirected();
	std::string toString();
	int findVertex(int start, int end);
};

