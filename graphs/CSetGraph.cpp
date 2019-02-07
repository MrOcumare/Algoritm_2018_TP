//
// Created by Mr.Ocumare on 17.12.2018.
//

#include "CSetGraph.h"

bool SetGraph::isValidIndex(int index) const {
    return 0 <= index && index < set_graph.size();
}

SetGraph::SetGraph(const IGraph& graph)
{
    set_graph.resize(graph.VerticesCount());
    for( int from = 0; from < set_graph.size(); from++ )
        for ( int vertices : graph.GetNextVertices(from) ) {
            set_graph[from].insert(vertices);
        }
}


void SetGraph::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
    if (!(std::find( set_graph[from].begin(),  set_graph[from].end(), to) !=  set_graph[from].end())) {
        set_graph[from].insert(to);
    }
    //adjacency_list[to].push_back(from);
}


std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> next_vertices;
    std::copy(set_graph[vertex].begin(), set_graph[vertex].end(), std::back_inserter(next_vertices));
    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> prev_vertices;
    for( int from = 0; from < set_graph.size(); from++ )
        for( int i : set_graph[from])
            if( i == vertex )
                prev_vertices.push_back(from);
    return prev_vertices;
}
