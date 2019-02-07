#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int Key;
    int Height;
    int Number;
    
    Node* Left;
    Node* Right;
    Node(int key) : Key(key), Height(1), Left(0), Right(0), Number(1) {}
};

int Height(Node* node) {
    return node == 0 ? 0 : node->Height;
}

int BalanceFactor(Node* node) {
    return Height(node->Right) - Height(node->Left);
}

void FixHeight(Node* node) {
    int hleft = Height(node->Left);
    int hright = Height(node->Right);
    node->Height = ((hleft > hright) ? hleft : hright) + 1;
}

void FixNumber(Node * p) {
    p->Number = ((p->Right == 0) ? 0 : p->Right->Number) + ((p->Left == 0) ? 0 : p->Left->Number) + 1;
}

Node* RotateRight(Node* p) {
    Node* pR = p->Left;
    p->Left = pR->Right;
    pR->Right = p;
    
    FixNumber(p);
    FixNumber(pR);
    FixHeight(p);
    FixHeight(pR);
    return pR;
}

Node* RotateLeft(Node* p) {
    Node* pL = p->Right;
    p->Right = pL->Left;
    pL->Left = p;
    
    FixNumber(p);
    FixNumber(pL);
    FixHeight(p);
    FixHeight(pL);
    return pL;
}

Node* Balance(Node* p) {
    FixHeight(p);
    
    if (BalanceFactor(p) == 2) {
        if (BalanceFactor(p->Right) < 0)
            p->Right = RotateRight(p->Right);
        return RotateLeft(p);
    }
    
    if (BalanceFactor(p) == -2) {
        if (BalanceFactor(p->Left) > 0)
            p->Left = RotateLeft(p->Left);
        return RotateRight(p);
    }
    
    return p;
}

Node* Insert(Node* p, int key, int &pos) {
    if (p == 0) 
        return new Node(key);
    
    ++(p->Number);
    
    if( key < p->Key ) {
        pos += ((p->Right == 0) ? 0 : p->Right->Number) + 1;
        p->Left = Insert(p->Left, key, pos);
    } else
        p->Right = Insert(p->Right, key, pos);
    
    return Balance(p);
}

Node* FindMin(Node* p) {
    return p->Left == 0 ? p : FindMin(p->Left);
}

Node* RemoveMin(Node* p) {
    if( p->Left == 0 )
        return p->Right;
    
    p->Left = RemoveMin(p->Left);
    --p->Number;
    return Balance(p);
}

Node* Remove(Node* p, int position) {
    if (p == 0) 
    	return 0;

    if (position >= p->Number) 
    	return p;

    int sum = 0;
    stack<Node*> nodes;
    
    while (true) {
        int rightNumber = (p->Right == 0) ? 0 : p->Right->Number;
        
        if (position - sum > rightNumber) {
            nodes.push(p);
            p = p->Left;
            sum += rightNumber + 1;
        } else if (position - sum < rightNumber) {
            if (p->Right != 0) {
                nodes.push(p);
                p = p->Right; 
            } else break;
        } else {
            Node* left = p->Left;
            Node* right = p->Right;
            int key = p->Key;
            delete p;
            if (right == 0) {
                if (left == 0) {
                    if (!nodes.empty()) {
                        p = nodes.top();
                        nodes.pop();
                        
                        if (p->Key > key)
                            p->Left = 0;
                        else
                            p->Right = 0;
                        
                        --p->Number;
                    }
                    else return 0;
                }
                else
                    p = left;
            } else {
                Node* min = FindMin(right);
                min->Right = RemoveMin(right);
                min->Left = left;
                FixNumber(min);
                p = Balance(min);
            } 
            break;
        }
    }
    Node *p1;
    
    while (!nodes.empty()) {
        p1 = nodes.top();
        p1->Number--;

        if (p1->Key > p->Key)
            p1->Left = p;
        else
            p1->Right = p;
        
        p = Balance(p1);
        nodes.pop();
    }

    return p;
}

void Delete(Node* node) {
    if (!node) 
        return;
    Delete(node->Left);
    Delete(node->Right);
    delete node;
}





int main() {
    Node* root = 0;
    int n, key, position, operation;;
    cin >> n;
    vector<int> result;
    
    for (int i = 0; i < n; ++i) {
        cin >> operation;
        switch (operation) {
    	case 1:
        	position = 0;
            cin >> key;
            root = Insert(root, key, position);
            std::cout << position << std::endl;
            break;
        case 2:
            cin >> key;
            root = Remove(root, key);
        }
    }
    
    for (int i = 0; i < result.size(); ++i)
        cout << result[i] << endl;

    Delete(root);
    
    return 0;
}