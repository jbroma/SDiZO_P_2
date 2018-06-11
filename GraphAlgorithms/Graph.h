#pragma once
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "Edge.h"
#include "PriorityQueue.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Graph {

private:
	AdjacencyMatrix * adj_matrix;
	AdjacencyList * adj_list;
	struct DisjointSet;
	// These fields are initialized when loading a graph or generating a random one
	int edges;
	int vertices;
	int source_vertex;
	int destination_vertex;
	
	// Filepath in case we want to reload the graph
	std::string source_file_path;
	// Indicates whether graph was properly loaded from file
	bool status;
	// If undirected is set to true, it means that conversion has occured
	bool undirected;
	// manual_mode flag is used for printing algorithm results;
	bool manual_mode;
	// output stores the result of the last algorithm
	std::string output;

	// Helper functions for different algorithms
	void union_kruskal(int& x, int& y, DisjointSet** sets);
	int find_kruskal(int& vertex, DisjointSet** sets);


public:
	Graph();
	~Graph();
	bool getStatus();
	bool getManualMode();
	void setManualMode(bool mode);
	std::string getSourceFilePath();
	void setSourceFilePath(std::string path);
	std::string MatrixToString();
	std::string ListToString();
	std::string& getAlgorithmOutput();
	void setUndirected();
	bool getUndirected();
	void loadGraphFromFile(std::string file_path);
	void saveGraphToFile(std::string file_path);
	
	// Shortest Path Algorithms
	void spDijkstraMatrix();
	void spDijkstraList();
	void spBellmanFordMatrix();
	void spBellmanFordList();

	// Minimal Spanning Tree Algorithms
	void mstPrimMatrix();
	void mstPrimList();
	void mstKruskalMatrix();
	void mstKruskalList();

	// Maximum Flow Algorithms	
	void mfBFSMatrix() {};
	void mfBFSList() {};
	void mfDFSMatrix() {};
	void mfDFSList() {};
};

struct Graph::DisjointSet {
	int parent;
	int rank;
	DisjointSet(int parent) : parent(parent), rank(0) {
	};
};

