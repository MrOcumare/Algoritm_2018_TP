#include <iostream>
#include "Generator.h"
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"
#include "chrono"

struct Time {
    float setFinish() {
        timeFinish = std::chrono::steady_clock::now();
    };

    void setStart() {
        timeStart = std::chrono::steady_clock::now();
    };
    void check() {
        auto elapsedMks = std::chrono::duration_cast<std::chrono::microseconds>(timeFinish - timeStart);
        std::cout << "\t\033[0;31m time: " << elapsedMks.count() << " µs" << "\033[0m\n";
    };
    std::chrono::time_point<std::chrono::steady_clock> timeStart;
    std::chrono::time_point<std::chrono::steady_clock> timeFinish;
};







int main() {
    Time my_time;
    int vertices = 0,
        edges = 0;
    std::cout << "Enter the count of graph vertices: ";
    std::cin >> vertices;
    std::cout << "Enter the number of graph edges: ";
    std::cin >> edges;


    my_time.setStart();
    Generator buff(vertices, edges);
    my_time.setFinish();
    my_time.check();

    my_time.setStart();
    ListGraph list_graph(buff);
    my_time.setFinish();
    my_time.check();

    //std::cout << list_graph << "\n";
    my_time.setStart();
    MatrixGraph matr_graph(list_graph);
    my_time.setFinish();
    my_time.check();
    //std:: cout << matr_graph << "\n";
    my_time.setStart();
    SetGraph set_graph(matr_graph);
    my_time.setFinish();
    my_time.check();
    //std:: cout << set_graph << "\n";
    my_time.setStart();
    ArcGraph link_graph(set_graph);
    my_time.setFinish();
    my_time.check();
    //std::cout << link_graph << "\n";
    return 0;
}