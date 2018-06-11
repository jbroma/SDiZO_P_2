#include "stdafx.h"
#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(int vertex_count) {
	this->vertices = vertex_count;
	this->arr = new List<Edge>*[vertices];
	for (int i = 0; i < vertices; i++) {
		this->arr[i] = new List<Edge>();
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
	// Check whether edge already exists
	for (Edge v : *arr[start]) {
		if (v.getEndVertex() == end)
			return;
	}
	this->arr[start]->pushBack(Edge(start, end, weight));
	if (undirected)
		this->arr[end]->pushBack(Edge(end, start, weight));
}

void AdjacencyList::removeEdge(int start, int end) {
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	for (auto it = arr[start]->begin(); it != arr[start]->end(); ++it) {
		if (it->getEndVertex() == end) {
			arr[start]->remove(it);
			break;
		}
	}
	if (undirected) {
		for (auto it = arr[end]->begin(); it != arr[end]->end(); ++it) {
			if (it->getStartVertex() == start) {
				arr[end]->remove(it);
				break;
			}
		}
	}
}

bool AdjacencyList::isEdge(int start, int end) {
	if (start >= vertices || start < 0 || end >= vertices || end < 0)
		throw std::invalid_argument("Invalid vertex parameters");
	for (Edge v : *arr[start]) {
		if (v.getEndVertex() == end)
			return true;
	}
	return false;
}

List<Edge>& AdjacencyList::getAdjacent(int vertex) {
	return *arr[vertex];
}

void AdjacencyList::convertToUndirected() {
	if (undirected)
		return;
	for (int i = 0; i < vertices; ++i) {
		for (auto it = arr[i]->begin(); it != arr[i]->end(); ++it) {
			addEdge(it->getEndVertex(), i, it->getEdgeWeight());
		}
	}
	this->undirected = true;
}

void AdjacencyList::setUndirected() {
	this->undirected = true;
}

std::string AdjacencyList::toString() {
	std::stringstream ss;
	
	for (int i = 0; i < vertices; i++) {
		ss << "Vertex " << i << ": ";
		for (Edge& v : *arr[i]) {
			ss << " => " << v.toString();
		}
		ss << "\n";
	}
	return ss.str();
}




