//
// Created by Mr.Ocumare on 18.12.2018.
//

#include <cassert>
#include "CArcGraph.h"


ArcGraph::ArcGraph(const IGraph &other) : number_of_vertices(other.VerticesCount()){
    for (int i = 0; i <  (int)number_of_vertices; i++){
        for(int vertice : other.GetNextVertices(i)){
            link_array.push_back({i, vertice});
        }
    }
};

// Добавление ребра от from к to.
void ArcGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));
    if (!(std::find( link_array.begin(),  link_array.end(), std::pair <int, int>(from, to)) !=  link_array.end())) {
        link_array.emplace_back(std::pair<int, int>(from, to));
    }

};

std::vector<int> ArcGraph::GetNextVertices(int vertex) const{
    assert(isValidIndex(vertex));
    std::vector<int> next_vertices;
    for(auto edge: link_array){
        if (edge.first == vertex){
            next_vertices.push_back(edge.second);
        }
    }
    return next_vertices;
};

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const{
    assert(isValidIndex(vertex));
    std::vector<int> next_vertices;
    for(auto edge: link_array){
        if (edge.second == vertex){
            next_vertices.push_back(edge.first);
        }
    }
    return next_vertices;
}

bool ArcGraph::isValidIndex(int index) const {
    return 0 <= index && index < number_of_vertices;
}