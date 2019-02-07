#include <vector>
#include <list>
#include <cassert>
#include <queue>
#include <cstdint>
#include <iostream>
#include <algorithm>

struct NodeGraph {
    int min_len_way;                   // у каждой ноды будет храниться минимальная длииина пути
    int count_of_inc_list_graph;      // количество входных вершин с минимальной длииной
    std::list<int> links_list;       // список связей

    NodeGraph() : min_len_way(0), count_of_inc_list_graph(0), links_list() {};

};

class ListGraph {
public:
     ListGraph(int n) :  list_graph(n), nod_from(-1) {};

    ~ListGraph() = default;

    void AddEdge(int from, int to) {
        assert(isValidIndex(from));
        assert(isValidIndex(to));
        if (!(std::find( list_graph[from].links_list.begin(),  list_graph[from].links_list.end(), to) !=  list_graph[from].links_list.end())) {
            list_graph[from].links_list.push_back(to);
            list_graph[to].links_list.push_back(from);
        }
    };

    int CountOfShortWays(int from, int to) { // возвращает количество кратчайших вершин между вершинами
        if ( this->nod_from == -1 ) {
            BFS(from);
            return list_graph[to].count_of_inc_list_graph;
        } else if (this->nod_from == from) {
            return list_graph[to].count_of_inc_list_graph;
        }
    };

private:
    std::vector<NodeGraph> list_graph;
    int nod_from;
    bool isValidIndex(int index) const {
        return 0 <= index && index < list_graph.size();
    };

    void BFS(int from) {
        std::queue<int> nodes_queue; // очередь рассматриваемых вешин
        nodes_queue.push(from);
        list_graph[from].count_of_inc_list_graph = 1;
        list_graph[from].min_len_way = 0;
        while (!nodes_queue.empty()) {
            int curreent_nod = nodes_queue.front(); // текущая рассматриваемая вершина
            nodes_queue.pop();
            int new_way = list_graph[curreent_nod].min_len_way + 1;
            for (int to : list_graph[curreent_nod].links_list) {
                if (list_graph[to].count_of_inc_list_graph != 0) { //  проверка на вхождение в вершину
                    if (new_way < list_graph[to].min_len_way) {    // если новый путь меньше чем уже существующий
                        list_graph[to].min_len_way = new_way;
                        list_graph[to].count_of_inc_list_graph = list_graph[curreent_nod].count_of_inc_list_graph;
                    } else if (new_way == list_graph[to].min_len_way) { // если путь такой же длинны
                        list_graph[to].count_of_inc_list_graph += list_graph[curreent_nod].count_of_inc_list_graph;
                    }
                } else {                                            // иначе мы не были в этой вершине
                    nodes_queue.push(to);                         // добавдяем все пути через которые можно прийти в эту вершину
                    list_graph[to].count_of_inc_list_graph += list_graph[curreent_nod].count_of_inc_list_graph;
                    list_graph[to].min_len_way = new_way;

                }
            }
        }
    };
};
int main() {
    int nods = 0, //количестов вершин графа
        from = 0,
        to = 0,
        links = 0; //количетсо ребер графа

    std::cin >> nods;
    ListGraph list_graph(nods);

    std::cin >> links;

    for(int i = 0; i < links; ++i){
        int from(0), to(0);
        std::cin >> from >> to;
        list_graph.AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << list_graph.CountOfShortWays(from, to) << std::endl;
    return 0;
}