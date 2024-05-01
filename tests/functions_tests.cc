#include <gtest/gtest.h>
#include <functions/functions.h>
#include <string>

using namespace std;

TEST(graph_test, test) {
	Graph<int> graph;
	
	graph.add_vertex(2, 1);
	graph.add_vertex(3, 1);
	graph.add_vertex(4, 1);

	graph.add_edge(2,3,1);
	graph.add_edge(3,4,2);

	graph.print();

}

TEST(functional_test, test) {

}