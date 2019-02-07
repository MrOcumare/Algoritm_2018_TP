//
// Created by Mr.Ocumare on 18.12.2018.
//
#include "IGraph.h"
#include <utility>
#ifndef GRAPHS_CARCGRAPH_H
#define GRAPHS_CARCGRAPH_H

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int n) : number_of_vertices(n) {}

    ~ArcGraph(){};

    explicit ArcGraph(const IGraph &other);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override {
        return number_of_vertices;
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    // массив начал и концов рёбер.
    std::vector<std::pair<int, int>> link_array;

    bool isValidIndex(int index) const;

    // количество вершин в графе.
    size_t number_of_vertices;
};

#endif //GRAPHS_CARCGRAPH_H
