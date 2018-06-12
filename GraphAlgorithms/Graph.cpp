#include "stdafx.h"
#include "Graph.h"


Graph::Graph() :
	status(false),
	undirected(false),
	manual_mode(false)
{}

Graph::~Graph() {
	delete adj_list;
	delete adj_matrix;
}

bool Graph::getStatus() {
	return status;
}

bool Graph::getManualMode() {
	return this->manual_mode;
}

void Graph::setManualMode(bool mode) {
	this->manual_mode = mode;
}

std::string Graph::getSourceFilePath() {
	return this->source_file_path;
}

void Graph::setSourceFilePath(std::string path) {
	this->source_file_path = path;
}

std::string Graph::MatrixToString() {
	return adj_matrix->toString();
}

std::string Graph::ListToString() {
	return adj_list->toString();
}

std::string& Graph::getAlgorithmOutput() {
	return output;
}

void Graph::setUndirected() {
	adj_list->convertToUndirected();
	adj_matrix->convertToUndirected();
	this->undirected = true;
}

bool Graph::getUndirected() {
	return undirected;
}

void Graph::loadGraphFromFile(std::string file_path) {
	this->status = false;
	std::ifstream file(file_path);
	int* initial_params[4] = { &this->edges, &this->vertices, &this->source_vertex, &this->destination_vertex };
	int edge[3];
	if (file.is_open()) {
		for (int i = 0; i < 4; ++i) {
			file >> *initial_params[i];
			if (file.fail()) {
				std::cout << "File error / READ / Initial Parameters" << std::endl;
				system("PAUSE");
				return;
			}
		}
		this->adj_list = new AdjacencyList(this->vertices);
		this->adj_matrix = new AdjacencyMatrix(this->vertices);
		for (int i = 0; i < edges; ++i) {
			for (int j = 0; j < 3; ++j) {
				file >> edge[j];
				if (file.fail()) {
					std::cout << "File error / READ / Edge data" << std::endl;
					system("PAUSE");
					return;
				}
			}
			adj_matrix->addEdge(edge[0], edge[1], edge[2]);
			adj_list->addEdge(edge[0], edge[1], edge[2]);
		}
		file.close();
		this->status = true;
		return;
	}
	else {
		std::cout << "File error / OPEN" << std::endl;
		system("PAUSE");
		return;
	}
}

void Graph::saveGraphToFile(std::string file_path) {
	// not implemented
}

void Graph::spDijkstraMatrix() {
	
	auto queue = new PriorityQueue<int>;
	auto dist = new int[vertices];
	auto prev = new int[vertices];
	
	for (int i = 0; i < vertices; ++i) {
		dist[i] = INT_MAX;
		prev[i] = -1;
		queue->insert(i, dist[i]);
	}
	queue->decreaseKey(source_vertex, 0);
	dist[source_vertex] = 0;
	int u, v, weight;
	while (!queue->isEmpty()) {
		u = queue->popMin();
		for (v = 0; v < vertices; ++v) {
			if (u != v && adj_matrix->isEdge(u, v)) {
				weight = adj_matrix->getWeight(u, v);
				if (dist[v] > dist[u] + weight) {
					dist[v] = dist[u] + weight;
					queue->decreaseKey(v, dist[v]);
					prev[v] = u;
				}
			}
		}
	}
	
	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		ss << "Start: " << source_vertex << "\n\n";
		ss << "  END\t  DIST\t  PATH\n";
		for (int i = 0; i < vertices; ++i) {
			ss << "  " << i << "\t|  " << dist[i] << "\t|  ";
			int j = i;
			ss << j << " ";
			while (j != 0) {
				ss << prev[j] << " ";
				j = prev[j];
			}
			ss << "\n";
		}
		this->output = ss.str();
	}

	delete queue;
	delete[] dist;
	delete[] prev;
}

void Graph::spDijkstraList() {
	
	auto queue = new PriorityQueue<int>;
	auto dist = new int[vertices];
	auto prev = new int[vertices];

	for (int i = 0; i < vertices; ++i) {
		dist[i] = INT_MAX;
		prev[i] = -1;
		queue->insert(i, dist[i]);
	}
	queue->decreaseKey(source_vertex, 0);
	dist[source_vertex] = 0;
	int u, v, weight;
	
	while (!queue->isEmpty()) {
		u = queue->popMin();
		auto& adjacent = adj_list->getAdjacent(u);
		for (Edge& e : adjacent) {
			v = e.getEndVertex();
			weight = e.getEdgeWeight();
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				queue->decreaseKey(v, dist[v]);
				prev[v] = u;
			}
		}
	}

	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		ss << "Start: " << source_vertex << "\n\n";
		ss << "  END\t  DIST\t  PATH\n";
		for (int i = 0; i < vertices; ++i) {
			ss << "  " << i << "\t|  " << dist[i] << "\t|  ";
			int j = i;
			ss << j << " ";
			while (j != 0) {
				ss << prev[j] << " ";
				j = prev[j];
			}
			ss << "\n";
		}
		this->output = ss.str();
	}

	delete queue;
	delete[] dist;
	delete[] prev;
}

void Graph::spBellmanFordMatrix() {
	
	// Create an array of edges to simplify the process of relaxing
	Edge** edges_arr = new Edge*[this->edges];
	int edges_counter = 0;
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			if (adj_matrix->isEdge(i, j))
				edges_arr[edges_counter++] = new Edge(i, j, adj_matrix->getWeight(i, j));
		}
	}

	auto dist = new int[vertices];
	auto prev = new int[vertices];
	
	// Initialize dist and prev
	for (int i = 0; i < vertices; ++i) {
		dist[i] = INT_MAX;
		prev[i] = -1;
	}
	dist[source_vertex] = 0;
	prev[source_vertex] = 0;
	int u, v, weight;
	// Relax all edges 
	for (int i = 1; i <= vertices - 1; ++i) {
		for (int j = 0; j < edges; ++j) {
			u = edges_arr[j]->getStartVertex();
			v = edges_arr[j]->getEndVertex();
			weight = edges_arr[j]->getEdgeWeight();
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				prev[v] = u;
			}
		}
	}

	// Check for negative-weight cycles and delete edges
	bool negative_edges = false;
	for (int i = 0; i < edges; ++i) {
		int u = edges_arr[i]->getStartVertex();
		int v = edges_arr[i]->getEndVertex();
		int weight = edges_arr[i]->getEdgeWeight();
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			negative_edges = true;
		delete edges_arr[i];
	}

	if (manual_mode) {
		std::stringstream ss;
		ss << "Start: " << source_vertex << "\n\n";
		ss << "  END\t  DIST\t  PATH\n";
		for (int i = 0; i < vertices; ++i) {
			ss << "  " << i << "\t|  " << dist[i] << "\t|  ";
			int j = i;
			ss << j << " ";
			while (j != 0) {
				ss << prev[j] << " ";
				j = prev[j];
			}
			ss << "\n";
		}
		if (negative_edges)
			ss << "Graph containts negative cycles\n";
		this->output = ss.str();
	}

	delete[] edges_arr;
	delete[] prev;
	delete[] dist;
}

void Graph::spBellmanFordList() {

	auto dist = new int[vertices];
	auto prev = new int[vertices];
	for (int i = 0; i < vertices; ++i) {
		dist[i] = INT_MAX;
		prev[i] = -1;
	}

	dist[source_vertex] = 0;
	prev[source_vertex] = 0;
	int u, v, weight;
	// Relax all edges
	for (int i = 1; i <= vertices - 1; ++i) {
		for (int j = 0; j < vertices; ++j) {
			auto& adjacent = adj_list->getAdjacent(j);
			for (Edge& e : adjacent) {
				u = e.getStartVertex();
				v = e.getEndVertex();
				weight = e.getEdgeWeight();
				if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					prev[v] = u;
				}
			}
		}
	}
	// Check for negative-weight cycles and delete edges
	bool negative_edges = false;
	for (int i = 0; i < vertices; ++i) {
		auto& adjacent = adj_list->getAdjacent(i);
		for (Edge& e : adjacent) {
			u = e.getStartVertex();
			v = e.getEndVertex();
			weight = e.getEdgeWeight();
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				negative_edges = true;
		}
	}

	if (manual_mode) {
		std::stringstream ss;
		ss << "Start: " << source_vertex << "\n\n";
		ss << "  END\t  DIST\t  PATH\n";
		for (int i = 0; i < vertices; ++i) {
			ss << "  " << i << "\t|  " << dist[i] << "\t|  ";
			int j = i;
			ss << j << " ";
			while (j != 0) {
				ss << prev[j] << " ";
				j = prev[j];
			}
			ss << "\n";
		}
		if (negative_edges)
			ss << "Graph containts negative cycles\n";
		this->output = ss.str();
	}

	delete[] prev;
	delete[] dist;
}

void Graph::mstPrimMatrix() {
	
	auto queue = new PriorityQueue<int>;
	auto key = new int[vertices]; 
	auto parent = new int[vertices]; 
	auto included = new bool[vertices]; 

	for (int i = 0; i < vertices; ++i) {
		key[i] = INT_MAX;
		parent[i] = -1;
		included[i] = false;
	}

	queue->insert(source_vertex, 0);
	key[source_vertex] = 0;
	while (!queue->isEmpty()) {
		int u = queue->popMin();
		if (included[u] == true) 
			continue;
		included[u] = true;
		for (int i = 0; i < vertices; ++i) {
			if (adj_matrix->isEdge(u, i)) {
				int v = i;
				int weight = adj_matrix->getWeight(u,i);
				if (!included[v] && key[v] > weight) {
					key[v] = weight;
					queue->insert(v, key[v]);
					parent[v] = u;
				}
			}
		}
	}
	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		int totalMST = 0;
		ss << "Edge\t" << "Weight\n";
		for (int i = 1; i < vertices; ++i) {
			ss << "(" << parent[i] << ", " << i << ")\t" << key[i] << "\n";
			totalMST += key[i];
		}
		ss << "\nTotal edge weight: " << totalMST << "\n";
		output = ss.str();
	}

	delete queue;
	delete[] key;
	delete[] parent;
	delete[] included;
}

void Graph::mstPrimList() {

	auto queue = new PriorityQueue<int>;
	auto key = new int[vertices];			// need to initalize this to INF
	auto parent = new int[vertices];		// need to initialize this with -1
	auto included = new bool[vertices];

	for (int i = 0; i < vertices; ++i) {
		key[i] = INT_MAX;
		parent[i] = -1;
		included[i] = false;
	}

	queue->insert(source_vertex, 0);
	key[source_vertex] = 0;
	while (!queue->isEmpty()) {
		int u = queue->popMin();
		if (included[u] == true) 
			continue;
		included[u] = true;
		auto& adjacent = adj_list->getAdjacent(u);
		for (Edge& e : adjacent) {
			int v = e.getEndVertex();
			int weight = e.getEdgeWeight();
			if (!included[v] && key[v] > weight) {
				key[v] = weight;
				queue->insert(v, weight);
				parent[v] = u;
			}
		}
	}
	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		int totalMST = 0;
		ss << "Edge\t" << "Weight\n";
		for (int i = 1; i < vertices; ++i) {
			ss << "(" << parent[i] << ", " << i << ")\t" << key[i] << "\n";
			totalMST += key[i];
		}
		ss << "\nTotal edge weight: " << totalMST << "\n";
		output = ss.str();
	}

	delete queue;
	delete[] key;
	delete[] parent;
	delete[] included;
}

void Graph::mstKruskalMatrix() {

	auto queue = new PriorityQueue<Edge*>;
	auto result = new List<Edge*>;
	int u, v, weight;
	Edge* next_edge;
	// Make Sets
	DisjointSet** sets = new DisjointSet*[vertices];
	for (int i = 0; i < vertices; ++i) {
		sets[i] = new DisjointSet(i);
	}
	
	// Put all edges into the queue and sort them
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			if (i != j && adj_matrix->isEdge(i, j)) {
				weight = adj_matrix->getWeight(i, j);
				queue->insert(new Edge(i, j, weight), weight);
			}	
		}
	}
	// Main part
	for (int i = 0; i < edges; ++i) {
		next_edge = queue->popMin();
		u = next_edge->getStartVertex();
		v = next_edge->getEndVertex();
		if (find_kruskal(u, sets) != find_kruskal(v, sets)) {
			result->pushBack(next_edge);
			union_kruskal(u, v, sets);
		}
		else delete next_edge;
	}
	
	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		int totalMST = 0;
		ss << "Edge\t" << "Weight\n";
		for (Edge* e : *result) {
			ss << e->toString() << "\n";
			totalMST += e->getEdgeWeight();
			delete e;
		}
		ss << "\nTotal edge weight: " << totalMST << "\n";
		output = ss.str();
	}

	// cleanup
	for (int i = 0; i < vertices; ++i) {
		delete sets[i];
	}

	delete[] sets;
	delete queue;
	delete result;
}

void Graph::mstKruskalList() {

	auto queue = new PriorityQueue<Edge*>;
	auto result = new List<Edge*>;
	int u, v, weight;
	Edge* next_edge;
	// Make Sets
	DisjointSet** sets = new DisjointSet*[vertices];
	for (int i = 0; i < vertices; ++i) {
		sets[i] = new DisjointSet(i);
	}

	// Put all edges into the queue and sort them
	for (int i = 0; i < vertices; ++i) {
		auto& adjacent = adj_list->getAdjacent(i);
		for (Edge& e : adjacent) {
			weight = e.getEdgeWeight();
			// put (deep) copy of the edge in the queue
			next_edge = new Edge(e);
			queue->insert(next_edge, weight);
		}
	}
	
	for (int i = 0; i < edges; ++i) {
		next_edge = queue->popMin();
		u = next_edge->getStartVertex();
		v = next_edge->getEndVertex();
		if (find_kruskal(u, sets) != find_kruskal(v, sets)) {
			result->pushBack(next_edge);
			union_kruskal(u, v, sets);
		}
		else delete next_edge;
	}

	if (manual_mode) {
		// Get the results here to std::string from sstream
		// and add them to the output buffer
		std::stringstream ss;
		int totalMST = 0;
		ss << "Edge\t" << "Weight\n";
		for (Edge* e : *result) {
			ss << e->toString() << "\n";
			totalMST += e->getEdgeWeight();
			delete e;
		}
		ss << "\nTotal edge weight: " << totalMST << "\n";
		output = ss.str();
	}

	// cleanup
	for (int i = 0; i < vertices; ++i) {
		delete sets[i];
	}

	delete[] sets;
	delete queue;
	delete result;
}

void Graph::union_kruskal(int& x, int& y, DisjointSet** sets) {
	int a = find_kruskal(x,sets);
	int b = find_kruskal(y,sets);
	if (sets[a]->rank < sets[b]->rank)
		sets[a]->parent = b;
	else
		sets[b]->parent = a;

	if (sets[a]->rank = sets[b]->rank)
		sets[a]->rank += 1;
}

int Graph::find_kruskal(int& vertex, DisjointSet** sets) {
	if (sets[vertex]->parent != vertex)
		sets[vertex]->parent = find_kruskal(sets[vertex]->parent,sets);
	return sets[vertex]->parent;
}

void Graph::generateGraph(int& vertices, float& density) {
	
	// This function generates a random graph that is ready for testing 
	// Initialisation
	this->vertices = vertices;
	adj_matrix = new AdjacencyMatrix(vertices);
	adj_list = new AdjacencyList(vertices);
	std::random_device rd;
	std::mt19937 gen(rd());
	//distribution for shuffle
	dist vertex_dist(0, INT_MAX);
	//distribution for edge weights
	dist edge_dist(1, 1000);				
	//Step 1 - Generate at least 1 valid path
	//Start with random sequence of vertices
	auto queue = new Queue<int>;
	auto arr = new int[vertices];
	for (int i = 0; i < vertices; ++i)
		arr[i] = i;
	int tmp, rand1, rand2;
	// shuffle
	for (int i = 0; i < vertices * 10; ++i) {
		rand1 = vertex_dist(gen) % vertices;
		rand2 = vertex_dist(gen) % vertices;
		tmp = arr[rand1];
		arr[rand1] = arr[rand2];
		arr[rand2] = tmp;
	}
	// Enqueue the sequence
	for (int i = 0; i < vertices; ++i) {
		queue->enqueue(arr[i]);
	}
	delete[] arr;
	// Create the path
	int start, end, weight;
	start = queue->dequeue();
	source_vertex = start;
	while (!queue->isEmpty()) {
		end = queue->dequeue();
		weight = edge_dist(gen);
		adj_matrix->addEdge(start, end, weight);
		adj_list->addEdge(start, end, weight);
		start = end;
	}
	this->destination_vertex = start;
	delete queue;
	int edges = vertices - 1;
	int max_edges = vertices * (vertices - 1);
	int desired_edges = density * max_edges;
	// Step 2 - Fill the graph with random edges until desired density is met
	while (edges != desired_edges) {
		start = vertex_dist(gen) % vertices;
		end = vertex_dist(gen) % vertices;
		if (start != end && !adj_matrix->isEdge(start, end)) {
			weight = edge_dist(gen);
			adj_matrix->addEdge(start, end, weight);
			adj_list->addEdge(start, end, weight);
			++edges;
		}
	}
	this->edges = edges;
	this->status = true;
}
