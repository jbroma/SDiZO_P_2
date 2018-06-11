#pragma once
#include "ConsoleNav.h"
#include "Graph.h"
#include <string>
#include <chrono>
#include <random>

// Custom type definitions
typedef void (Graph::*alg_pt)();

typedef std::uniform_int_distribution<> dist;

// Pointers to specific algorithms of a graph
const alg_pt sp_d_m		=	&Graph::spDijkstraMatrix;
const alg_pt sp_d_l		=	&Graph::spDijkstraList;
const alg_pt sp_bf_m	=	&Graph::spBellmanFordMatrix;
const alg_pt sp_bf_l	=	&Graph::spBellmanFordList;
const alg_pt mst_p_m	=	&Graph::mstPrimMatrix;
const alg_pt mst_p_l	=	&Graph::mstPrimList;
const alg_pt mst_k_m	=	&Graph::mstKruskalMatrix;
const alg_pt mst_k_l	=	&Graph::mstKruskalList;
const alg_pt mf_bfs_m	=	&Graph::mfBFSMatrix;
const alg_pt mf_bfs_l	=	&Graph::mfBFSList;
const alg_pt mf_dfs_m	=	&Graph::mfDFSMatrix;
const alg_pt mf_dfs_l	=	&Graph::mfDFSList;

// --------------------------------------------
//				Menu functions
// --------------------------------------------

void manualMenu();

// Common menus
alg_pt algorithmsMenu();

// Manual menus
void manualTest(Graph* g);
void modificationMenu(Graph* g);
void viewMenu(Graph* g);

// Test menus
int sizeMenu();
float densityMenu();
void performTimeTest();
Graph* generateGraph(int vertices, float density);
std::string generateResults(int& results);
