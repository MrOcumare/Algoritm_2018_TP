/* Выполнил Мурашко И.А. АПО-13
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, 
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества 
и проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество; 
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству. 
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.
stdin       stdout
+ hello     OK
+ bye       OK
? bye       OK
+ bye       FAIL
- bye       OK
? bye       FAIL
? hello     OK
*/


#include <iostream>
#include <vector>
#include <string>

const int FIRST_SIZE = 8;           // размер первоначальной таблицы по зпдпнию
const int HASH_PARAMETR_1 = 11;     
const int HASH_PARAMETR_2 = 19;     
const double FULL_COEFF = 0.75;     // коэффициент заполнения 



template<class T>
class hash_node{            // класс ноды
public:
    hash_node(const T &val): vallue(val), deleted_flag(false) {}
    bool check_of_deleted() const {return deleted_flag;};
    void set_of_deleted(bool flag) {deleted_flag = flag;}
    const T &get_vallue() const {return vallue;}; // 
    void set_vallue(const T &data) {vallue = data;}

    hash_node(const hash_node<T>&) = delete;
    hash_node<T>& operator=(const hash_node<T>&) = delete;
    hash_node<T>& operator=(hash_node<T>&& other) = delete;
    hash_node(hash_node<T>&& other) = delete;

private:
    T vallue;
    bool deleted_flag;
};

template<class T>
class hash_table {          // класс hash таблицы
public:


    hash_table(): hash_array(FIRST_SIZE, NULL), capacity_of_hash_array(FIRST_SIZE), size_of_hash_array(0) {}
    ~hash_table() {
        for(int i = 0; i < hash_array.size(); i++){
            delete hash_array[i];
        }
    }  
    hash_table(const hash_table<T>&) = delete;
    hash_table<T>& operator=(const hash_table<T>&) = delete;
    hash_table<T>& operator=(hash_table<T>&& other) = delete;
    hash_table(hash_table<T>&& other) = delete;
    bool add(const T& val){
        if (((double) size_of_hash_array / (double) capacity_of_hash_array) >= FULL_COEFF){
            rehash_array();
        }
        int hash1 = first_hesh_func(val, capacity_of_hash_array);
        int hash2 = second_hesh_func(val, capacity_of_hash_array);
        int k = 0;
        int first_of_del = -1;        
        while (hash_array[hash1] != NULL && k < capacity_of_hash_array) {
            if(hash_array[hash1]->get_vallue() == val && !hash_array[hash1]->check_of_deleted()){   // проверка на вхождение значения 
                return false;                                                                         
            }
            if(hash_array[hash1]->check_of_deleted() && first_of_del < 0) {
                first_of_del = hash1;                                                               // запоминаем первый удаленный
            }
            hash1 = (hash1 + hash2) % capacity_of_hash_array;
            k++;
            
        }
        if (first_of_del < 0) {
            hash_array[hash1] = new hash_node<T>(val);
        } else {
            hash_array[first_of_del]->set_vallue(val);
            hash_array[first_of_del]->set_of_deleted(false);
        }
        size_of_hash_array++;
        return true;
    }
    bool has(const T& val) {

        int hash1 = first_hesh_func(val, capacity_of_hash_array);
        int hash2 = second_hesh_func(val, capacity_of_hash_array);
        
        int i = 0;

        while(hash_array[hash1] != NULL && i < capacity_of_hash_array) {
            if(hash_array[hash1]->get_vallue() == val && !hash_array[hash1]->check_of_deleted()) {  
                return true;                  //куку, нашли 
            }
            hash1 = (hash1 + hash2) % capacity_of_hash_array;
            i++;
        }
        return false;
    }

    bool del(const T& val) {
        int hash1 = first_hesh_func(val, capacity_of_hash_array);
        int hash2 = second_hesh_func(val, capacity_of_hash_array);
        int i = 0;
        while(hash_array[hash1] != NULL && i < capacity_of_hash_array) {
            if(hash_array[hash1]->get_vallue() == val && !hash_array[hash1]->check_of_deleted()) {  
                hash_array[hash1]->set_of_deleted(true);
                size_of_hash_array--;
                return true;
            }

            hash1 = (hash1 + hash2) % capacity_of_hash_array;
            i++;
        }
        return false;
    }

private:
    std::vector<hash_node <T>*> hash_array;   // hash таблица
    int size_of_hash_array;                   // количество элементов в таблице          
    int capacity_of_hash_array;               // емкость таблицы
    int first_hesh_func(const std::string &val, int capacity) const {
        int hash = 0;
        
        for(int i = val.size() - 1; i >= 0; i--) {
            hash += (HASH_PARAMETR_1 * hash + val[i]) % capacity;
        }
        return hash % capacity;
    }
    int second_hesh_func(const std::string &val, int capacity) const{
        int hash = 0;
 
        for(int i = val.size() - 1; i >= 0; i--) {
            hash += (HASH_PARAMETR_2 * hash + val[i]) % capacity;
        }
        return (2 * hash + 1) % capacity;
    }
    void rehash_array(){
        int new_capasity = capacity_of_hash_array * 2;
        std::vector<hash_node<T>*> new_hash_array(new_capasity, NULL); // новая hash-таблица
        int i = 0;
        while ( i < capacity_of_hash_array) {
            if (hash_array[i] != NULL && !hash_array[i]->check_of_deleted()){
    
                    int hash1= first_hesh_func(hash_array[i]->get_vallue(), new_capasity);
                    int hash2= second_hesh_func(hash_array[i]->get_vallue(), new_capasity);

                    int k = 0;
                    while (new_hash_array[hash1] != NULL && k < new_capasity){
                        hash1 = (hash1 + hash2) % new_capasity;
                        k++;
                    } 
                    new_hash_array[hash1] = hash_array[i];
                
            } else {
                delete hash_array[i];
            }
            hash_array[i] = NULL;
            i++;
        } 
        hash_array = new_hash_array;
        capacity_of_hash_array = new_capasity;  
    }       
};


int main() {
    hash_table <std::string> table;
    char operation;
    std::string string_value;

    while (std::cin >> operation >> string_value) { // ввод операции и фходного значения 
        bool operation_result = false; // результат опетации 
        switch (operation) {
            case '+':
                operation_result = table.add(string_value); // добавление в таблицу
                break;
            case '-':
                operation_result = table.del(string_value); // удаление из таблицы
                break;
            case '?':
                operation_result = table.has(string_value); // проверка на вхождение в таблицу 
                break;
            default:
                //break;
                continue;
        }
        std::cout << (operation_result ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}