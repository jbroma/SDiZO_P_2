#include "stdafx.h"
#include "Graph.h"


Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::saveGraphToFile(std::string file_path) {
	std::ofstream out;
	out.open(file_path, std::ios::app);
	out << this->edges << " " << this->vertices << " " << this->source_vertex->getVertexID() << " " << this->destination_vertex->getVertexID() << "\n";

	out.close();
}
