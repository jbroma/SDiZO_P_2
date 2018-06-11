#include "stdafx.h"
#include "Edge.h"
#include <string>
#include <sstream>

Edge::Edge() {
}

Edge::Edge(int start, int end, int edge_weight) {
	this->start_vertex = start;
	this->end_vertex = end;
	this->edge_weight = edge_weight;
}

Edge::Edge(const Edge & other) {
	this->start_vertex = other.start_vertex;
	this->end_vertex = other.end_vertex;
	this->edge_weight = other.edge_weight;
}

Edge::~Edge() {
}

int Edge::getStartVertex() {
	return start_vertex;
}

int Edge::getEndVertex() {
	return end_vertex;
}

int Edge::getEdgeWeight() {
	return edge_weight;
}

std::string Edge::toString() {
	std::stringstream ss;
	ss << "(" << start_vertex << ", " << end_vertex << ")" << " : " << edge_weight;
	return ss.str();
}


