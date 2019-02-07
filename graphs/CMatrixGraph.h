//
// Created by Mr.Ocumare on 17.12.2018.
//
#include <vector>
#include "IGraph.h"
#include <iostream>
#ifndef GRAPHS_CMATRIXGRAPH_H
#define GRAPHS_CMATRIXGRAPH_H
class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int n) : adjacency_matrix(n) {
        for (int i = 0; i < n; i++) {
            adjacency_matrix[i].push_back(0);
        }
    }

    ~MatrixGraph() = default;

    explicit MatrixGraph(const IGraph &other);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override {
        return adjacency_matrix.size();
    }




    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
    friend std::ostream& operator<<(std::ostream& os, const IGraph& graph);
    std::vector<std::vector<int> > adjacency_matrix;
private:

    // массив двусвязных списков
    // индекс в массиве - номер вершины, из которой исходит вершина.
    // в списке перечислены номера вершин, в которые можно попасть из этой вершины.
//    std::vector<std::vector<int> > adjacency_matrix;

    bool isValidIndex(int index) const;
};
#endif //GRAPHS_CMATRIXGRAPH_H
