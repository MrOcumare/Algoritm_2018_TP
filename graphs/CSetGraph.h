//
// Created by Mr.Ocumare on 17.12.2018.
//

#ifndef GRAPHS_CSETGRAPH_H
#define GRAPHS_CSETGRAPH_H
#include "IGraph.h"
#include <unordered_set>

#ifndef INC_1_CSETGRAPH_HPP
#define INC_1_CSETGRAPH_HPP

class SetGraph : public IGraph {
public:
    explicit SetGraph(int n);

    ~SetGraph() = default;

    explicit SetGraph(const IGraph &other);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override{
        return set_graph.size();
    };

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    // граф хранится как массив хештаблиц.
    // индекс в массиве - номер вершины, из которой исходит ребро.
    // хештаблица хранит номера всех вершин, в которые можно попасть.
    std::vector<std::unordered_set<int>> set_graph;

    bool isValidIndex(int index) const;
};
#endif //INC_1_CSETGRAPH_HPP
#endif //GRAPHS_CSETGRAPH_H
