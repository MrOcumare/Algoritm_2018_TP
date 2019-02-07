//
// Created by Mr.Ocumare on 21.12.2018.
//
#include "Generator.h"

int Generator::GetRand(int size, int pos) {
    int res = rand() % (size + 1);
    if ( res != pos ) return res;
    else return GetRand(size, pos);
}

Generator::Generator(int size, int links) {
    assert(links <= size*size);
    buffer_list_graph.resize(static_cast<unsigned long>(size));
    int i = 0,
            new_link = 0;
    while (links > 0) {
        if (i == size) i = 0;
        new_link = GetRand(size, i);
        if (!(std::find( buffer_list_graph[i].begin(),  buffer_list_graph[i].end(), new_link) !=  buffer_list_graph[i].end())) {
            buffer_list_graph[i].push_back(new_link);
            links--;
            i++;
        }

    }

}


bool Generator::isValidIndex(int index) const {
    return 0 <= index && index < buffer_list_graph.size();
}

Generator::Generator(const IGraph& graph)
{
    buffer_list_graph.resize(graph.VerticesCount());
    for( int from = 0; from < buffer_list_graph.size(); from++ )
        for ( int vertices : graph.GetNextVertices(from) ){
            buffer_list_graph[from].push_back(vertices);
        }
}

void Generator::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
    buffer_list_graph[from].push_back(to);
    //adjacency_list[to].push_back(from);
}


std::vector<int> Generator::GetNextVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> next_vertices;
    std::copy(buffer_list_graph[vertex].begin(), buffer_list_graph[vertex].end(), std::back_inserter(next_vertices));
    return next_vertices;
}

std::vector<int> Generator::GetPrevVertices(int vertex) const
{
    assert(isValidIndex(vertex));
    std::vector<int> prev_vertices;
    for( int from = 0; from < buffer_list_graph.size(); from++ )
        for( int i : buffer_list_graph[from])
            if( i == vertex )
                prev_vertices.push_back(from);
    return prev_vertices;
}
