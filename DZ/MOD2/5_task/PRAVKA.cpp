#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <functional>

#include <string>
#include "haffman.h"
struct DereferenceCompareNode;
class Tree;
class TreeNode;

class TreeNode{                         //  узел дерева
private:
    int data;
    char character;
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
 
};
 
class Tree {                            //  дерево узлов
private: 
    
    TreeNode* root;                     //  необходимо знать корневую ноду
    std::vector<int> ResultOfPreOrder;  //  вектор хранения результатов 

public:
    std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck; 

    
    Tree(){
        root = NULL;
    }               // конструктор по умолчанию

    Tree(int val,  char c){
        root = new TreeNode(val, c);       //  конструктор 
    }

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

}; 

struct DereferenceCompareNode : public std::binary_function<Tree*, Tree*, bool> {
    bool operator()(Tree* lhs, Tree* rhs) const {
        return lhs->get_root()->get_data() > rhs->get_root()->get_data();
    }
}; 



void bild_table(TreeNode* Node, std::string &Buf, std::string* result) {
    if (Node->get_character() != '\0') {
        result[(int)Node->get_character()] = Buf;
    }
    if (Node->get_left()){
        bild_table(Node->get_left(), Buf.append("0"), result);
        Buf = Buf.substr(0, Buf.size()-1);
    }
    if(Node->get_right()){
        bild_table(Node->get_right(), Buf.append("1"), result);
        Buf = Buf.substr(0, Buf.size()-1);
    }
    
}

std::string* bild_table(Tree* tree) {
    TreeNode* Node = tree->get_root();
    std::string* result = new std::string[256];
    std::string Buf = "";
    bild_table(Node, Buf, result); 
    return result;
}


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
       std::cout << q.top()->get_root()->get_character() << " " <<  q.top()->get_root()->get_data() << std::endl;
        q.pop();
    }
    std::cout << '\n';
}

void Encode(CInputStream& input, COutputStream& output){
    int mass[256] = {0};
    std::vector<char> wer;
    unsigned char c = 0;
	while (!input.Read(c)) { 
        mass[c]++;
        wer.push_back(c);
    }
    // std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck;
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
  
    std::string* table_code = bild_table(nodesToCheck.top());


    int count = 0; char buf = 0;
    while (!input.Read(c)) { 
        std::vector<bool> x;
        for (int i = 0; i < table_code[(int)c].length(); i++) {
            if (table_code[(int)c][i] == '1') {
                x.push_back(1);
            } else {
                x.push_back(0);
            }
        }
        for(int n = 0; n < x.size(); n++) {
            buf = buf | x[n] << (7 - count);   
            count++;   
            if (count == 8) { 
                count=0;   
                ofstream out((output.outputFileName).c_str());
                out << (buf); 
                //output.Write(buf);  
                buf=0;
            }
        }
    }
}
void Decode(COutputStream& output, CInputStream& input)  {
    //std::ifstream F("output.txt", std::ios::in | std::ios::binary);
    TreeNode *PTR = nodesToCheck.top()->get_root();
    int count = 0; 
    byte R_byte; 
	while(!input.Read(R_byte))
	{   bool b = R_byte & (1 << (7 - count)) ; 
		if (b) PTR=PTR->get_right(); 
        else PTR=PTR->get_left();
		if (PTR->get_left() == NULL && PTR->get_right() == NULL) {
            ofstream out((output.outputFileName).c_str());
            out << (PTR->get_character()); 

            PTR=nodesToCheck.top()->get_root();
        }  
		count++;
		// if (count == 8) {
        //     count = 0; 
        //     R_byte = output.Read();
        // }
	}
    
	
}
int main() {

    string inputFileName = "input.txt";
    string outputFileName = "output.txt";

    CInputStream input( inputFileName );
    COutputStream output( outputFileName );  

    Encode( input, output );
    Decode( output, input );


    return 0;
}
// int main()
// {
//     // std::ifstream f("1.txt", std::ios::out | std::ios::binary);
	
//     // int mass[256] = {0};
   
// 	// while (!f.eof()) { 
//     //     unsigned char c = f.get();
       
//     //     mass[c]++;
//     // }
//     // std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck;

//     // for(int i = 0; i < 256; i++ ) 
//     // {
//     //     if ( mass[i] != 0 ){
//     //         nodesToCheck.push(new Tree(mass[i], (char)i));
//     //     }
//     // }
//     // while(nodesToCheck.size() > 1){
//     //     Tree* a = nodesToCheck.top();
//     //     nodesToCheck.pop();
//     //     Tree* b = nodesToCheck.top();
//     //     nodesToCheck.pop();
//     //     nodesToCheck.push(new Tree(a, b));
//     // }
  
//     // std::string* table_code = bild_table(nodesToCheck.top());
//     // f.clear(); f.seekg(0);
//     // f.close();

//     Encode(table_code);


     
//     delete[] table_code;

//     // TreeNode *PTR = nodesToCheck.top()->get_root();
//     // Decode(PTR, nodesToCheck);


	
//     return 0;
// }
