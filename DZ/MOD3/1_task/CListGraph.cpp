#include "CListGraph.hpp"

bool ListGraph::isValidIndex(int index) const {
    return 0 <= index && index < adjacency_list.size();
}

ListGraph::ListGraph(const IGraph& graph)
{
    adjacency_list.resize(graph.VerticesCount());
    for( int from = 0; from < adjacency_list.size(); from++ )
        for ( int vertices : graph.GetNextVertices(from) ){
            adjacency_list[from].push_back(vertices);
        }
}


void ListGraph::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
    adjacency_list[from].push_back(to);
    adjacency_list[to].push_back(from);
}


std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    assert(isValidIndex(vertex));


    std::vector<int> next_vertices;
    std::copy(adjacency_list[vertex].begin(), adjacency_list[vertex].end(), std::back_inserter(next_vertices));
    return next_vertices;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> prev_vertices;
    for( int from = 0; from < adjacency_list.size(); from++ )
        for( int i = 0; i < adjacency_list[from].size(); i++ )
            if( adjacency_list[from][i] == vertex )
                prev_vertices.push_back(from);
    return prev_vertices;
}
