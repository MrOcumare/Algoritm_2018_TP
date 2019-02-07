#include <iostream>

#include "CListGraph.hpp"


int main() {
    ListGraph list_graph(5);
    list_graph.AddEdge(0, 1);
    list_graph.AddEdge(0, 2);
    list_graph.AddEdge(1, 3);
    list_graph.AddEdge(2, 4);
    list_graph.AddEdge(3, 4);

    std::cout << list_graph << "\n";


    return 0;
}