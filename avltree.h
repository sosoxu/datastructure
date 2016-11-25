#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "bstree.h"
#include "utlity.h"

template<typename T>
class AVLTreeNode : public BSTNode<T>
{
public:
    int height;
public:
    AVLTreeNode(T val, AVLTreeNode* parent = NULL, AVLTreeNode* left = NULL, AVLTreeNode* right = NULL, int height = 0)
        :BSTNode<T>(val, parent, left, right), height(height){}
};

template<typename T, typename Visitor = BSTreeVisitor<T> >
class AVLTree : public BSTree<T, Visitor>
{
public:
	typedef AVLTreeNode<T> AVLNode;
    typedef typename BSTree<T, Visitor>::Node Node;
public:
    virtual Node* createNode(T val){ return new AVLNode(val); }

	virtual void insert(T key);
    virtual Node* insertNode(Node*& node, Node* z);
	virtual Node* remove(Node*& node, Node* z);

public:
    static int height(AVLNode* node) { 
		if (node)
			return node->height;
		else
			return 0;
	}
    static void updateHeight(AVLNode* node);
    static AVLNode* llrotate(AVLNode* node);
    static AVLNode* rrrotate(AVLNode* node);
    static AVLNode* lrrotate(AVLNode* node);
    static AVLNode* rlrotate(AVLNode* node);
	static AVLNode* avlNode2BSTNode(Node* node);
};

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::avlNode2BSTNode( Node* node )
{
	return static_cast<AVLNode*>(node);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::updateHeight(AVLNode* node)
{
	AVLNode* left = static_cast<AVLNode*>(node->left);
	AVLNode* right = static_cast<AVLNode*>(node->right);
	if (!left && !right)
		node->height = 1;
	else
		node->height = max(height(left), height(right)) + 1;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::insert( T key )
{
	Node* z = createNode(key);
	if (z)
	{
        insertNode(BSTree<T,Visitor>::m_root, z);
	}
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::llrotate( AVLNode* node )
{
    AVLNode* b = static_cast<AVLNode*>(node->left);
	node->left = b->right;
	b->right = node;

    updateHeight(node);
    updateHeight(b);
    return b;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::rrrotate( AVLNode* node )
{
    AVLNode* b = static_cast<AVLNode*>(node->right);
    node->right = b->left;
    b->left = node;

    updateHeight(node);
    updateHeight(b);
    return b;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::lrrotate( AVLNode* node )
{
    node->left = rrrotate(static_cast<AVLNode*>(node->left));
    return llrotate(node);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::rlrotate( AVLNode* node )
{
    node->right = llrotate(static_cast<AVLNode*>(node->right));
    return rrrotate(node);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* AVLTree<T, Visitor>::remove( Node*& node, Node* z )
{
	return NULL;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* AVLTree<T, Visitor>::insertNode( Node*& node, Node* z )
{
	AVLNode* x = static_cast<AVLNode* >(z);
    AVLNode* n = static_cast<AVLNode* >(node);
	if (!node)
	{
        node = z;
		n = static_cast<AVLNode* >(node);
    }
    else if (z->key < node->key)
    {
        node->left = insertNode(node->left, z);
        if (height(static_cast<AVLNode*>(node->left)) - height(static_cast<AVLNode*>(node->right)) == 2)
        {
            if (z->key < node->left->key)
                node = llrotate(n);
            else
                node = lrrotate(n);
			n = static_cast<AVLNode* >(node);
        }
    }
    else if (z->key > node->key)
    {
        node->right = insertNode(node->right, z);
        if (height(static_cast<AVLNode*>(node->right)) - height(static_cast<AVLNode*>(node->left)) == 2)
        {
            if (z->key > node->right->key)
                node = rrrotate(n);
            else
                node = rlrotate(n);
			n = static_cast<AVLNode* >(node);
        }
    }

    updateHeight(n);
    return node;
}


#endif
