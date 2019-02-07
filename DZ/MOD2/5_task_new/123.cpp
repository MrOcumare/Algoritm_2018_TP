#include <iostream>
#include "Huffman.h"
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cassert>
 
using namespace std;

struct Hnode {
    unsigned char ch;
    size_t count;
    Hnode *left;
    Hnode *right;

    Hnode();

    // конструктор для построения узла при сжатии
    Hnode(Hnode *l, Hnode *r, size_t s) {
        left = l;
        right = r;
        count = s;
    }

    // конструктор для построения листа при сжатии
    Hnode(byte c, size_t s) {
        ch = c;
        count = s;
        left = NULL;
        right = NULL;
    }
    // конструктор для построения узла при декодировании
    Hnode(Hnode* l, Hnode* r){ //internal node
        left = l;
        right = r;
    }
    // конструктор для построения листа при декодировании
    Hnode(unsigned char c){ //leaf
        ch = c;
        left = NULL;
        right = NULL;
    }
};

// кастомная сортировка для вектора nodes. Сортируем по полю count
template <typename T1, typename T2>
struct less_first2 {
    typedef Hnode* type;
    bool operator ()(type const& a, type const& b) const {
        return a->count > b->count;
    }
};

class HEncode {
public:
    string bits;

    void initList( const map<char, int>& Symbols );   // Выполняем заполнение вектора List и сортировку
    void initSymbolsBit( const map<char, int>& Symbols );
    void readFile( string filename );
    void treeWayToBin( Hnode *tree, string binCode ); // функция высчитывает путь в двоичном виде
    void huffTree();          // построение дерева Хаффмана
    string encode( string filename );                 // Проходим по всему тексту, преобразуя каждую букву в двоичный символ и считаем колличество бит
    void printTree(Hnode *tree, ofstream & ostr);     // записываем дерево Хаффмана в файл
    byte bitStrToChar(string s);
    void writeZipFile(  string originFileName, string zipFileName );

private:
    vector<byte> data;             // удалить в дальнейшем
    vector<Hnode*> List;      // Хранит в вектор листов, отсортированный по колличеству повторений
    map<char, int> Symbols;   // хранит в себе пары <буква, количество повторений>
    map<char, string> SymbolsBit;   // хранит в себе пары <буква, путь в дереве>
    int numBits;
    int readBytesCount;
};

// Выполняем заполнение вектора List и сортировку
void HEncode::initList( const map<char, int> &Symbols ) {
    for( auto iter : Symbols ){
        List.push_back( new Hnode(iter.first, iter.second) );
    }
    // сразу отсортируем по колличеству элементов
    sort( List.begin(), List.end(), less_first2<Hnode*, Hnode*>() );
}

// Инициализация SymbolsBit с помощью Symbols
void HEncode::initSymbolsBit( const map<char, int> &Symbols ) {
    for( auto iter : Symbols ){
        SymbolsBit[iter.first] = "";
    }
}

// чтение файла и заполнение мэп Symbols
void HEncode::readFile( string filename ) {
    ifstream myFile( filename.c_str() );
    while ( true ) {
        byte temp;
        temp = (byte) myFile.get();
        if (!myFile.good())
            break;

        // если элемента нет в мэпе, то добавляем этот элемент
        auto pos = Symbols.find(temp);
        if (pos == Symbols.end()) {
            Symbols.insert(pair<char, int>(temp, 1));
        } else {
            // присваивание нового значения по существующему ключу
            Symbols.at(temp) = pos->second + 1;
        }
    }

    initList( Symbols );
    initSymbolsBit( Symbols );
}

// функция высчитывает путь в двоичном виде
void HEncode::treeWayToBin(Hnode *tree, string binCode) {
//    for( auto iter : SymbolsBit ){
//        cout << iter.first << " : " << iter.second << " " << endl;
//    }

    if (!tree->left and !tree->right)
        SymbolsBit.at(tree->ch) = binCode;

    if (tree->left)
        treeWayToBin(tree->left, binCode+"0");

    if (tree->right)
        treeWayToBin(tree->right, binCode+"1");
}

void HEncode::huffTree( ) {
    if( List.size() <= 1 ){
        cout << "error size" << endl;
        return;
    } else {
        while ( List.size() > 1 ){
            // Берем 2 наименьших значения
            auto tmp1 = List[List.size() - 1];
            auto tmp2 = List[List.size() - 2];
            List.pop_back();
            List.pop_back();

            Hnode *node1 = tmp1;
            Hnode *node2 = tmp2;

            Hnode *huff = new Hnode( node1, node2, node1->count + node2->count );
            List.push_back(huff);
            sort( List.begin(), List.end(), less_first2<Hnode*, Hnode*>() );
        }

        string blank = "";
        treeWayToBin( List.back(), blank );

    }
}

// Проходим по всему тексту, преобразуя каждую букву в двоичный символ и считаем колличество бит
string HEncode::encode(string filename) {
    numBits = 0;
    string bits;
    ifstream myFile( filename.c_str() );
    while (true){
        byte temp;
        temp = myFile.get();
        if (!myFile.good())
            break;
        auto tmp = SymbolsBit.find(temp);
        // auto tmp2 = Symbols.find(temp);
        bits += tmp->second;
        numBits += tmp->second.size();
    }

    myFile.close();
    return bits;
}

// записываем дерево Хаффмана в файл
void HEncode::printTree(Hnode *tree, ofstream &ostr) {
    assert(tree);
    if (!tree->right and !tree->left)
        ostr << 'L' << tree->ch;

    else if (tree->right and tree->left){
        ostr << 'N';
        printTree(tree->left, ostr);
        printTree(tree->right, ostr);
    }
}

void HEncode::writeZipFile( string originFileName, string zipFileName) {
    string bits = encode( originFileName );
    string newFile = zipFileName;
    //newFile = newFile + ".huf";
    ofstream out(newFile.c_str());
    out << numBits;
    printTree( List.back(), out);
    while (bits.size() % 8 != 0)   //дописываем строку нулями, что бы она была кратна байту
        bits += '0';
    for (size_t i=0;i<bits.size();i+=8){
        out << bitStrToChar(bits.substr(i, 8));
    }
    out.close();
}


byte HEncode::bitStrToChar(string s) {
    char total = 0;
    char val = 1;
    for (int i=7;i>=0;i--){
        total += (s[i] - '0') * val;
        val = val *2;
    }

    return total;
}


class HDecode{
public:
    string fileText;

    void fileToStr( string filename );
    Hnode *buildTreeByFile( stringstream & stringStream );  // Рекрсивно парсим строку и восстанавливаем дерево
    Hnode *fileParse( string textData );    // восстанавливаем дерево Хаффмана из строки
    void treeWayToBinDecode( Hnode *tree, string code );    // чтения бинарного дерева для получения пар < символ, путь в дереве >
    string charToBitStr(unsigned char c, string byte, size_t bitval);   // Преобразование символов в строку бит
    string makeBitStr( string filename );   // получаем последовательность всех символов текстового файла в бинарном виде
    void restoreText( string newFileName, string bitStr,  Hnode* tree ); // Окончательное восстановление сжатого текста

private:
    map<char, string> SymbolsBitDecode;   // хранит в себе пары <буква, путь в дереве> для декодирования
    int numBits;
    int position;
};

void HDecode::fileToStr(string filename) {
// обнуляем переменную fileText
    fileText = "";
    ifstream zipStream(filename.c_str());
    while(true){
        byte temp;
        temp = zipStream.get();
        if (!zipStream.good()){
            break;
        }
        fileText += temp;
    }
 //   cout << "filetext = " << fileText << endl;
}

// Рекрсивно парсим строку и восстанавливаем дерево
Hnode *HDecode::buildTreeByFile(stringstream &stringStream) {
    char temp;
    stringStream.get(temp);
    if (temp ==  'N'){
        return new Hnode( buildTreeByFile(stringStream), buildTreeByFile(stringStream) );
    }
    else if (temp == 'L'){
        char newChar;
        stringStream.get(newChar);
        return new Hnode(newChar);
    }
    return NULL;
}

// восстанавливаем дерево Хаффмана из строки
Hnode *HDecode::fileParse(string textData) {
    numBits = 0;
    position = 0;

    stringstream stringStream (stringstream::in | stringstream::out);
    stringStream << textData;   // в конец строки записываем textData
    stringStream >> numBits;   //считываем сначала строки колличество записанных в него бит
    Hnode * tree = buildTreeByFile( stringStream );  // восстанвливаем дерево
    position = stringStream.tellg();

    return tree;
}

// чтения бинарного дерева для получения пар < символ, путь в дереве >
void HDecode::treeWayToBinDecode(Hnode *tree, string code) {
    if (!tree->left and !tree->right){
        SymbolsBitDecode.insert( pair<char, string>(tree->ch, code) );
    }

    if (tree->left)
        treeWayToBinDecode( tree->left, code+"0" );

    if (tree->right)
        treeWayToBinDecode( tree->right, code+"1" );
}

// Преобразование символов в строку бит
string HDecode::charToBitStr(unsigned char c, string byte, size_t bitval) {
    if (byte.size() == 8)
        return byte;
    else if (c >= bitval){
        byte+="1";
        return charToBitStr(c-bitval,byte,bitval/2);
    }
    else if (c < bitval){
        byte+="0";
        return charToBitStr(c,byte,bitval/2);
    }
    return "";
}

string HDecode::makeBitStr(string filename) {
    string bits = "";
    ifstream zipFile(filename.c_str());
    zipFile.seekg( position );   // получаем позицию начала текстовых данных
    while (true){
        byte temp;
        temp = zipFile.get();
        if (!zipFile.good())
            break;
        string byte = "";
        bits += charToBitStr( temp, byte, 128 );  // формирование строки символов в бинарном виде
    }
    return bits.substr(0, numBits);  // записываем в начало колличество бит
}

void HDecode::restoreText(string newFileName, string bitStr, Hnode *tree) {
    stringstream ss ( stringstream::in | stringstream::out );
    ss << fileText;
    ss.seekg( position - 1 );
    ofstream restoreText( newFileName.c_str() );
    Hnode *currentNode = tree;
    size_t i = 0;

    //goes through bitStr and traverses the tree to find each decoded character
    while ( i < bitStr.size() ){
        if (!currentNode->right and !currentNode->left){
            restoreText << currentNode->ch;
            currentNode = tree;
        }
        else if (bitStr[i] == '0'){
            currentNode = currentNode->left;
            i++;
        }
        else if (bitStr[i] == '1'){
            currentNode = currentNode->right;
            i++;
        }
    }
    restoreText << currentNode->ch;
}



  
void Encode( CInputStream& original, COutputStream& compressed ){
    HEncode inputStream;

    inputStream.readFile( original.inputFileName);
    inputStream.huffTree();
    inputStream.bits = inputStream.encode( original.inputFileName );
    inputStream.writeZipFile( original.inputFileName, compressed.outputFileName );
}
void Decode( COutputStream& compressed, CInputStream& original ){
    HDecode outputStream;
    string file = compressed.outputFileName;

    outputStream.fileToStr( file );
    Hnode *tree = outputStream.fileParse( outputStream.fileText );
    string binCodeText = "";       // binCodeText хранит бинарные значения символов (пути до символов в дереве)
    outputStream.treeWayToBinDecode( tree, binCodeText );   // получение значений символов в бинарном виде
    string bitStr = outputStream.makeBitStr( file );        // получаем строку состоящую из колличесва символов и последовательности
    // символов в виде набора бит
    string newFileName = original.inputFileName;
    outputStream.restoreText( newFileName, bitStr, tree );
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


// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <map>
// #include <functional>
// #include <queue>
// #include <string>
// #include "Huffman.h"
// struct DereferenceCompareNode;
// class Tree;
// class TreeNode;

// class TreeNode{                         //  узел дерева
// private:
//     int data;
//     char character;
//     TreeNode* Left;                     //  указатель на левого потомка
//     TreeNode* Right;                    //  указатель на правого потомка 
// public:
//     int get_data(){return data;}        //  возвращает значение 
//     void set_data(int val){ this->data = val;}

//     char get_character() {return character;}
//     void set_character(char character) {this->character = character;}

//     void set_right(TreeNode* val) {     //  меняем значение левого потомка 
//         this->Right = val;
//     };
//     void set_left(TreeNode* val){       // меняем занчение правого потомка
//         this->Left = val;
//     };
   
//     TreeNode* get_left(){return Left;}      //  считываем занчение левого потомка
//     TreeNode* get_right(){return Right;}    //  считываем значение правого потомка
//     TreeNode() {
//         this->data = 0;
//         this->character = '\0';
//         this-> Left = NULL;
//         this->Right = NULL;
//     }
//     TreeNode(int input_data, char c): data(input_data), character(c), Left(NULL), Right(NULL){}; // конструктор для корневой вершины
 
// };
 
// std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck; 
// class Tree {                            //  дерево узлов
// private: 
    
//     TreeNode* root;                     //  необходимо знать корневую ноду
//     std::vector<int> ResultOfPreOrder;  //  вектор хранения результатов 

// public:

    
//     Tree(){
//         root = NULL;
//     }               // конструктор по умолчанию

//     Tree(int val,  char c){
//         root = new TreeNode(val, c);       //  конструктор 
//     }

//     TreeNode* get_root() {
//         return root;
//     }

//     Tree(Tree* left, Tree *right) {
//         this->root = new TreeNode();
//         this->root->set_data(left->get_root()->get_data() + right->get_root()->get_data());
//         this->root->set_left(left->get_root());
//         this->root->set_right(right->get_root());
//         this->root->set_character('\0');
//     }

// }; 

// struct DereferenceCompareNode : public std::binary_function<Tree*, Tree*, bool> {
//     bool operator()(Tree* lhs, Tree* rhs) const {
//         return lhs->get_root()->get_data() > rhs->get_root()->get_data();
//     }
// }; 



// void bild_table(TreeNode* Node, std::string &Buf, std::string* result) {
//     if (Node->get_character() != '\0') {
//         result[(int)Node->get_character()] = Buf;
//     }
//     if (Node->get_left()){
//         bild_table(Node->get_left(), Buf.append("0"), result);
//         Buf = Buf.substr(0, Buf.size()-1);
//     }
//     if(Node->get_right()){
//         bild_table(Node->get_right(), Buf.append("1"), result);
//         Buf = Buf.substr(0, Buf.size()-1);
//     }
    
// }

// std::string* bild_table(Tree* tree) {
//     TreeNode* Node = tree->get_root();
//     std::string* result = new std::string[256];
//     std::string Buf = "";
//     bild_table(Node, Buf, result); 
//     return result;
// }


// template<typename T> void print_queue(T& q) {
//     while(!q.empty()) {
//        std::cout << q.top()->get_root()->get_character() << " " <<  q.top()->get_root()->get_data() << std::endl;
//         q.pop();
//     }
//     std::cout << '\n';
// }

// void Encode(CInputStream& input, COutputStream& output){
//     int mass[256] = {0};
//     std::vector<char> wer;
//     unsigned char c = 0;
// 	while (!input.Read(c)) { 
//         mass[c]++;
//         wer.push_back(c);
//     }
//     // std::priority_queue<Tree*, std::vector<Tree*>, DereferenceCompareNode> nodesToCheck;
//     for(int i = 0; i < 256; i++ ) 
//     {
//         if ( mass[i] != 0 ){
//             nodesToCheck.push(new Tree(mass[i], (char)i));
//         }
//     }
//     while(nodesToCheck.size() > 1){
//         Tree* a = nodesToCheck.top();
//         nodesToCheck.pop();
//         Tree* b = nodesToCheck.top();
//         nodesToCheck.pop();
//         nodesToCheck.push(new Tree(a, b));
//     }
  
//     std::string* table_code = bild_table(nodesToCheck.top());


//     int count = 0; char buf = 0;
//     while (!input.Read(c)) { 
//         std::vector<bool> x;
//         for (int i = 0; i < table_code[(int)c].length(); i++) {
//             if (table_code[(int)c][i] == '1') {
//                 x.push_back(1);
//             } else {
//                 x.push_back(0);
//             }
//         }
//         for(int n = 0; n < x.size(); n++) {
//             buf = buf | x[n] << (7 - count);   
//             count++;   
//             if (count == 8) { 
//                 count=0;   
//                 output.Write(buf); 
//                 buf=0;
//             }
//         }
//     } 
// }
// void Decode( COutputStream& output, CInputStream& input)  {
//     //std::ifstream F("output.txt", std::ios::in | std::ios::binary);
//     TreeNode *PTR = nodesToCheck.top()->get_root();
//     int count = 0; 
//     char byte; 
// 	while(!input.Read(byte))
// 	{   bool b = byte & (1 << (7 - count)) ; 
// 		if (b) PTR=PTR->get_right(); 
//         else PTR=PTR->get_left();
// 		if (PTR->get_left() == NULL && PTR->get_right() == NULL) {
//             //std::cout<<PTR->get_character(); 

//             output.Write(PTR->get_character());

//             PTR=nodesToCheck.top()->get_root();
//         }  
// 		count++;
// 		if (count==8) {
//             count=0; 
//             byte = output.Read(); 
//         }
// 	}
    
	
//}
