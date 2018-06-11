#pragma once
#include <string>
#include <iostream>

class Edge {

private:
	int start_vertex;
	int end_vertex;
	int edge_weight;

public:
	Edge();
	Edge(int start, int end, int edgeWeight);
	Edge(const Edge& other);
	~Edge();
	int getStartVertex();
	int getEndVertex();
	int getEdgeWeight();
	std::string toString();

	Edge& operator=(const Edge& other) {
		this->start_vertex = other.start_vertex;
		this->end_vertex = other.end_vertex;
		this->edge_weight = other.edge_weight;
		return *this;
	}

	bool operator==(const Edge& other) const {
		return	(this->start_vertex == other.start_vertex) &&
				(this->end_vertex == other.end_vertex);
	}

	bool operator!=(const Edge& other) const {
		return	(this->start_vertex != other.start_vertex) &&
				(this->end_vertex != other.end_vertex);
	}
	
	friend std::ostream& operator<<(std::ostream& output, const Edge& v) {
		output << "(" << v.start_vertex << ", " << v.end_vertex << ")";
		return output;
	}
};

