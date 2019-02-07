//
// Created by Mr.Ocumare on 17.12.2018.
//


#include "CMatrixGraph.h"

bool MatrixGraph::isValidIndex(int index) const {
    return 0 <= index && index < adjacency_matrix.size();
}

MatrixGraph::MatrixGraph(const IGraph& graph)
{

    std::vector< std::vector<int> > buff_matrix_graph (graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++ )
        for (int j =0 ; j <  graph.VerticesCount(); j++)
            buff_matrix_graph[i].push_back(0);

    for( int from = 0; from < buff_matrix_graph.size(); from++ ) {
        for ( int vertices : graph.GetNextVertices(from)) {
            buff_matrix_graph[from][vertices]  = 1;
        }
    }


    adjacency_matrix = std::move(buff_matrix_graph);


}


void MatrixGraph::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
    if (!(std::find( adjacency_matrix[from].begin(),  adjacency_matrix[from].end(), to) !=  adjacency_matrix[from].end())) {
        adjacency_matrix[from][to] = 1;
    }

}


std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    assert(isValidIndex(vertex));

    std::vector<int> next_vertices;
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        if (adjacency_matrix[vertex][i] == 1) {
            next_vertices.push_back(i);
        }

    }
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> prev_vertices;
    for( int from = 0; from < adjacency_matrix.size(); from++ )
        if (adjacency_matrix[from][vertex] == 1)
            prev_vertices.push_back(from);
    return prev_vertices;
}
