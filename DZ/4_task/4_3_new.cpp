#include <iostream>

class Heap{
public:
    Heap(){
        size = 0;
        capacity = 8;
        result = 0;
        int * array = new int[capacity];
    }
    ~Heap(){
        delete[] array;
    }
    void add_train(int train_in, int train_out){
        // if (capacity == size ){
        //     realloc_array();
        // }
        array[size] = train_in;
        size++;
    }
    void realloc_array(){
        int * buffer = new int [capacity * 2];
        for (int i = 0; i < size; i++){
            buffer[i] = array[i];
        }
        delete[] array;
        capacity *= 2;
        int * array = new int [capacity * 2];
        for (int i = 0; i < size; i++) {
            array[i] = buffer[i];
        }
        delete[] buffer;
    }

    void print(){
        for (int i = 0; i < size; i++){
            std::cout << array[i] << " ";
        }
    }

private:
    size_t size;
    size_t capacity;
    int result;
    int* array;
};

int main() {
    Heap MyHeap;
    int n = 0,
    train_in = 0,
    train_out = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> train_in >> train_out;
        MyHeap.add_train(train_in, train_out);
    }


    return 0;

}