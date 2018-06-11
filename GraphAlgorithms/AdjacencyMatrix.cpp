#include "stdafx.h"
#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(int vertex_count) {
	vertices = vertex_count;
	matrix = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		matrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			// all vertices are disconnected
			matrix[i][j] = NO_EDGE;
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix() {
	for (int i = 0; i < vertices; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void AdjacencyMatrix::addEdge(int start, int end, int weight) {
	// constraint: weight cannot be equal to NO_EDGE
	if (weight == NO_EDGE)
		throw std::invalid_argument("Weight cannot be equal to " + NO_EDGE);
	// constraint: edge cannot exist prior to adding it
	if (matrix[start][end] != NO_EDGE)
		throw std::invalid_argument("Edge already exists!");
	// contstraint: vertices must have a non-negative ID
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	
	matrix[start][end] = weight;
	if (undirected)
		matrix[end][start] = weight;
}

void AdjacencyMatrix::removeEdge(int start, int end) {
	// contstraint: vertices must have a non-negative ID
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	matrix[start][end] = NO_EDGE;
	if (undirected)
		matrix[end][start] = NO_EDGE;
}

bool AdjacencyMatrix::isEdge(int start, int end) {
	// contstraint: vertices must have a non-negative ID
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	return matrix[start][end] != NO_EDGE ? true : false;
}

int AdjacencyMatrix::getWeight(int start, int end) {
	return matrix[start][end];
}

void AdjacencyMatrix::setUndirected() {
	this->undirected = true;
}

void AdjacencyMatrix::convertToUndirected() {
	if (undirected)
		return;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			matrix[j][i] = matrix[i][j];
		}
	}
	this->undirected = true;
}

std::string AdjacencyMatrix::toString() {
	std::stringstream ss;
	ss << "Adjacency Matrix contents:\n";
	ss << "\t";
	for (int i = 0; i < vertices; i++) {
		ss << i << " ";
	}
	ss << "\n";
	for (int i = 0; i < vertices; i++) {
		ss << i << "\t";
		for (int j = 0; j < vertices; j++) {
			if (matrix[i][j] == NO_EDGE)
				ss << "N ";
			else 
				ss << matrix[i][j] << " ";
		}
		ss << "\n";
	}
	return ss.str();
}

