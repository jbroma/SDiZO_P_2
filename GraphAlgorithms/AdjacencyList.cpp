#include "stdafx.h"
#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(int vertex_count) {
	this->vertices = vertex_count;
	this->arr = new List<Vertex>*[vertices];
	for (int i = 0; i < vertices; i++) {
		this->arr[i] = new List<Vertex>();
	}
}

AdjacencyList::~AdjacencyList() {
	for (int i = 0; i < vertices; i++)
		delete this->arr[i];
	delete[] arr;
}

void AdjacencyList::addEdge(int start, int end, int weight) {
	// We assume that weight cannot be equal to NO_EDGE for compatibility with Adjacency Matrix
	if (weight == NO_EDGE)
		throw std::invalid_argument("Weight cannot be equal to " + NO_EDGE);
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	// TODO: Check if node already exists inside a list
	this->arr[start]->pushBack(Vertex(end, weight));
	if (undirected)
		this->arr[end]->pushBack(Vertex(start, weight));
}

void AdjacencyList::removeEdge(int start, int end) {
	// This requires finding vertex number, need to add find fuction
}

bool AdjacencyList::isEdge(int start, int end) {
	// This requires finding vertex number
	return false;
}

std::string AdjacencyList::toString() {
	/*for (int i = 0; i < vertices; i++) {
		this->arr[i]->
	}*/
	return "xd";
}

int AdjacencyList::findVertex(int start, int end) {
	/*int pos = -1;
	while()*/
	return 0;
}




