/*
задача 4_3 
Мурашко АПО - 13
На вокзале есть некоторое количество тупиков, куда прибывают электрички. 
Этот вокзал является их конечной станцией. Дано расписание движения электричек, 
в котором для каждой электрички указано время ее прибытия, а также время 
отправления в следующий рейс. Электрички в расписании упорядочены по времени 
прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным 
номером. При этом если электричка из какого-то тупика отправилась в момент 
времени X, то электричку, которая прибывает в момент времени X, в этот тупик 
ставить нельзя, а электричку, прибывающую в момент X+1 — можно. В данный момент 
на вокзале достаточное количество тупиков для работы по расписанию. 
Напишите программу, которая по данному расписанию определяет, какое 
минимальное количество тупиков требуется для работы вокзала.*/



#include <iostream>
#include <cassert>
class Heap{
public:
    Heap(){
        size = 0;
        capacity = 1;
        result = 0;
        array = new int[capacity];
    }
    
    Heap( const Heap& ) = delete; // конструктор копирования 
    void operator=( const Heap& ) = delete; // Оператор присваивания копированием
    Heap& operator=(Heap&& other) = delete ; // Оператор присваивания перемещением
    Heap(Heap&& other) = delete; // Конструктор перемещения
    
    ~Heap(){
        delete[] array;
    }

    void rewrite_first(){
        assert(size >= 0);

        int buffer = array[0];
        array[0] = array[size - 1];
        --size;
        if(size > 0) {
            SiftDown(0);
        }
    }
    void add_train(int train_in, int train_out){
        if (capacity == size ){
             realloc_array();
         }
        if(size != 0 && array[0] < train_in) {
            rewrite_first();
        }
        array[size] = train_out;
        SiftUp(size);
        size++;
        if (result < size){
            result = size;
        }
    }
    void realloc_array(){
        int * buffer = new int [capacity * 2];
        for (int i = 0; i < size; i++){
            buffer[i] = array[i];
        }
        delete[] array;
        capacity *= 2;
        array = new int [capacity * 2];
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
    int get_result(){
        return result;
    }

private:
    size_t size;
    size_t capacity;
    int result;
    int* array;
    void SiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if(array[index] >= array[parent]) {
                return;
            }
            std::swap(array[index], array[parent]);
            index = parent;
        }
    }
    void SiftDown(int index) {
        while(true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int parent = index;

            if(left < size && array[parent] > array[left]) {
                parent = left;
            }
            if(right < size && array[parent] > array[right]) {
                parent = right;
            }

            if(parent != index) {
                std::swap(array[index], array[parent]);
                //SiftDown(parent);
                index = parent;
            } else {
                break;
            }
        }
    }
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
    //MyHeap.print();
    std::cout << MyHeap.get_result();
    return 0;

}