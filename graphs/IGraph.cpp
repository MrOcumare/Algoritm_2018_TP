//
// Created by Mr.Ocumare on 17.12.2018.
//

#include "IGraph.h"
std::ostream &operator<<(std::ostream &os, const IGraph &graph) {
    os << "[";
    for (int from = 0; from <  (int)graph.VerticesCount(); from++){
        for(int to = 0; to  <  graph.GetNextVertices(from).size(); to++){
            os << from << " ⟶ " << graph.GetNextVertices(from)[to] << ", ";
        }
    }
    os << "\b\b]";
    return os;
};