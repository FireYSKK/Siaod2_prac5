// A simple representation of graph using STL
#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	int n, start, end, weight;
	wchar_t isDirected;
	wcout << "Enter the number of nodes: ";
	wcin >> n;
	Graph graph(n + 1);
	wcout << "Directed (D) or Undirected (U): ";
	wcin >> isDirected;

	if (isDirected == L'D') {
		wcout << "Enter edges: start | end | weight. End condition - '0' in any field" << endl;
		do {
			wcin >> start;
			if (start == 0) break;
			wcin >> end;
			if (end == 0) break;
			wcin >> weight;
			if (weight == 0) break;
			graph.addDirectedEdge(start, end, weight);
		} while (start && end && weight);

		wcout << "Graph's adjacency list: " << endl;
		graph.printTable();
		wcout << "The drawing:" << endl;
		graph.plotDirected();
		wcout << endl;

	}
	else if (isDirected == L'U') {
		wcout << "Enter edges: first | second | weight. 0 in any field is end condition" << endl;
		do {
			wcin >> start;
			if (start == 0) break;
			wcin >> end;
			if (end == 0) break;
			wcin >> weight;
			if (weight == 0) break;
			graph.addUndirectedEdge(start, end, weight);
		} while (start && end && weight);

		wcout << "Graph's adjacency list: " << endl;
		graph.printTable();
		wcout << "The drawing:" << endl;
		graph.plotUndirected();
		wcout << endl;

		if (isDirected == L'U') {
			graph.FindEulerLoop();
			wcout << endl << "--Spanning Tree with DFS--" << endl;
			Graph* ST = graph.buildSpanningTree();
			wcout << "Spanning tree's adjacency list: " << endl;
			ST->printTable();
			wcout << "The drawing: " << endl;
			ST->plotUndirected();
		}
	}
	else {
		wcout << "Wrong input! No graph for you :P" << endl;
	}

    return 0;
}





/*graph.addDirectedEdge(1, 2);
graph.addDirectedEdge(1, 4);
graph.addDirectedEdge(2, 3);
graph.addDirectedEdge(2, 5);
graph.addDirectedEdge(3, 5);
graph.addDirectedEdge(4, 5);
graph.addDirectedEdge(5, 2);
graph.addDirectedEdge(5, 1);
graph.addDirectedEdge(4, 1);
graph.addUndirectedEdge(4, 6);
graph.addUndirectedEdge(5, 7);
graph.addUndirectedEdge(5, 6);*/

/*for (int i = 0; i < 4; i++)
	graph.addNode();

graph.addDirectedEdge(1, 2);
graph.addDirectedEdge(2, 3);
graph.addDirectedEdge(3, 1);*/