#pragma once
#include <string>

class Vertex {

private:
	int vertexID;
	int edgeWeight;

public:
	Vertex();
	Vertex(int vertexID, int edgeWeight);
	Vertex(const Vertex& other);
	~Vertex();
	int getVertexID();
	int getEdgeWeight();
	std::string toString();

	Vertex& operator=(const Vertex& other) {
		this->vertexID = other.vertexID;
		this->edgeWeight = other.edgeWeight;
		return *this;
	}

	bool operator==(const Vertex& other) const {
		return this->vertexID == other.vertexID;
	}
	bool operator!=(const Vertex& other) const {
		return this->vertexID == other.vertexID;
	}
};

