#include "Graph.h"

int shift(int value) {
	return 3 * (value - 1);
}

Graph::Graph(int nodes) {
	for (int i = 0; i < nodes; i++)
		addNode();
}

void Graph::addNode() {
	map<int, int> node_adj;
	adj.push_back(node_adj);
}

void Graph::addDirectedEdge(int start, int end, int weight) {
	try {
		adj[start].insert({ end, weight });
	}
	catch (...) {
		wcout << "Something went wrong" << endl;
	}
}

void Graph::addUndirectedEdge(int first, int second, int weight) {
	try {
		adj[first].insert({ second, weight });
		adj[second].insert({ first, weight });
	}
	catch (...) {
		wcout << "Something went wrong" << endl;
	}
}

void Graph::printTable() {
	for (int i = 1; i < adj.size(); i++) {
		wcout << i;
		for (map<int, int>::const_iterator iter = adj[i].begin(); iter != adj[i].end(); iter++) {
			wcout << " -> " << iter->first;
		}
		wcout << endl;
	}
}

void Graph::plotDirected() {

	int width = adj.size();
	int line_length = shift(width) - 1, line_height = shift(width) - 2;

	// Матрица для вывода
	wchar_t* plot = new wchar_t[line_length * line_height];
	for (int i = 0; i < line_height; i++) {
		for (int j = 0; j < line_length; j++) {
			// Заполнение пробелами
			plot[i * line_length + j] = L' ';
		}
	}

	int node_last = -1;
	deque<int> right_adj, left_adj;

	for (int node = 1; node < width; node++) {
		// Запись чисел в матрицу
		if (node < 10) {
			plot[shift(node) * line_length + shift(node)] = (wchar_t)node + L'0';
		}
		else {
			plot[shift(node) * line_length + shift(node)] = (wchar_t) (node / 10) + L'0';
			plot[shift(node) * line_length + shift(node) + 1] = (wchar_t) (node % 10) + L'0';
		}

		// Формирование двух очередей для текущего узла
		// 1. С большими номерами
		// 2. С меньшими номерами
		// Для каждой очереди пути будут отрисовываться в разные стороны
		for (map<int, int>::const_iterator iter = adj[node].begin(); iter != adj[node].end(); iter++) {
			if (node < iter->first) {
				right_adj.push_back(iter->first);
			}
			else {
				left_adj.push_back(iter->first);
			}
		}

		// Пути к узлам с большими номерами

		if (!right_adj.empty()) {
			// Последний связанный узел
			node_last = shift(right_adj.back());
			// Прямой проход
			for (int i = shift(node) + 2; i < node_last; i++) {
				// Если текущий узел связан с узлом, находящимся под чертой
				if (i == shift(right_adj.front())) {
					plot[shift(node) * line_length + i] = (plot[shift(node) * line_length + i] == L'│') ? L'┼' : L'┬';

					// Отрисовка вертикальной черты
					for (int j = shift(node) + 1; j < i - 1; j++) {
						if (plot[j * line_length + i] == L' ') plot[j * line_length + i] = L'│';
					}
					if (plot[(i - 1) * line_length + i] == L' ') 
						plot[(i - 1) * line_length + i] = L'↓';

					right_adj.pop_front();
				}
				// Отрисовка горизонтальной черты
				else {
					plot[shift(node) * line_length + i] = L'─';
				}
			}
			// Для последнего связанного узла отдельные символы
			plot[shift(node) * line_length + node_last] = (plot[shift(node) * line_length + node_last] == L'│') ? L'┤' : L'┐';
			for (int j = shift(node) + 1; j < node_last - 1; j++) {
				if (plot[j * line_length + node_last] == L' ') plot[j * line_length + node_last] = L'│';
			}
			if (plot[(node_last - 1) * line_length + node_last] == L' ') 
				plot[(node_last - 1) * line_length + node_last] = L'↓';

			right_adj.pop_front();
		}

		// Пути к узлам с меньшими номерами

		if (!left_adj.empty()) {
			// Последний связанный узел
			node_last = shift(left_adj.front());
			// Проход в обратную сторону
			for (int i = shift(node) - 1; i > node_last; i--) {
				// Если текущий узел связан с узлом, находящимся над чертой
				if (i == shift(left_adj.back())) {
					plot[shift(node) * line_length + i] = (plot[shift(node) * line_length + i] == L'│') ? L'┼' : L'┴';

					// Отрисовка вертикальной черты
					for (int j = shift(node) - 1; j > i + 1; j--) {
						if (plot[j * line_length + i] == L' ') plot[j * line_length + i] = L'│';
					}
					if (plot[(i + 1) * line_length + i] == L' ') 
						plot[(i + 1) * line_length + i] = L'↑';

					left_adj.pop_back();
				}
				// Отрисовка горизонтальной черты
				else {
					plot[shift(node) * line_length + i] = L'─';
				}
			}
			// Для последнего связанного узла отдельные символы
			plot[shift(node) * line_length + node_last] = L'└';
			for (int j = shift(node) - 1; j > node_last + 1; j--) {
				if (plot[j * line_length + node_last] == L' ') plot[j * line_length + node_last] = L'│';
				if (plot[j * line_length + node_last] == L'└') plot[j * line_length + node_last] = L'├';
			}
			if (plot[(node_last + 1) * line_length + node_last] == L' ') 
				plot[(node_last + 1) * line_length + node_last] = L'↑';

			left_adj.pop_back();

		}
		
	}

	for (int i = 0; i < line_height; i++) {
		for (int j = 0; j < line_length; j++) {
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << plot[i * line_length + j];
		}
		wcout << endl;
	}
}

void Graph::plotUndirected() {

	int width = adj.size();
	int line_length = shift(width) - 1, line_height = shift(width) - 2;

	// Матрица для вывода
	wchar_t* plot = new wchar_t[line_length * line_height];
	for (int i = 0; i < line_height; i++) {
		for (int j = 0; j < line_length; j++) {
			// Заполнение пробелами
			plot[i * line_length + j] = L' ';
		}
	}

	int node_last = -1;
	deque<int> node_adj;

	for (int node = 1; node < width; node++) {
		// Запись чисел в матрицу
		if (node < 10) {
			plot[shift(node) * line_length + shift(node)] = (wchar_t)node + L'0';
		}
		else {
			plot[shift(node) * line_length + shift(node)] = (wchar_t)(node / 10) + L'0';
			plot[shift(node) * line_length + shift(node) + 1] = (wchar_t)(node % 10) + L'0';
		}
		// Для неор графа достаточно 1 очереди
		for (map<int, int>::const_iterator iter = adj[node].begin(); iter != adj[node].end(); iter++) {
			if (iter->first > node)
				node_adj.push_back(iter->first);
		}

		// Пути к узлам

		if (!node_adj.empty()) {
			// Последний связанный узел
			node_last = shift(node_adj.back());
			// Прямой проход
			for (int i = shift(node) + 2; i < node_last; i++) {
				// Если текущий узел связан с узлом, находящимся под чертой
				if (i == shift(node_adj.front())) {
					plot[shift(node) * line_length + i] = (plot[shift(node) * line_length + i] == L'│') ? L'┼' : L'┬';

					// Отрисовка вертикальной черты
					for (int j = shift(node) + 1; j < i; j++) {
						if (plot[j * line_length + i] == L' ') plot[j * line_length + i] = L'│';
					}

					node_adj.pop_front();
				}
				// Отрисовка горизонтальной черты
				else {
					plot[shift(node) * line_length + i] = L'─';
				}
			}
			// Для последнего связанного узла отдельные символы
			plot[shift(node) * line_length + node_last] = (plot[shift(node) * line_length + node_last] == L'│') ? L'┤' : L'┐';
			for (int j = shift(node) + 1; j < node_last; j++) {
				if (plot[j * line_length + node_last] == L' ') plot[j * line_length + node_last] = L'│';
			}

			node_adj.pop_front();
		}

	}

	for (int i = 0; i < line_height; i++) {
		for (int j = 0; j < line_length; j++) {
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << plot[i * line_length + j];
		}
		wcout << endl;
	}
}

void Graph::FindEulerLoop() {
	/*int* vertex_weight = new int[adj.size()] { 0 };
	for (int i = 0; i < adj.size(); i++) {
		for (map<int, int>::const_iterator iter = adj[i].begin(); iter != adj[i].end(); iter++) {
			vertex_weight[iter->first]--;
			vertex_weight[i]++;
		}
	}*/
	for (int i = 0; i < adj.size(); i++) {
		if (adj[i].size() % 2 != 0) {
			wcout << "Graph doesn't have Euler's loop" << endl;
			return;
		}
	}
	vector<map<int, int>> copy(adj);
	wcout << "Graph's Euler's loop: " << endl;
	euler(1, &copy );
	wcout << endl;
}

void Graph::euler(int v, vector<map<int, int>> *g) {
	while (!(*g)[v].empty()) {
		map<int, int>::iterator u = (*g)[v].begin(); // берем любое ребро
		int next = u->first;
		(*g)[v].erase(u);			// удаляем его
		(*g)[next].erase(v);
		euler(next, g);            // запускаемся от противоположного конца
	}
	wcout << v << " ";     // выписываем текущую вершину
}

Graph* Graph::buildSpanningTree() {
	Graph* spanningTree = new Graph(adj.size());
	DFSspanningTree(spanningTree, 1);
	return spanningTree;
}

void Graph::DFSspanningTree(Graph* g, int next) {
	/*wcout << "-------------------" << endl;
	wcout << "Call for > " << next << endl;
	g->printTable();
	wcout << "-------------------" << endl;*/
	for (auto iter = adj[next].begin(); iter != adj[next].end(); iter++) {
		if ((g->adj)[iter->first].empty()) {
			g->addUndirectedEdge(next, iter->first, iter->second);
			//wcout << "Added " << next << " " << iter->first << endl;
			DFSspanningTree(g, iter->first);
		}
	}
}