#include <gtest/gtest.h>
#include <functions/functions.h>

using namespace std;

TEST(graph_test, test) {
	Graph<string> graph;
	
	graph.add_vertex("one");
	graph.add_vertex("two");
	graph.add_vertex("three");
	graph.add_vertex("four");
	graph.add_vertex("five");
	graph.add_vertex("six");


	graph.add_edge(0,3,99);
	graph.add_edge(1,2,99);
	graph.add_edge(1, 3, 99);
	graph.add_edge(2, 4, 99);
	graph.add_edge(4, 0, 99);
	graph.add_edge(4, 3, 99);
	graph.add_edge(5, 1, 2);
	graph.add_edge(5, 2, 2);
	graph.add_edge(5, 3, 2);
	graph.add_edge(5, 4, 2);

	graph.print();

	cout << graph.find_graph_center()<<endl;
	print_for_dijkstra((graph.Dijkstra(5)));

}

TEST(functional_test, test) {

}