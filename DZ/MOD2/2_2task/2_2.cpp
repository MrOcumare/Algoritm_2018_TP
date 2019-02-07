#include <iostream>
//TODO: вкорячить правило 5
#include <cassert>



class TreeNode{                         //  узел дерева
private:
    int data;
    TreeNode* Parent;                   //  хранит указатель на родителя
    TreeNode* Left;                     //  указатель на левого потомка
    TreeNode* Right;                    //  указатель на правого потомка 
public:
    int get_data(){return data;}        //  возвращает значение 
    void set_right(TreeNode* val) {     //  меняем значение левого потомка 
        this->Right = val;
    };
    void set_left(TreeNode* val){       // меняем занчение правого потомка
        this->Left = val;
    };
    TreeNode* get_left(){return Left;}      //  считываем занчение левого потомка
    TreeNode* get_right(){return Right;}    //  считываем значение правого потомка
    TreeNode(int input_data): data(input_data), Parent(NULL), Left(NULL), Right(NULL){}; // конструктор для корневой вершины
    TreeNode(int input_data, TreeNode* I_AM_YORE_FATHER): data(input_data), Parent(I_AM_YORE_FATHER), Left(NULL), Right(NULL){}; // конструктор для других вершин c родителем 
};

class Tree {                            //  дерево узлов
private: 
    TreeNode* root;                     //  необходимо знать корневую ноду
public:
    Tree(int val){
        root = new TreeNode(val);       //  конструктор 
    }
    void add(int val) {                 // ф-ия добавления
        TreeNode* PTR = root;
        TreeNode* PTR_Parent = NULL;
        while (true) {
            PTR_Parent = PTR;
            if (val < PTR->get_data()){                             // если входное значение меньше текущего то отправляем его в левое поддерево
                if (PTR->get_left() == NULL) {
                    PTR->set_left(new TreeNode(val, PTR_Parent)) ;
                    break;
                }
                PTR = PTR->get_left();
            } else {                                                // иначе в правое
                if (PTR->get_right() == NULL) {
                    PTR->set_right(new TreeNode(val, PTR_Parent));
                    break;
                }
                PTR = PTR->get_right();
            }
        }
    }
    TreeNode* get_root() {
        return root;
    }
     
}; 

typedef struct Stack {
    size_t size;
    size_t capacity;
    TreeNode **data;
} Stack;
 
Stack* newStack() {
    Stack* TMP = new Stack();
    TMP->capacity = 8;
    TMP->size = 0;
    TMP->data = new TreeNode* [TMP->capacity];
    return TMP;
}
 
void freeStack(Stack **s) {
    delete[] (*s)->data;
    delete (*s);
    *s = NULL;
}


void push(Stack *s, TreeNode *item) {
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        TreeNode** Buffer = new TreeNode* [s->capacity];
        for (int i = 0; i < s->size; i++){
            Buffer[i] = s->data[i];
        }
        delete[] s->data;
        s->data = Buffer;
        delete[] Buffer;
        //s->data = (TreeNode**) realloc(s->data, s->capacity * sizeof(TreeNode*));
    }
    s->data[s->size++] = item;
}
 
TreeNode* pop(Stack *s) {
    if (s->size == 0) {
        assert("Стек пуст");
    }
    s->size--;
    return s->data[s->size];
}
 
void iterPreorder(TreeNode  *root) {                       //   преордер обход
    Stack *Stack_Node = newStack();
        while (Stack_Node->size != 0 || root != NULL) {
            if (root != NULL) {
                std::cout << root->get_data() << " ";
                if (root->get_right()) {
                    push(Stack_Node, root->get_right());
                }
                root = root->get_left();
            } else {
                root = pop(Stack_Node);
            }
        }
        freeStack(&Stack_Node);
} 

    // void preOrder(TreeNode* PTR){                            //    рекурсивный обход
    //     if (PTR == NULL) return;                             //    рекурсивный обход
    //         std::cout << PTR->get_data() << " ";             //    рекурсивный обход
    //         preOrder(PTR->get_left());                       //    рекурсивный обход
    //         preOrder(PTR->get_right());                      //    рекурсивный обход
    //         }                                                //    рекурсивный обход
    // void show(){                                             //    рекурсивный обход
    //     TreeNode* PTR = root;                                //    рекурсивный обход
    //     preOrder(PTR);                                       //    рекурсивный обход
    // }                                                        //    рекурсивный обход
                                                                



int main() {
    
    int count = 0; //количество элементов в дереве 
    std::cin >> count; 

    int input = 0; // входное значение
    std::cin >> input;
    Tree* MyTree = new Tree(input);

    while (count != 1) {

        std::cin >> input;
        MyTree->add(input);
        count--;

    }
    iterPreorder(MyTree->get_root());
    

    // TODO: вывод дерева



    return 0;
}