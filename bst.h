#ifndef BST_H
#define BST_H

typedef int Type;
typedef struct BSTreeNode{
    Type key;
    BSTreeNode* left;
    BSTreeNode* right;
    BSTreeNode* parent;
} Node, *BSTree;


Node* create_bstree_node(Type key, Node* parent, Node* left, Node* right)
{
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p)
        return NULL;
    p->key = key;
    p->parent = parent;
    p->left = left;
    p->right = right;
    return p;
}

//前序遍历
void preorder_bstree(BSTree tree)
{
    if (tree)
    {
        printf("%d", tree->key);
        preorder_bstree(tree->left);
        preorder_bstree(tree->right);
    }
}

void inorder_bstree(BSTree tree)
{
    if (tree)
    {
        inorder_bstree(tree->left);
        printf("%d", tree->key);
        inorder_bstree(tree->right);
    }
}

void postorder_bstree(BSTree tree)
{
    if (tree)
    {
        postorder_bstree(tree->left);
        postorder_bstree(tree->right);
        printf("%d", tree->key);
    }
}

Node* bstree_search(BSTree tree, Type key)
{
    if (!tree || key == tree->key)
        return tree;
    if (key < tree->left)
        return bstree_search(tree->left, key);
    else
        return bstree_search(tree->right, key);
}

Node* iterative_bstree_search(BSTree tree, Type key)
{
    while (tree && tree->key != key)
    {
        if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

Node* bstree_maximnum(BSTree tree)
{
    if (!tree)
        return tree;
    while (tree->right)
        tree = tree->right;
    return tree;
}

Node* bstree_minimun(BSTree tree)
{
    if (!tree)
        return tree;
    while (tree->left)
        tree = tree->left;
    return tree;
}

Node* bstree_insert(BSTree tree, Node *z)
{
    Node* x = tree;
    Node* y = NULL;
    while(!x)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (!y)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    return tree;
}

Node* insert_bstree(BSTree tree, Type key)
{
    Node* z = NULL;
    if (z = create_bstree_node(key, NULL, NULL, NULL))
        return bstree_insert(tree, z);
    return tree;
}

#endif // BST_H

