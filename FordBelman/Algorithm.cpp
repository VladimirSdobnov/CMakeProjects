#include <iostream>
#include <limits.h>
#include "TVector.h"
#include "Header.h"
#include "../List/list.h"

void bellmanFord(TVector<int>& distance, TVector<int>& up, TVector<Edge>& graph, int vertices,
	int source) {
	// Заполняем расстояния от старта до вершин INFINITE
	for (int i = 0; i < vertices; i++) {
		distance[i] = INT_MAX;
		up[i] = -1; // Нет предшественника для каждой вершины
	}
	distance[source] = 0; // Расстояние от старта до старта 0

	// Проходим через все ребра |V| - 1 раз
	for (int i = 0; i < vertices - 1; ++i) {
		// Повторяем для каждого ребра
		for (const Edge& e : graph) {
			// Обнавляем расстояние, если найдем более короткий путь
			if (distance[e.source] != INT_MAX
				&& distance[e.source] + e.weight < distance[e.destination]) {
				distance[e.destination] = distance[e.source] + e.weight;
				up[e.destination] = e.source; // Устанавливаем предшественника
			}
		}
	}

	// Проверяем на наличие отрицательных циклов
	for (const Edge& e : graph) {
		if (distance[e.source] != INT_MAX
			&& distance[e.source] + e.weight
			< distance[e.destination]) {
			std::cout
				<< "Graph contains negative weight cycle\n";
			return;
		}
	}
}

// Функция, реализующая алгоритм Дейкстры
void dijcstra_mark(TVector<int>& distance, TVector<int>& up, TVector<TList<Edge>>& ADJ, int vertices, int source) {
	TVector<int> mark(vertices);          // Массив для маркировки посещенных вершин
	for (int i = 0; i < vertices; i++) {
		distance[i] = INT_MAX;
		up[i] = -1;
		mark[i] = 0;
	}
	int nq = vertices;

	distance[source] = 0; // Расстояние до стартовой вершины равно 0

	// Основной цикл алгоритма
	while (nq > 0) {
		int c = 0;

		// Находим непосещенную вершину с минимальным расстоянием
		while (mark[c] != 0) {
			c = c + 1;
		}
		int i = c;
		for (int k = c; k < vertices; ++k) {
			if (mark[k] == 0 && distance[i] > distance[k]) {
				i = k;
			}
		}

		// Отметим вершину как посещенную
		mark[i] = 1;
		nq -= 1;

		// Обрабатываем все рёбра, исходящие из вершины i
		for (auto Node : ADJ[i]) {
			Edge edge = Node.data();
			int j = edge.destination;  // Вершина назначения
			if (mark[j] == 0) { // Если вершина еще не посещена
				if (distance[j] > distance[i] + edge.weight) { // Если найдено более короткое расстояние
					distance[j] = distance[i] + edge.weight;
					up[j] = i; // Запоминаем предшествующую вершину
				}
			}
		}
	}
}

int main() {
	// Пример использования:
	int n = 5; // Количество вершин в графе
	int s = 0; // Стартовая вершина
	TVector<int> distance(n);
	TVector<int> up(n);
	TVector<int> distance2(n);
	TVector<int> up2(n);

	// Граф: список рёбер
	TVector<TList<Edge>> ADJ(n); // Граф с n вершинами
	TVector<Edge> graph;
	graph.append(Edge({ 0, 1, 10 }));
	graph.append(Edge({ 0, 2, 5 }));
	graph.append(Edge({ 1, 2, 2 }));
	graph.append(Edge({ 1, 3, 1 }));
	graph.append(Edge({ 2, 3, 9 }));
	graph.append(Edge({ 3, 4, 4 }));

	// Добавление рёбер в граф
	TList<Edge> list1;
	list1.push_back(Edge({ 0, 1, 10 }));
	list1.push_back(Edge({ 0, 2, 5 }));
	ADJ.append(list1);

	TList<Edge> list2;
	list2.push_back(Edge({ 1, 2, 2 }));
	list2.push_back(Edge({ 1, 3, 1 }));
	ADJ.append(list2);

	TList<Edge> list3;
	list3.push_back(Edge({ 2, 3, 9 }));
	ADJ.append(list3);

	TList<Edge> list4;
	list4.push_back(Edge({ 3, 4, 4 }));
	ADJ.append(list4);

	// Запуск алгоритма Дейкстры
	dijcstra_mark(distance, up, ADJ, n, s);
	bellmanFord(distance2, up2, graph, n, s);


	// Вывод результатов
	std::cout << "Shortest distances from vertex " << s << ":\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "Distance to vertex " << i << " = " << distance2[i] << "\n";
	}

	std::cout << "\nPredecessor vertices:\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "Predecessor of vertex " << i << " = " << up2[i] << "\n";
	}

	// Вывод результатов
	std::cout << "Shortest distances from vertex " << s << ":\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "Distance to vertex " << i << " = " << distance[i] << "\n";
	}

	std::cout << "\nPredecessor vertices:\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "Predecessor of vertex " << i << " = " << up[i] << "\n";
	}

	

	return 0;
}
