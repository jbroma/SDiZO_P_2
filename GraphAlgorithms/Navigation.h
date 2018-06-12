#pragma once
#pragma warning(disable : 4996)

#include "ConsoleNav.h"
#include "Graph.h"
#include <string>
#include <chrono>
#include <ctime>

// Custom type definitions
typedef void (Graph::*alg_pt)();
typedef std::chrono::system_clock sys_clock;

// Pointers to specific algorithms of a graph
static const alg_pt sp_d_m		=	&Graph::spDijkstraMatrix;
static const alg_pt sp_d_l		=	&Graph::spDijkstraList;
static const alg_pt sp_bf_m		=	&Graph::spBellmanFordMatrix;
static const alg_pt sp_bf_l		=	&Graph::spBellmanFordList;
static const alg_pt mst_p_m		=	&Graph::mstPrimMatrix;
static const alg_pt mst_p_l		=	&Graph::mstPrimList;
static const alg_pt mst_k_m		=	&Graph::mstKruskalMatrix;
static const alg_pt mst_k_l		=	&Graph::mstKruskalList;
static const alg_pt mf_bfs_m	=	&Graph::mfBFSMatrix;
static const alg_pt mf_bfs_l	=	&Graph::mfBFSList;
static const alg_pt mf_dfs_m	=	&Graph::mfDFSMatrix;
static const alg_pt mf_dfs_l	=	&Graph::mfDFSList;

struct Algorithms {
	alg_pt pt;
	std::string container_name;
	std::string algorithm_name;
	Algorithms(alg_pt pt, std::string cn, std::string an) : pt(pt), container_name(cn), algorithm_name(an) {};
};
// --------------------------------------------
//				Menu functions
// --------------------------------------------

void manualMenu();

// Common menus
Algorithms algorithmsMenu();

// Manual menus
void manualTest(Graph* g);
void modificationMenu(Graph* g);
void viewMenu(Graph* g);

// Test menus
int sizeMenu();
float densityMenu();
void performTimeTest();
std::string generateResults(double* results, int& ammount, Algorithms& algorithm, int& size, float& density);
void saveResultsToFile(std::string& results, std::string& time_stamp, Algorithms& algorithm, int& size, float& density);
