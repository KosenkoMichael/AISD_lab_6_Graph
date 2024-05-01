#pragma once

#include<iostream>
#include<list>
#include<vector>
#include<exception>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>

const int INF = std::numeric_limits<int>::max();

using namespace std;

void print_for_dijkstra(vector<double> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		cout << "to " << i << " is " << vec[i] << endl;
	}
}

template<typename V, typename Distance = double>
class Graph {
private:
	struct Edge {
		int _num;
		Distance _val;
	};
	struct Vertex {
		int _num;
		V _val;
		list<Edge> _edge;
	};
	vector<Vertex> _graph;
	void dfs_h(int from, vector<int>& visited) {
		visited[from] = 1;
		for (auto& i : (*this)[from]._edge) {
			if (!visited[i._num]) {
				dfs_h(i._num, visited);
			}
		}
		cout << from << " ";
	}
	void rework_for_chill_life() {
		size_t count = 0;
		for (auto& i : _graph) {
			i._num = count;
			count++;
		}
	}
public:
	//HELP
	Graph() = default;
	void print() {
		for (auto& vertex : _graph) {
			cout << vertex._num << "-" << vertex._val;
			for (auto& edge : vertex._edge) {
				cout << "-->" << "|" << edge._num << "-" << edge._val << "|";
			}
			cout << endl;
		}
	}
	Vertex& operator[](size_t num) {
		for (auto& vertex : _graph) {
			if (vertex._num == num) {
				return vertex;
			}
		}
		throw invalid_argument("No such vertex");
	}
	size_t size() {
		return _graph.size();
	}
	vector<Vertex> vertices() const {
		return _graph;
	}
	list<Edge> edges(int from) const {
		if (has_vertex(from))
			return (*this)[from]._edge;
	}
	//VERTEX
	bool has_vertex(int num){
		try {
			(*this)[num];
		}
		catch (invalid_argument& e) {
			return false;
		}
		return true;
	}
	void add_vertex(V val) {
		int new_num = _graph.size();
		_graph.push_back({ new_num,val });
	}
	void remove_vertex(int num) {
		for (auto& vertex : _graph) {
			vertex._edge.remove_if([&](Edge& x) { return x._num == num; });
		}
		_graph.erase(std::remove_if(_graph.begin(), _graph.end(), [num](Vertex& v)
			{
				return v._num == num;
			}
		), _graph.end());
		rework_for_chill_life();
	}
	//EDGE
	void add_edge(int from, int to, Distance val) {
		try {
			(*this)[from]._edge.push_back({ to, val });
		}
		catch (invalid_argument& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	bool has_edge(int from, int to) {
		if (has_vertex(from)) {
			for (auto& edge : (*this)[from]._edge)
				if (edge._num == to)
					return true;
		}
		return false;
	}
	bool has_edge(int from, int to, Distance val) {
		if (has_vertex(from)) {
			for (auto& edge : (*this)[from]._edge)
				if (edge._num == to && edge._val == val)
					return true;
		}
		return false;
	}
	void remove_edge(int from, int to) {
		if(has_vertex(from))
			(*this)[from]._edge.remove_if([&](Edge& x) { return x._num == to; });
	}
	void remove_edge(int from, int to, Distance val) {
		if (has_vertex(from))
			(*this)[from]._edge.remove_if([&](Edge& x) { return (x._num == to && x._val == val); });
	}
	//FUNCTIONAL
	void dfs(int start_vertex){
		if (has_vertex(start_vertex)) {
			vector<int> visited(size()+1, 0);
			dfs_h(start_vertex, visited);
		}
	}
	vector<double> Dijkstra(int from) {
		vector<double> distance(size(), INF);
		distance[from] = 0;

		priority_queue<std::pair<int, int>, vector<std::pair<int, int>>,greater<>> queue;
		queue.push({ 0, from });

		while (!queue.empty()) {
			int u = queue.top().second;
			queue.pop();

			for (auto& edge: (*this)[u]._edge) {
				int v = edge._num;
				int weight = edge._val;

				if (distance[v] > distance[u] + weight) {
					distance[v] = distance[u] + weight;
					queue.push({ distance[v], v });
				}
			}
		}
		return distance;
	}
	V find_graph_center() {
		int center = -1;
		int max_dist = -1;
		for (auto& vertex: _graph) {
			vector<double> dist = Dijkstra(vertex._num);
			int max_d = *max_element(dist.begin(), dist.end());
			if (max_d < max_dist || max_dist == -1) {
				max_dist = max_d;
				center = vertex._num;
			}
		}
		return (*this)[center]._val;
	}
};