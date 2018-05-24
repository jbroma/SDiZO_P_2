#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex(int vertexID, int edgeWeight) {
	this->vertexID = vertexID;
	this->edgeWeight = edgeWeight;
}


Vertex::~Vertex() {
}

int Vertex::getVertexID() {
	return this->vertexID;
}

int Vertex::getEdgeWeight() {
	return this->edgeWeight;
}
