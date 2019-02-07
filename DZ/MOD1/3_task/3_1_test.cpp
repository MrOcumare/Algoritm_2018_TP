
// Реализовать очередь с динамическим зацикленным буфером.

// Обрабатывать команды push back и pop front.

// Формат ввода
// В первой строке количество команд n. n ≤ 1000000.

// Каждая команда задаётся как 2 целых числа: a b.

// a = 2 - pop front
// a = 3 - push back

// Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.


#include <iostream>
#include <cassert>
#define DefaulCapacity 8
class Queue {
    public:
        Queue() {
            capacity = DefaulCapacity;
            size = 0;
            tail = 0;
            head = 0;
            data = new long[capacity];
        }
        ~Queue() {
            delete[] data;
        }
        void push(long value) {
            if(size == capacity) {
                myRealloc();
            }
            data[tail % capacity] = value;
            tail++;
            size++;
        }
        long pop() {
            if(size == 0) {
                return -1;
            }
            size--;
            return data[(head++)%capacity];
        }
    private:
        long* data;
        long capacity;
        long head;
        long tail;
        long size;
        Queue( const Queue& ) = delete;
        void operator=( const Queue& ) = delete;
        void myRealloc() {
            capacity *= 2;
            long* newData = new long[capacity];
            long j = 0;
            for(long i = head; i < size + head; i++) {
                newData[j++] = data[i % (capacity/2)];
            }
            delete[] data;
            data = newData;
            head = 0;
            tail = size;

        }
};
int main(){
    Queue myqueue;
    bool flag = true;

    long CountOperation = 0, code = 0, value = 0;
    std::cin >> CountOperation;
    assert(CountOperation > 0);
    for (long i = 0; i < CountOperation; i++){
        std::cin >> code >> value;
        assert(code == 3 || code == 2);
        if (code == 2) {
           if(myqueue.pop() != value) {
               flag = false;
           }
        } else if(code == 3) {
            myqueue.push(value);
        }
    }
    if (flag){
        std::cout << "YES";
    } else{
        std::cout << "NO";
    }
    return 0;
}
