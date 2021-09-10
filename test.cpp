#include "genBST.h"


int main(){
    BST<int> tree;
    tree.insert(1);
    tree.insert(6);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    tree.insert(8);
    tree.insert(12);
    tree.insert(11);
    tree.insert(9);
    tree.inorder();
    tree.findAndDeleteByMerging(11);
    tree.inorder();
}