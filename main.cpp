#include <iostream>
#include "bstree.h"

int main()
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.preorder(BSTreeVisitor<int>());
    tree.inorder(BSTreeVisitor<int>());
    tree.postorder(BSTreeVisitor<int>());
    return 0;
}

