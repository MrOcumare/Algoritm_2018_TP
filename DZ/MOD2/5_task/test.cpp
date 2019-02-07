#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <functional>
#include <queue>
#include <string>
const int count_char = 256;
class Tree;
class TreeNode;

class TreeNode{                         //  узел дерева
private:
    int data;
    unsigned char character;
    TreeNode* Left;                     //  указатель на левого потомка
    TreeNode* Right;                    //  указатель на правого потомка 
public:
    int get_data(){return data;}        //  возвращает значение 
    void set_data(int val){ this->data = val;}

    char get_character() {return character;}
    void set_character(char character) {this->character = character;}

    void set_right(TreeNode* val) {     //  меняем значение левого потомка 
        this->Right = val;
    };
    void set_left(TreeNode* val){       // меняем занчение правого потомка
        this->Left = val;
    };
   
    TreeNode* get_left(){return Left;}      //  считываем занчение левого потомка
    TreeNode* get_right(){return Right;}    //  считываем значение правого потомка
    TreeNode() {
        this->data = 0;
        this->character = '\0';
        this-> Left = NULL;
        this->Right = NULL;
    }
    TreeNode(int input_data, char c): data(input_data), character(c), Left(NULL), Right(NULL){}; // конструктор для корневой вершины
    // TreeNode(TreeNode* left, TreeNode* right) {
    //     this->Left = left;
    //     this->Right = right;
    // }
    //TreeNode(int input_data, TreeNode* I_AM_YORE_FATHER): data(input_data), Parent(I_AM_YORE_FATHER), Left(NULL), Right(NULL){}; // конструктор для других вершин c родителем 
};

class Tree {                            //  дерево узлов
private: 

    TreeNode* root;                     //  необходимо знать корневую ноду
    std::vector<int> ResultOfPreOrder;  //  вектор хранения результатов 

public:

    
    Tree(){

        root = NULL;
    }               // конструктор по умолчанию

    Tree(int val,  char c){
        root = new TreeNode(val, c);       //  конструктор 
    }
    /*void add(int val) {                 // ф-ия добавления
        if (root == NULL) {
            root = new TreeNode(val);
            return;
        }
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
    }*/
    
    TreeNode* get_root() {
        return root;
    }

    Tree(Tree* left, Tree *right) {
        this->root = new TreeNode();
        this->root->set_data(left->get_root()->get_data() + right->get_root()->get_data());
        this->root->set_left(left->get_root());
        this->root->set_right(right->get_root());
        this->root->set_character('\0');
    }



    void result_of_preorder(int val) {
        ResultOfPreOrder.push_back(val);
        // std::cout << val << " "; 
        // std::cout << ResultOfPreOrder.size() << " ";
        // std::cout << ResultOfPreOrder[ResultOfPreOrder.size() - 1] << " " << std::endl; 
    }

    void show_result_of_preorder() {
        //std::cout << ResultOfPreOrder.size();
        for (int i = 0; i < ResultOfPreOrder.size(); i++) {
            std::cout << ResultOfPreOrder[i] << " ";
        }
        // for (auto &i : this->ResultOfPreOrder) {
        //     std::cout << i << " ";
        // }
        // std::cout << std::endl;
       
    }
    void iterPreorder() {                       //   преордер обход 
    TreeNode* root = this->get_root();
    std::vector<TreeNode*> V;
    while (V.size() != 0 || root != NULL) {
        if (root != NULL) {

            //std::cout << root->get_data() << " ";
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

struct DereferenceCompareNode : public std::binary_function<Tree*, Tree*, bool> {
    bool operator()(Tree* lhs, Tree* rhs) const {
        return lhs->get_root()->get_data() > rhs->get_root()->get_data();
    }
};


    /*
class Queue{
private:
    Tree QueueNode;
    Tree NextQueueNode;
    int prior;
public:
    Queue(): QueueNode(), NextQueueNode(), prior(0) {};

    Queue(int val, char c) {
        
    }

};
*/
// std::string* codeTable() {
//     std::string * codeTable = new std::string[256];
//     codeTable()
    
// }
// std::string incode(std::string input_text) {
//     std::string * codes = codeTable();
//     std::string resul = "";
//     for (int i = 0; i < input_text.size(); i++) {
//         resul.append(codes[input_text[i]]);
//     }
//     return resul;
// }

void bild_table(TreeNode* Node, std::vector<bool> &Buf, std::vector<bool>* result) {
    if (Node->get_character() != '\0') {
            result[(int)Node->get_character()] = Buf;
            // std::cout << Node->get_character() << "--" << (int)Node->get_character() << "--";
            // for(int i = 0; i < result[(int)Node->get_character()].size(); i++) {
            //     std::cout << result[(int)Node->get_character()][i];
            // }
            // std::cout << std::endl;
    }
    if (Node->get_left()){
        Buf.push_back(0);
        bild_table(Node->get_left(), Buf, result);
    // //std::cout << std::endl << Buf.size() << Buf[0];
        Buf.pop_back();
        //std::cout << "left";
    } 
    if(Node->get_right()){
        Buf.push_back(1);
        bild_table(Node->get_right(), Buf, result);
        Buf.pop_back();
        //std::cout << "right";
    } 
}
    
std::vector<bool>* bild_table(Tree* tree) {
    TreeNode* Node = tree->get_root();
    std::vector<bool>result[count_char];  
    std::vector<bool> Buf; 
    bild_table(Node, Buf, result); 
    return result;
}


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
       std::cout << q.top()->get_root()->get_character() << " " <<  q.top()->get_root()->get_data() << std::endl;
       //std::cout << q.top() << std::endl;
        q.pop();
    }
    std::cout << '\n';
}



int main()
{
    std::ifstream f("1.txt", std::ios::out | std::ios::binary);
	
    int mass[256] = {0};
   
    std::vector<char> wer;
	while (!f.eof()) { 
        unsigned char c = f.get();
        mass[c]++;
        wer.push_back(c);
    }
    std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck;

    for(int i = 0; i < 256; i++ ) 
    {
        if ( mass[i] != 0 ){
            nodesToCheck.push(new Tree(mass[i], (char)i));
        }
    }

    while(nodesToCheck.size() > 1){
        Tree* a = nodesToCheck.top();
        nodesToCheck.pop();
        Tree* b = nodesToCheck.top();
        nodesToCheck.pop();
        nodesToCheck.push(new Tree(a, b));
    }

    //std::cout << nodesToCheck.top()->get_root()->get_data();
    std::vector<bool>* table_code = bild_table(nodesToCheck.top());
/////////////////
    for (int i = 0; i < 256; i++) {
        if (table_code[i].size() > 0){
            for (int j = 0; j < table_code[i].size(); j++) {
                std::cout << table_code[i][j] ;
            
            }
        }
        
        std::cout << std::endl;     
    }

    // print_queue(nodesToCheck);
    // std::string result_of_incode = "";
    // for (int i = 0; i < wer.size(); i++){
    //     //std::cout << wer[i]; 
    //     result_of_incode += table_code[wer[i]];
    // }
    // std::cout << result_of_incode << std::endl;


    // // std::ifstream h("1.txt", std::ios::out | std::ios::binary);
    // // std::string result_of_code = "";
    // // while (!h.eof()) { 
    // //     unsigned char c = f.get();
    // //     //result_of_code.append(table_code[c]);
    // //     std::cout << c;
    // // }
    // // std::cout << result_of_code << std::endl;
    // std::string result_of_decode = "";
    // TreeNode* Buffer = nodesToCheck.top()->get_root();
    // for (int i = 0; i < result_of_incode.length(); i++){
    //     if (result_of_incode[i] == '1') {
    //         Buffer = Buffer->get_right();
    //         if (Buffer->get_character() != '\0') {
    //             result_of_decode += Buffer->get_character();
    //             Buffer = nodesToCheck.top()->get_root();
    //         }
    //     } else if(result_of_incode[i] == '0') {
    //         Buffer = Buffer->get_left();
    //         if (Buffer->get_character() != '\0') {
    //             result_of_decode += Buffer->get_character();
    //             Buffer = nodesToCheck.top()->get_root();
    //         }
    //     }


    // }   
    // std::cout << result_of_decode << std::endl;



    // nodesToCheck.top()->iterPreorder();
    // nodesToCheck.top()->show_result_of_preorder();
    return 0;
}
