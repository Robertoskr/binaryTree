//generic binary tree
#include "../stacks/stack.h"
#include "../queues/queue.h"
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
template<class T>
class BTNode{
public:
    BTNode(){
        left = right = 0;
    }
    BTNode(const T& e, BTNode<T> *l = 0, BTNode<T> *r = 0){
        el = e; left = l; right = r;
    }
    T el;
    BTNode<T> *left, *right;
};
template<class T>
class BST{
public:
    BST(){root = 0;}
    ~BST(){clear();}
    void clear(){
        clear(root);
        root = 0;
    }
    bool isEmpty() const{
        return root == 0;
    }
    void preorder(){
        preorder(root);
    };
    void inorder(){
        inorder(root);
    };
    void postorder(){
        postorder(root);
    };
    T* search(const T& el) const {
        return search(root, el);
    };
    void breadthFirst();
    void iterativePreorder();
    void iterativeInorder();
    void iterativePostorder();
    void MorrisInorder();
    void insert(const T&);
    void deleteByMerging(BTNode<T>*&);
    void findAndDeleteByMerging(const T&);
    void deleteByCopying(BTNode<T>*&);
    void balance(T*, int, int);
protected:
    BTNode<T>* root;
    void clear(BTNode<T>*);
    T* search(BTNode<T>*, const T&) const;
    void preorder(BTNode<T>*);
    void inorder(BTNode<T>*);
    void postorder(BTNode<T>*);
    virtual void visit(BTNode<T>* p){
        cout << p->el << ' ';
    }
};
template<class T>
void BST<T>::clear(BTNode<T>* p){
    p = 0;
}
//searching a binary seach tree
/*an algo for location an element in this tree is quite straightforward, as indicated by its implementation
for every node we compare the element to be located with the value stored in the node if the element is less than the value 
to to the left subtree and try again, if its greater than the node the right subtree*/ 
template<class T> 
T* BST<T>::search(BTNode<T>* p, const T& el) const {
    while(p != 0){ //while the pointer dont point to null
        if(el == p->el)
            return &p->el;
        else if(el < p->el)
            p = p->left;
        else p = p->right;
    }
    return 0;
}
//tree traversal
//breadth first traversal is visiting each node starting from the lowest or highest level and moving down or up
//implemetation of this kind of traversal is straightforwar when a queue is used
template<class T>
void BST<T>::breadthFirst(){
    Queue<BTNode<T>*> queue;
    BTNode<T>* p = root;
    if(p!=0){
        queue.enqueue(p);
        while(!queue.isEmpty()){
            p = queue.dequeue();
            visit(p);
            if(p->left != 0)
                queue.enqueue(p->left);
            if(p->right != 0)
                queue.enqueue(p->right);
        }
    }
};
//deph first traversal
//proceds as far as posible to the left then backs up until the first crossroad goes one steo to the right
/*VLR—preorder tree traversal
LVR—inorder tree traversal
LRV—postorder tree traversal
these are the types of tree treversal*/
template<class T>
void BST<T>::inorder(BTNode<T>* p){
    if(p!= 0){
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}
template<class T>
void BST<T>::preorder(BTNode<T>* p){
    if(p != 0){
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}
template<class T>
void BST<T>::postorder(BTNode<T>* p){
    if(p!=0){
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}
//a non recursive implementation of the postorder tree traversal
template<class T>
void BST<T>::iterativePreorder(){
    Stack<BTNode<T>*> travStack;
    BTNode<T> *p = root;
    if(p != 0){
        travStack.insert(p);
        while(!travStack.isEmpty()){
            p = travStack.pop();
            visit(p);
            if(p->right != 0)
                travStack.insert(p->right); //right inserted first because the left needs to be poped first
            if(p->left != 0)
                travStack.insert(p->left);
        }
    }
}
template<class T>
void BST<T>::iterativePostorder(){
    Stack<BTNode<T>*> travStack;
    BTNode<T> *p = root, *q = root;
    if(p != 0){
        travStack.insert(p);
        for( ; p->left != 0 ; p = p->left)
            travStack.insert(p);
        while(p->right == 0 || p->right == q){
            visit(p);
            q = p;
            if(travStack.isEmpty())
                return;
            p = travStack.pop();
        }
        travStack.insert(q);
        p = p->right;
        };
};
//stackless depth first traversal
//morrris inorder
template<class T>
void BST<T>::MorrisInorder(){
    BTNode<T> *p = root, *tmp;
    while(p != 0)
        if(p->left == 0){
            visit(p);
            p = p->right;
        }
        else{
            tmp = p->left;
            while(tmp->right != 0 && tmp->right != p)
                tmp = tmp->right;
            if(tmp->right == 0){
                tmp->right = p;
                p = p->left;
            }
            else{
                visit(p);
                tmp->right = 0;
                p = p->right;
            }
        }
}
//insertion , seaarching in a binary tree does not modify the tree 
//implementation of insertion algorithm
template<class T>
void BST<T>::insert(const T& el){
    BTNode<T> *p = root, *prev = 0;
    while(p != 0){ // find a place for inserting a new node
        prev = p;
        if(el < p->el)
            p = p->left;
        else p = p->right;
    }
    if(root == 0) // tree is empty
        root = new BTNode<T>(el);
    else if(el < prev->el)
        prev->left = new BTNode<T>(el);
    else prev->right = new BTNode<T>(el);
}
//deletetion
//there are few types of deleting 
//deletion by mergin
template<class T>
void BST<T>::deleteByMerging(BTNode<T>*& node){
    BTNode<T> *tmp = node;
    if(node != 0){
        if(!node->right){
            node = node->left; //node has no right child
        }
        else if(node->left == 0)
            node = node->right; //node has no left childs, its right child is atached to its parent
        else{
            tmp = node->left;
            while(tmp->right != 0){
                tmp = tmp->right;
            }
            tmp->right = node->right;
            tmp = node;
            node = node->left;
        }
        delete tmp;
    }
}
template<class T>
void BST<T>::findAndDeleteByMerging(const T& el){
    BTNode<T> *node = root, *prev = 0;
    while(node != 0){
        if(node->el == el)
            break;
        prev = node;
        if(el < node->el)
            node = node->left;
        else
            node = node->right;
    }
    if (node != 0 && node->el == el){
        if(node == root)
            deleteByMerging(root);
        else if(prev->left == node)
            deleteByMerging(prev->left);
        else deleteByMerging(prev->right);
    }else if(root != 0)
        cout << "Element " << el << " is not in the tree\n";
    else cout << "The tree is empty";
}
//deletetion by copiyng
template<class T>
void BST<T>::deleteByCopying(BTNode<T>*& node){
    BTNode<T> *previous, *tmp = node;
    if(node->right == 0)
        node = node->left;
    else if(node->left == 0){
        node = node->rigth;
    }
    else{
        tmp = node->left;
        previous = node;
        while(tmp->right != 0){
            previous = node;
            tmp = tmp->right;
        }
        node->el = tmp->el;
        if(previous == node)
            previous->left = tmp->left;
        else previous->right = tmp->left;
    }
    delete tmp;
}
//balancing a tree
template<class T>
void BST<T>::balance(T data[], int first, int last){
    if(first <= last){
        int middle = (first + last) / 2;
        insert(data[middle]);
        balance(data, first, middle-1);
        balance(data, middle+1, last);
    }
}
//the dsw algorithm, the algorithm discussed in the previous chapter was somewhat inneficient

#endif