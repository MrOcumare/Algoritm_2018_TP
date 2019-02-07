//
// Created by Mr.Ocumare on 21.12.2018.
//
#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include "IGraph.h"
#ifndef GRAPHS_GENERATOR_H
#define GRAPHS_GENERATOR_H

//class Generator{
//public:
//    static IGraph GraphGenerator(int, int) ;
//    static int GetRand (int, int);
//};

class Generator : public IGraph {
public:
    explicit Generator(int n, int m);

    ~Generator() = default;

    explicit Generator(const IGraph &other);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override{
        return buffer_list_graph.size();
    };

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    int GetRand(int size, int pos);
private:
    // граф хранится как массив хештаблиц.
    // индекс в массиве - номер вершины, из которой исходит ребро.
    // хештаблица хранит номера всех вершин, в которые можно попасть.
    std::vector<std::list<int>> buffer_list_graph;

    bool isValidIndex(int index) const;
};
#endif //GRAPHS_GENERATOR_H
