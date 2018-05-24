#pragma once
class Vertex {

private:
	int vertexID;
	int edgeWeight;

public:
	Vertex(int vertexID, int edgeWeight);
	~Vertex();
	int getVertexID();
	int getEdgeWeight();
};

