
#include <iostream>


class Node   
{
public:
    long content;
    Node *next_node;
 
    Node(long item, Node *next){
        content = item, next_node = next;
    }
};

Node* init_list(Node* tmp, long N, Node* first){
    for (long i = 2; i <= N; ++i) 
    {
        tmp->next_node = new Node(i, first);
        tmp = tmp->next_node;
    }
    return tmp;
}

long find_elem(Node* tmp, long k){
    while (tmp != tmp->next_node)    
    {
        for (long i = 1; i < k; ++i)
        {
            tmp = tmp->next_node;
        }
        Node *deleteNode = tmp->next_node;
        tmp->next_node = tmp->next_node->next_node;

        delete deleteNode;
    }
    return tmp->content;
}

long main()
{
    long N, k;
    std::cin >> N >> k;
    Node *first =new Node(1,  nullptr); 
    first->next_node = first;        
    Node *tmp = first;    
    tmp = init_list(tmp, N, first);

    std::cout << find_elem(tmp, k) << std::endl;  
}