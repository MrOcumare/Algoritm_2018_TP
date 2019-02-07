//
// Created by Mr.Ocumare on 17.12.2018.
//
#include <vector>
#include <algorithm>
#include <ostream>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#ifndef GRAPHS_IGRAPH_H
#define GRAPHS_IGRAPH_H
struct IGraph {
public:

    virtual ~IGraph(){};

    // граф ориентированный,
    // добавление неориентированного ребра
    //     от 'from' к 'to'.
    //     от 'to' к 'from'.
    virtual void AddEdge(int from, int to) = 0;

    // количество вершин.
    // номер вершины ∈ [0, VerticesCount)
    virtual size_t VerticesCount() const = 0;

    // возвращает номера всех вершин, в которые можно попасть из 'vertex'.
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    // возвращает номера всех вершин, из которых можно попасть в 'vertex'.
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

    // вывод графа в виде строки [1 ⟶ 2, 2 ⟶ 4].
    friend std::ostream& operator<<(std::ostream& os, const IGraph& graph);
};
#endif //GRAPHS_IGRAPH_H
