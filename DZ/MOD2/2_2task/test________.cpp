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
#include <deque>

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

    void static displayElement(TreeNode<T>* PTR) {
        std::cout << PTR->get_data() << ' ';
    };

    void iterPreorder(std::function<void(TreeNode<T>*)> processElement) {                       //   преордер обход
        if (root == nullptr)
            return;
        TreeNode<T>* PTR = root;
        std::vector<TreeNode<T>*> V;
        V.push_back(root);
        while (V.size() > 0) {
            PTR = V.back();
            processElement(PTR);
            V.pop_back();
            if (PTR->get_right())
                V.push_back(PTR->get_right());
            if (PTR->get_left())
                V.push_back(PTR->get_left());

        }


    }

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
        std::vector<TreeNode<T>*> V;

        iterPreorder([&V](TreeNode<T>* element) {
            V.push_back(element);
        });
        while (V.size() > 0) {
            TreeNode<T>* dellelement = V.back();
            V.pop_back();
            delete dellelement;
        }

    }
    void preorder_show() {
        iterPreorder(displayElement);
    };
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

//получает на фход функтр

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
    MyTree.preorder_show();





    return 0;
}