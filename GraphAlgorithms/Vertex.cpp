#include "stdafx.h"
#include "Vertex.h"
#include <string>
#include <sstream>

Vertex::Vertex() {
}

Vertex::Vertex(int vertexID, int edgeWeight) {
	this->vertexID = vertexID;
	this->edgeWeight = edgeWeight;
}

Vertex::Vertex(const Vertex & other) {
	this->vertexID = other.vertexID;
	this->edgeWeight = other.edgeWeight;
}

Vertex::~Vertex() {
}

int Vertex::getVertexID() {
	return this->vertexID;
}

int Vertex::getEdgeWeight() {
	return this->edgeWeight;
}

std::string Vertex::toString() {
	std::stringstream ss;
	ss << "(" << vertexID << " : " << edgeWeight << ")";
	return ss.str();
}
