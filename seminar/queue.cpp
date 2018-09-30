//реализация очереди на списке 
// необходим закоьцевать 

#include <iostream>
// Queue.h
class Queue{
public:
    Queue(const Queue& other ) = delete;
    //Queue(Queue && other) {*this = std::move(other);}
    
    ~Queue();

    Queue& operator = (const Queue& other) = delete;

    void Push(int value);
    int Pop();
    bool IsEmpty() const {return !head;};
private:
    struct Node;


    Node* head = nullptr;
    Node* tail = nullptr;


};


struct Queue::Node{
    int Value  =0;
    Node* Next = nullptr;
    Node() = default;
    Node(int value) : Value(value){}
    
};

Queue :: ~Queue() 
{
    while (head) {
        Node* node = head;
        head = head -> Next;
        delete node;
    }
}
void Queue::Push(int value)
{
    Node* node = new Node(value);
    if (IsEmpty()) {
        head = tail = node;
        return;
    }
    tail->Next = node;
    tail = node;


}
int Queue::Pop() {
    assert(!IsEmpty());
    int result = head -> Value;
    Node * node =head;
    if (head == tail) {
        head = tail = nullptr;

    } else {
        head = head -> Next;
    }
    delete node;
    return result;
}
void test(){
    Queue queue;
    queue.Push(3);
    queue.Push(4);
    queue.Push(5);

    assert(queue.Pop() == 3);
    assert(queue.Pop() == 4);
    assert(queue.Pop() == 5);
    assert(!queue.IsEmpty());

}
//////////////////////////////////////

struct Operation  {
    int Code = 0;
    int Value = 0;

};

bool do_operation(Queue queue,  Operation op) {
    switch (op.Code) {
        case 3:
            queue.Push(op.Value);
            return true;
        case 2:
        {
            const int result = !queue.IsEmpty() ? queue.Pop() : -1;

            return result == op.Value;
        }
        
    }
    
}


int main() {
    // test();
    // std::cout <<"ZBS";
    Queue queue;
    int n = 0;
    std::cin >> n;
    for (int i =0 ; i < n; i++) {
        Operation op;
        std:: cin >> op.Code >> op.Value;
        if (!do_operation(queue, op)){
            std::cout << "No";
            return 0;
        }
        

        std::cout << "YES";

    } 
}




