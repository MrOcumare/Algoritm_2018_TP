#include <iostream>
//TODO: use 5 rule
class AvlNode {
private:
    int val;
    int hight;
    AvlNode* left;
    AvlNode* right;
public:
    AvlNode(int v): val(v), hight(1), left(NULL), right(NULL) {};
    int get_val() {
        return val;
    }
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
    
};

class AvlTree {
private:
    AvlNode* root;
    AvlNode* insert( int v, AvlNode* PTR) {// вставка ключа k в дерево с корнем p
        if(!PTR) return new AvlNode(v); 
        if(v < PTR->get_val())
            PTR->set_left(insert(v,PTR->get_left())) ;
        else
            PTR->set_right(insert(v,PTR->get_right()));
        return balance_tree(PTR);
    }

    AvlNode* balance_tree(AvlNode* PTR) { // балансировка узла p
        fixheight(PTR);
        if(bfactor(PTR)==2) {
            if(bfactor(PTR->get_right()) < 0)
                PTR->set_right(rotateright(PTR->get_right()));
            return rotateleft(PTR);
        }
        if(bfactor(PTR)==-2) {
            if(bfactor(PTR->get_left()) > 0 )
                PTR->set_left(rotateleft(PTR->get_left()));
            return rotateright(PTR);
        }
        return PTR; // балансировка не нужна
    }

    int bfactor(AvlNode* PTR) {
	    return height(PTR->get_right())-height(PTR->get_left());
    }

    int height(AvlNode* PTR) {
	    return PTR?PTR->get_hight():0;
    }

    void fixheight(AvlNode* PTR) {
        int h_left = height(PTR->get_left());
        int h_right = height(PTR->get_right());
        PTR->set_hight((h_left>h_right?h_left:h_right)+1);
    }

    AvlNode* rotateright(AvlNode* PTR) {// правый поворот вокруг p
        AvlNode* NEW_PTR = PTR->get_left();
        PTR->set_left(NEW_PTR->get_right());
        NEW_PTR->set_right(PTR);
        fixheight(PTR);
        fixheight(NEW_PTR);
        return NEW_PTR;
    }

    AvlNode* rotateleft(AvlNode* PTR) {// левый поворот вокруг q
    
        AvlNode* NEW_PTR = PTR->get_right();
        PTR->set_right(NEW_PTR->get_left());
        NEW_PTR->set_left(PTR);
        fixheight(PTR);
        fixheight(NEW_PTR);
        return NEW_PTR;
    }

    AvlNode* findmin(AvlNode* PTR) { // поиск узла с минимальным ключом в дереве p 
        return PTR->get_left()?findmin(PTR->get_left()):PTR;
    }

    AvlNode* deletmin(AvlNode* PTR) { // удаление узла с минимальным ключом из дерева p
        if(PTR->get_left() == 0)
            return PTR->get_right();
        PTR->set_left(deletmin(PTR->get_left()));
        return balance_tree(PTR);
    }

    AvlNode* delet( int v, AvlNode* PTR) { // удаление ключа k из дерева p

        if(!PTR) return 0;
        if(v < PTR->get_val())
            PTR->set_left(delet(v, PTR->get_left()));
        else if( v > PTR->get_val() )
            PTR->set_right(delet(v, PTR->get_right()));	
        else //  k == p->key 
        {
            AvlNode* PTR_left = PTR->get_left();
            AvlNode* PIR_right = PTR->get_right();
            delete PTR;
            if( !PIR_right ) return PTR_left;
            AvlNode* PTR_min = findmin(PIR_right);
            PTR_min->set_right(deletmin(PIR_right));
            PTR_min->set_left(PTR_left);
            return balance_tree(PTR_min);
        }	
        return balance_tree(PTR);
    }
public:
    AvlTree(): root(NULL) {};
    void add(int v) {
        root = insert(v, root);
    }
    void del(int v) {
        root =  delet(v, root);
    }

    void inorder(AvlNode* t)
    {
        if(t == NULL)
            return;
        inorder(t->get_left());
        std::cout << t->get_val() << " ";
        inorder(t->get_right());
    }
    AvlNode* get_root() {
        return root;
    }
};


int main() {
    AvlTree Tree;
    int count_of_comand = 0;
    std::cin >> count_of_comand;
    assert(count_of_comand >= 0);
    while (count_of_comand--){
        int command = 0, 
            value = 0;
        std::cin >> command >> value;
        switch(command){
            case 1:
                Tree.add(value);
                break;
            case 2:
                Tree.del(value);
                break;
            default:
                std::cout << "Error command\n";
        }
    }
    Tree.inorder(Tree.get_root());
    return 0;
}