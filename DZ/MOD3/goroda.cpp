//не добавлять новый элемент а поднимать с имененным приоритетом (если уменьшаем),
// а если увеличиваем то ничего делать не надо 


//восьминажки делаем короч
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
class State {
public:
    State(const std::string& state) : body(state) {
        checkAndfindNullPos();
    }
    std::vector <State> GetNextState() const;
private:
    std::string body;
    unsigned char nullPos;               //положение нуля 
    void checkAndfindNullPos();
};

void State::checkAndfindNullPos()
{
    for (int i =0; i  < body.length(); i++) {
        assert('0' <= body[i] &&  body[i] <= '9');
        if (body[i] == '0') {          ///ищем ноль короч 
            assert(nullPos < 0);
            nullPos = i;
        }
    }
}

std::vector <State> State::GetNextState() const{
    std::vector <State> result;
    if(nullPos > 2) {
        std::string up(body);
        std::swap(up[nullPos], up[nullPos - 3]);
        result.push_back(State(up));
    }
    if(nullPos < 6) {
        State down(body);
        std::swap(down.body[nullPos], down.body[nullPos + 3]);
        result.push_back(State(down));
    }
    if(nullPos % 3 != 0) {
        std::string left(body);
        std::swap(left[nullPos], left[nullPos + 3]);
        result.push_back(State(left));
    }
    if(nullPos % 3 != 2) {
        std::string right(body);
        std::swap(right[nullPos], right[nullPos + 3]);
        result.push_back(State(right));
    }
    return result;
}
struct Node {
    State Current;
    State Prev;

    int distance;
    Node (int i, State C, State P){
        this->Current = C;
        this->Prev = P;
        this->distance = i;
    }
};

bool operator < (Node node1, Node node2) {
    return node1.distance < node2.distance;
}
bool operator ==

std::vector <State> Dijkstra(State start, State finish) {

    std::unordered_map <State, std::pair<int, State> > states;

    std::priority_queue<Node > queue;

    queue.push(Node({0, start, finish}));
    while (!queue.empty()){
        auto value = queue.top();
        queue.pop();
        if( states.find(value.Current) == states.end()) {
            continue;
        }
        states.insert(std::make_pair(value.Current, std::make_pair(value.distance, value.Prev)));
        if (finish == value.Current) {
            break;
        }
        for (auto next: value.Current.GetNextState()){
            if (states.find(next) != states.end()) {
                continue;
            }
            queue.push(Node( {value.distance + 1, next, value.Current}));
        }
    }
    std::stack<State> result;
    result.push
}

int main() {

    return 0;
}