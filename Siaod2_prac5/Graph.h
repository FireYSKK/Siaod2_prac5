#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <deque>
#include <io.h>
#include <fcntl.h>
using namespace std;

class Graph {
	vector<map<int, int>> adj;
public:
	Graph(int nodes = 1);

	void addNode();

	void addDirectedEdge(int start, int end, int weight = 1);
	void addUndirectedEdge(int first, int second, int weight = 1);

	void printTable();
	void plotDirected();
	void plotUndirected();

	void FindEulerLoop();
	void euler(int, vector<map<int, int>>*);

	Graph* buildSpanningTree();
	void DFSspanningTree(Graph*, int);
};

#endif