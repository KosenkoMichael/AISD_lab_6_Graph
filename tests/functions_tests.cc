#include <gtest/gtest.h>
#include <functions/functions.h>

using namespace std;

void process(string S) {
	cout << S.length() << " ";
}

TEST(graph_test, test) {
	Graph<string> graph;

	graph.add_vertex("one");
	graph.add_vertex("two");
	graph.add_vertex("three");

	graph.add_edge("one", "two", 100);
	graph.add_edge("two", "three", 200);
	graph.add_edge("three", "one", 300);
	graph.add_edge("three", "one", 10);

	graph.print();
	cout << endl;

	cout <<"graph.has_edge(\"one\", \"two\") " << boolalpha << graph.has_edge("one", "two") << endl;
	cout << "graph.has_edge(\"one\", \"three\") " << boolalpha << graph.has_edge("one", "three") << endl;
	cout << "graph.has_edge(\"one\", \"two\", 100) " << boolalpha << graph.has_edge("one", "two", 100) << endl;
	cout << "graph.has_edge(\"one\", \"two\", 200) " << boolalpha << graph.has_edge("one", "two", 200) << endl;
	cout << "graph.has_vertex(\"one\") " << boolalpha << graph.has_vertex("one") << endl;
	cout << "graph.has_vertex(\"five\") " << boolalpha << graph.has_vertex("five") << endl;
	cout << endl;

	graph.remove_edge("three", "one", 10);
	graph.remove_vertex("three");

	graph.print();
}

TEST(Dijkstra_test, test) {
	Graph<int> graph;
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_vertex(4);

	graph.add_edge(1,2,999);
	graph.add_edge(1,3,10);
	graph.add_edge(3,2,10);
	graph.add_edge(1,4,999);
	graph.add_edge(2,4,10);

	graph.print();
	cout << endl;
	graph.Dijkstra(1, true);

	cout << endl;
	cout << "graph.degree(1) " << graph.degree(1);
}

TEST(functional_test, test) {
	Graph<string> graph;

	graph.add_vertex("one");
	graph.add_vertex("two");
	graph.add_vertex("three");
	graph.add_vertex("four");

	graph.add_edge("four", "one", 10);
	graph.add_edge("four", "two", 15);
	graph.add_edge("four", "three", 20);
	graph.add_edge("one", "two", 100);
	graph.add_edge("three", "two", 200);

	graph.print();
	cout << endl;

	graph.dfs("four");
	cout << endl;

	cout << "graph.find_graph_center() " << graph.find_graph_center();
	cout << endl;

	graph.dfs("four");
	cout << endl;
	graph.process_dfs("four", process);
}