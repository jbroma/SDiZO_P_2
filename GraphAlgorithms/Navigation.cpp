#pragma once
#include "stdafx.h"
#include "Navigation.h"

int sizeMenu() {
	int menu_choice = menu(MENU_X, MENU_Y, "Select number of vertices", 5, "500", "1\t000", "2\t000", "4\t000","8\t000");
	return (int) 500 * pow(2, menu_choice - 1);
}

float densityMenu() {
	int menu_choice = menu(MENU_X, MENU_Y, "Select density of a graph", 4, "25%", "50%", "75%", "99%");
	switch (menu_choice) {
	case 1: return 0.25f;
	case 2: return 0.5f;
	case 3: return 0.75f;
	case 4: return 0.99f;
	}
	return 0;
}

alg_pt algorithmsMenu() {
	// This should return a pointer to a graph function that should be run;
	int structure_choice = menu(MENU_X, MENU_Y, "Select method of representation", 2, "Adjacency Matrix", "Adjacency List");
	system("cls");
	int algorithm_choice = menu(MENU_X, MENU_Y, "Select an algorithm to run", 6, "SP - Dijkstra", "SP - Bellman-Ford", "MST - Prim", "MST - Kruskal", "MF - Ford-Fulkerson (BFS)", "MF - Ford-Fulkerson (DFS)");
	system("cls");
	if (structure_choice == 2)
		algorithm_choice += 6;
	switch (algorithm_choice) {
	case 1:		return sp_d_m;
	case 2:		return sp_bf_m;
	case 3:		return mst_p_m;
	case 4:		return mst_k_m;
	case 5:		return mf_bfs_m;
	case 6:		return mf_dfs_m;
	case 7:		return sp_d_l;
	case 8:		return sp_bf_l;
	case 9:		return mst_p_l;
	case 10:	return mst_k_l;
	case 11:	return mf_bfs_l;
	case 12:	return mf_dfs_l;
	}
	std::cin.sync();
}

void manualMenu() {
	Sleep(100);
	std::string file_path = inputPrompt("Enter path of a file with graph");
	
	Graph * graph = new Graph();
	graph->setManualMode(true);
	graph->setSourceFilePath(file_path);
	graph->loadGraphFromFile(file_path);
	// Graph is loaded and ready for testing
	while (graph->getStatus()) {
		int menu_choice = menu(MENU_X, MENU_Y, "General Menu", 4, "Run algorithms", "Modify structure", "View Graph", "Return");
		switch (menu_choice) {
		case 1: manualTest(graph); break;
		case 2: break;						// Unimplemented modificationMenu
		case 3: viewMenu(graph); break;
		case 4: delete graph; return;
		}
	}
	delete graph;
}

void manualTest(Graph* graph) {
	// Select an algorithm to run
	alg_pt algorithm = algorithmsMenu();
	// If we want to run Prim's Algorithm, first we must convert the graph to an undirected one
	if (!graph->getUndirected() && algorithm == mst_p_l || algorithm == mst_p_m )
		graph->setUndirected();
	// If we want to run other algortihms, we reload the graph, to get it's directed form
	if (graph->getUndirected() && !(algorithm == mst_p_l || algorithm == mst_p_m)) {
		std::string file_path = graph->getSourceFilePath();
		delete graph;
		graph = new Graph();
		graph->setManualMode(true);
		graph->setSourceFilePath(file_path);
		graph->loadGraphFromFile(file_path);
	}

	// Run the algorithm
	(graph->*algorithm)();
	if (graph->getUndirected())
		std::cout << "Graph was converted to an undirected graph !!!\n\n";
	std::cout << graph->getAlgorithmOutput() << "\n\n";
	system("Pause");
	system("cls");
	return;
}

void viewMenu(Graph* g) {
	// This function displays a graph in list/matrix form (selected by the user) and then returns to the manualMenu
	while (true) {
		int menu_choice = menu(MENU_X, MENU_Y, "Select representation of a graph", 3, "Adjacency Matrix", "Adjacency List", "Return");
		system("cls");
		switch (menu_choice) {
		case 1: {
			std::cout << "Adjacency Matrix of the graph:\n" << g->MatrixToString();
			system("pause");
			break;
		}
		case 2: {
			std::cout << "Adjacency List of the graph:\n" << g->ListToString();
			system("pause");
			break;
		}
		case 3: return;
		}
	}
	return;
}

void modificationMenu(Graph* g) {
	// THIS FUNCTION IS OF A SECONDARY PRIORITY
	// This function should allow for modification of vertices, edges etc.
}

void performTimeTest() {
	// This function should perform a test on a graph using selected algorithm and then display/save test data
	typedef std::chrono::high_resolution_clock clock;
	clock::time_point start_time, end_time;
	std::chrono::duration<double, std::nano> duration;
	double * results;
	int ammount = 100;
	Graph * graph;
	
	// Get test parameters - algorithm + representation, size, density
	alg_pt algorithm = algorithmsMenu();
	int size = sizeMenu();
	int density = densityMenu();
	system("cls");
	// Test Starts here
	gotoXY(0, 0);
	printf("Performing a test...");
	results = new double[ammount]();
	for (int i = 0; i < ammount; ++i)
	{
		// Display progress
		gotoXY(0, 1);
		printf("%02d %%", (i * 100 / ammount));

		// Generate a random graph
		graph = generateGraph(size, density);
		// Perform a test and add 
		start_time = clock::now();
		(*graph.*algorithm)();
		end_time = clock::now();
		duration = end_time - start_time;
		results[i] += duration.count();
		delete graph;
	}
	/*results[i] = results[i] / op_count;
	delete container_pt;*/
	
	delete[] results;
}

Graph* generateGraph(int vertices, float density) {
	// This function should generate a random graph that is ready for testing 
	std::random_device rd;
	std::mt19937 gen(rd());
	dist edge_dist(1,INT_MAX - 1);	//distribution for edge weights
	Graph* g = new Graph();
	// Step 1 - generate at least 1 valid path
	return g;
}
