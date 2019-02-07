#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include <queue>

//////todo  обход в ширину вынести сделать шаблонной



////////////////////////////////////////////////////------описание наивного дерева------////////////////////////////////////////////////////
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
    TreeNode(const TreeNode<T>&) = delete;
    TreeNode<T>& operator=(const TreeNode<T>&) = delete;
    TreeNode<T>& operator=(TreeNode<T>&& other) = delete;
    TreeNode(TreeNode<T>&& other) = delete;
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
    int treeHeight(TreeNode<T> *PTR) {
        if (PTR == 0)
        {
            return 0;
        }
        int left = treeHeight(PTR->get_left());
        int right = treeHeight(PTR->get_right());
        return 1 + std::max(left, right);
    }
    TreeNode<T>* get_root() {

        return root;

    }
}; 
////////////////////////////////////////////////////------описание наивного дерева------////////////////////////////////////////////////////


////////////////////////////////////////////////////------описание декартового дерева------////////////////////////////////////////////////////
template<class T>
class DecartTreeNode {
public:
    T data;                   //  значение ноды 
    int priority;                   //  приоритет ноды
    DecartTreeNode<T>* Left;                   //  указатель на левую ноду
    DecartTreeNode<T>* Right;                  //  указатель на правую ноду
    DecartTreeNode(): Left(NULL), Right(NULL){}                     //  конструктор по умолчанию
    DecartTreeNode(int val_data, int val_priority): Left(NULL) , Right(NULL), data(val_data), priority(val_priority){}                  //  конструктор по знпчеию
    DecartTreeNode(const DecartTreeNode<T>&) = delete;
    DecartTreeNode<T>& operator=(const DecartTreeNode<T>&) = delete;
    DecartTreeNode<T>& operator=(DecartTreeNode<T>&& other) = delete;
    DecartTreeNode(DecartTreeNode<T>&& other) = delete;
};
template<class T>
class DecartTree{
public:
    DecartTree(): root(NULL){};
    void Insert(int val_data, int val_priority){
        DecartTreeNode<T>* InsertNode = new DecartTreeNode<T>(val_data, val_priority);
        add(root, InsertNode);
    }
    DecartTree(const DecartTree<T>&) = delete;
    DecartTree<T>& operator=(const DecartTree<T>&) = delete;
    DecartTree<T>& operator=(DecartTree<T>&& other) = delete;
    DecartTree(DecartTree<T>&& other) = delete;
    ~DecartTree() {
        if (root == NULL) {
            return;
        } 
        std::queue<DecartTreeNode<T>*> queuefordell;
        queuefordell.push(root); 
        while( !queuefordell.size() == 0 ) {
            if (queuefordell.front()->Left != nullptr) { 
                queuefordell.push(queuefordell.front()->Left);
            }
            if (queuefordell.front()->Right != nullptr) {
                queuefordell.push(queuefordell.front()->Right);
            }
            delete queuefordell.front();
            queuefordell.pop();
        }    
        
    }
    void add(DecartTreeNode<T>*& PTR_root, DecartTreeNode<T>* PTR_insert){
        if (PTR_root == NULL){
            PTR_root = PTR_insert;
        }else if (PTR_root->priority < PTR_insert->priority) {
            Split (PTR_root, PTR_insert->data, PTR_insert->Left, PTR_insert->Right);
            PTR_root = PTR_insert;
        } else {
            if (PTR_insert->data < PTR_root->data){
                add(PTR_root->Left, PTR_insert);
            } else {
                add(PTR_root->Right, PTR_insert);
            }
        }
    }
    void Split(DecartTreeNode<T>* PTR_root, int data, DecartTreeNode<T>*& PTR_left, DecartTreeNode<T>*& PTR_right){
        if (PTR_root == NULL){
            PTR_left = NULL;
            PTR_right = NULL;
        } else if (data < PTR_root->data) {
            Split(PTR_root->Left, data, PTR_left, PTR_root->Left);
            PTR_right = PTR_root;
        } else {
            Split(PTR_root->Right, data, PTR_root->Right, PTR_right);
            PTR_left = PTR_root;
        }
    }
    DecartTreeNode<T>* get_root() {
        return root;
    }

    int treeHeight(DecartTreeNode<T>* PTR)
    {
        if (PTR == 0) {
            return 0;
        }
        int left = treeHeight(PTR->Left);
        int right = treeHeight(PTR->Right);
        return 1 + std::max(left, right);
    }

private:
    DecartTreeNode<T>* root;   
};
////////////////////////////////////////////////////------описание декартового дерева------////////////////////////////////////////////////////
int main()
{
    int count = 0;                  //  количество нод дерева
    std::cin >> count;

    int priority = 0,                    //  ключ дерева
        data = 0;                   //  вес(приоритет)

    Tree<int> MyTree; 
    DecartTree<int> MyDecartTree;
    for (int i = 0; i < count; i++){
        std::cin >> data >> priority;                    //  вводим значения 
        MyTree.add(data);
        MyDecartTree.Insert(data, priority);
    }
    std::cout << abs(MyTree.treeHeight(MyTree.get_root()) -  MyDecartTree.treeHeight(MyDecartTree.get_root()));
  
    return 0;
}

