#include <iostream>
#include <queue>
//TODO: use 5 rule
class AvlNode {  //узел дерева 
private:
    int val;            //  рост военнослужащего 
    int hight;          //  высота узла 
    AvlNode* left;      //  ссылка на левого потомка
    AvlNode* right;     //  ссылка на правого потомка
    int pos_nod;        //  позиция военнослужащего в строю (1, 2, 3 и тд)
public:

    AvlNode(const int& v): val(v), hight(1), pos_nod(1), left(NULL), right(NULL) {};

    int get_val() { return val; }
    AvlNode* get_left() {
        return left;
    }
    AvlNode* get_right() {
        return right;
    }
    void set_left(AvlNode* left) {
        this->left = left;
    }
    void set_right(AvlNode* right) {
        this->right = right;
    }
    int get_hight() {
        return hight;
    }
    void set_hight(int h) {
        this->hight = h;
    }
    void set_position(int val) {
        this->pos_nod = val;
    }
    int get_position() {    
        return pos_nod;
    }
};

class AvlTree {
private:
    AvlNode* root;

    AvlNode* insert( const int &v, int & position, AvlNode* PTR) {// вставка ключа k в дерево с корнем p
        if(!PTR) return new AvlNode(v);
        PTR->set_position(PTR->get_position() + 1 );
        if(v < PTR->get_val()){
            position = position + CountOfNod(PTR->get_right()) + 1;
            PTR->set_left(insert(v,position,PTR->get_left())) ;
        } else {
            PTR->set_right(insert(v,position,PTR->get_right()));
        }
        return balance_tree(PTR);
    }

    AvlNode* rotateright(AvlNode* PTR) {    // правый поворот вокруг ноды
        AvlNode* NEW_PTR = PTR->get_left();

        PTR->set_left(NEW_PTR->get_right());
        NEW_PTR->set_right(PTR);


        fixpos(PTR);
        fixpos(NEW_PTR);

        fixheight(PTR);
        fixheight(NEW_PTR);

        return NEW_PTR;
    }

    AvlNode* rotateleft(AvlNode* PTR) {     // левый поворот вокруг ноды
        AvlNode* NEW_PTR = PTR->get_right();

        PTR->set_right(NEW_PTR->get_left());
        NEW_PTR->set_left(PTR);

        fixpos(PTR);
        fixpos(NEW_PTR);

        fixheight(PTR);
        fixheight(NEW_PTR);

        return NEW_PTR;
    }

    int height(AvlNode* PTR) {
        return (PTR?PTR->get_hight():0);
    }

    void fixheight(AvlNode* PTR) {          //  перерасчет высоты узла 
        int h_left = height(PTR->get_left());
        int h_right = height(PTR->get_right());
        PTR->set_hight((h_left>h_right?h_left:h_right)+1);
    }


    int bfactor(AvlNode* PTR) {
        return height(PTR->get_right())-height(PTR->get_left());
    }

    AvlNode* balance_tree(AvlNode* PTR) {    // балансировка ноды 
        fixpos(PTR);
        fixheight(PTR);

        if(bfactor(PTR) == 2) {
            if(bfactor(PTR->get_right()) < 0)
                PTR->set_right(rotateright(PTR->get_right()));
            return rotateleft(PTR);
        } else if(bfactor(PTR) == -2) {
            if (bfactor(PTR->get_left()) > 0 )
                PTR->set_left(rotateleft(PTR->get_left()));
            return rotateright(PTR);
        }
        return PTR; // балансировка не нужна
    }

    //delete tree need

    AvlNode* deletmin(AvlNode* PTR, AvlNode** min) { // удаление узла с минимальным ключом из дерева 
        if(PTR->get_left() == NULL){
            *min = PTR;
            return PTR->get_right();
        }

        PTR->set_left(deletmin(PTR->get_left(), min));
        PTR->set_position(PTR->get_position() - 1);
    	return balance_tree(PTR);
       
    }

    void delet(int position) {
        if (root->get_position() <= position || Empty()) return; //

        root = delet( position, root);
    }

    AvlNode* delet( int position, AvlNode* PTR) { // удаление ключа по заданной позиции
        if (PTR == NULL)  return 0;
    	int pos = position - CountOfNod(PTR->get_right());
        if (pos > 0) {
            PTR->set_left(delet(pos - 1, PTR->get_left()));
        } else if( pos < 0) {
            PTR->set_right(delet(position, PTR->get_right()));
        } else {
            AvlNode* PTR_left = PTR->get_left();
            AvlNode* PIR_right = PTR->get_right();
            delete PTR;

            if( !PIR_right ) return PTR_left;

            AvlNode* min;
            AvlNode* right = deletmin(PIR_right, &min);

            min->set_right(right);
            min->set_left(PTR_left);
            return balance_tree(min);
        }
        PTR->set_position(PTR->get_position() - 1 );
        return balance_tree(PTR);
    }

    int CountOfNod(AvlNode *PTR) {
        return PTR ? PTR->get_position(): 0;
    }

    void fixpos(AvlNode *PTR) {
        int pos_l = CountOfNod(PTR->get_left());
        int pos_r = CountOfNod(PTR->get_right());
        PTR->set_position(pos_l + pos_r + 1);
    }
public:
    AvlTree(): root(NULL) {};

    int add(const int &v) {  //int Add от трех параметр и подстчет позиции 
        int position = 0;
        root = insert(v, position, root);
        return position;
    }

    bool Empty() {
        return root == NULL;
    }

    void del(int v) {
        root =  delet(v, root);
    }

    void inorder(AvlNode* t) {
        if(t == NULL)
            return;
        inorder(t->get_left());
        std::cout << t->get_val() << " ";
        inorder(t->get_right());
    }
    ~AvlTree() {
        if( root != NULL ) {
            std::queue<AvlNode*> listofnods;
            listofnods.push(root);
            while( listofnods.size() != 0 ) {
                if (listofnods.front()->get_left() != NULL) {
                    listofnods.push(listofnods.front()->get_left());
                }
                if (listofnods.front()->get_right() != NULL) {
                    listofnods.push(listofnods.front()->get_right());
                }
                delete listofnods.front();
                listofnods.pop();
            }
        }
    }

};


int main() {
    AvlTree Tree;
    int count_of_comand = 0;
    std::cin >> count_of_comand;
 
    while (count_of_comand--){
        int command = 0,
                value = 0;
        std::cin >> command >> value;
        switch(command){
            case 1:
                std:: cout << Tree.add(value) << std::endl;
                break;
            case 2:
                Tree.del(value);
                break;
            default:
                std::cout << "Error command\n";
        }
    }
    
    return 0;
}