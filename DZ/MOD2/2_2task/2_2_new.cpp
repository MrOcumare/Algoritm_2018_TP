/*

Выполнил Мурашко И.А. АПО-13
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 Требуется построить бинарное дерево, заданное наивным порядком вставки. 
 Т.е., при добавлении очередного числа K в дерево с корнем root, 
 если root→Key ≤ K, то узел K добавляется в правое поддерево root; 
 иначе в левое поддерево root. Выведите элементы в порядке pre-order 
 (сверху вниз).

Рекурсия запрещена.
Ввод	Вывод  2 1 5 4 3 6 7 8 9 10 
10
2
5
6
4
7
8
9
3
1
10

*/

//через функторы бахнуть удаление и обход 

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>

template<class T>
class TreeNode{                         //  узел дерева
private:
    T data;
    TreeNode<T>* Parent;                   //  хранит указатель на родителя
    TreeNode<T>* Left;                     //  указатель на левого потомка
    TreeNode<T>* Right;                    //  указатель на правого потомка 
public:
    int get_data(){return data;}        //  возвращает значение 
    void set_right(TreeNode* val) {     //  меняем значение левого потомка 
        this->Right = val;
    };
    void set_left(TreeNode* val){       // меняем занчение правого потомка
        this->Left = val;
    };
    void set_data(int val){ this->data = val;}
    TreeNode<T>* get_left(){return Left;}      //  считываем занчение левого потомка
    TreeNode<T>* get_right(){return Right;}    //  считываем значение правого потомка
    TreeNode(int input_data): data(input_data), Parent(NULL), Left(NULL), Right(NULL){}; // конструктор для корневой вершины
    TreeNode(int input_data, TreeNode* I_AM_YORE_FATHER): data(input_data), Parent(I_AM_YORE_FATHER), Left(NULL), Right(NULL){}; // конструктор для других вершин c родителем 
    ~TreeNode() = default;
};
template<class T>
class Tree {                            //  дерево узлов
private: 
    
    TreeNode<T>* root;                       //  необходимо знать корневую ноду
    std::vector<int> ResultOfPreOrder;  //  вектор хранения результатов 
public:
    Tree(){
        root = NULL;
    }               // конструктор по умолчанию
    Tree(int val){
        root = new TreeNode<T>(val);       //  конструктор 
    }
    Tree(const Tree<T>&) = delete;
    Tree<T>& operator=(const Tree<T>&) = delete;
    Tree<T>& operator=(Tree<T>&& other) = delete;
    Tree(Tree<T>&& other) = delete;

    ~Tree() {
        if (root == NULL) {
            return;
        } 
        std::queue<TreeNode<T>*> queuefordell;
        queuefordell.push(root); 
        while( !queuefordell.size() == 0 ) {
            if (queuefordell.front()->get_left() != nullptr) { 
                queuefordell.push(queuefordell.front()->get_left());
            }
            if (queuefordell.front()->get_right() != nullptr) {
                queuefordell.push(queuefordell.front()->get_right());
            }
            delete queuefordell.front();
            queuefordell.pop();
        }
        
    }
    void add(int val) {                 // ф-ия добавления
        if (root == NULL) {
            root = new TreeNode<T>(val);
            return;
        }
        TreeNode<T>* PTR = root;
        TreeNode<T>* PTR_Parent = NULL;
        while (true) {
            PTR_Parent = PTR;
            if (val < PTR->get_data()){                             // если входное значение меньше текущего то отправляем его в левое поддерево
                if (PTR->get_left() == NULL) {
                    PTR->set_left(new TreeNode<T>(val, PTR_Parent)) ;
                    break;
                }
                PTR = PTR->get_left();
            } else {                                                // иначе в правое
                if (PTR->get_right() == NULL) {
                    PTR->set_right(new TreeNode<T>(val, PTR_Parent));
                    break;
                }
                PTR = PTR->get_right();
            }
        }
    }
    TreeNode<T>* get_root() {

        return root;

    }

    void result_of_preorder(int val) {

        ResultOfPreOrder.push_back(val);

    }

    void show_result_of_preorder() {
       
        for (int i = 0; i < ResultOfPreOrder.size(); i++) {
            std::cout << ResultOfPreOrder[i] << " ";
        }  

    }
//получает на фход функтр 
    void iterPreorder() {                       //   преордер обход 
    TreeNode<T>* root = this->get_root();
    std::vector<TreeNode<T>*> V;
    while (V.size() != 0 || root != NULL) {
        if (root != NULL) {

            this->result_of_preorder((root->get_data()));

            if (root->get_right()) {
                V.push_back(root->get_right());
            }
            root = root->get_left();
        } else {
            root = V.back();
            V.pop_back();
        }
    }   
} 
}; 




                                                                
int main() {
    
    int count = 0; //количество элементов в дереве 
    std::cin >> count; 

    int input = 0; // входное значение
    Tree<int> MyTree;
    while (count != 0) {

        std::cin >> input;
        MyTree.add(input);
        count--;

    }

    MyTree.iterPreorder();
    MyTree.show_result_of_preorder();




    return 0;
}