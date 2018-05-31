#pragma once
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "Vertex.h"
#include <fstream>

class Graph {

private:
	AdjacencyList * adj_list;
	AdjacencyMatrix * adj_matrix;
	
	int edges;
	int vertices;
	Vertex * source_vertex;
	Vertex * destination_vertex;


public:
	Graph();
	~Graph();
	void loadGraphFromFile(std::string file_path);
	void saveGraphToFile(std::string file_path);

};

