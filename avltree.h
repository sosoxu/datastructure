#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "bstree.h"

template<typename T>
class AVLTreeNode : public BSTNode<T>
{
public:
	int factor; //Æ½ºâÒò×Ó
public:
	AVLTreeNode(T val, AVLTreeNode* parent = NULL, AVLTreeNode* left = NULL, AVLTreeNode* right = NULL, int factor = 0)
		:BSTNode(val, parent, left, right), factor(factor){}
};

template<typename T, typename Visitor = BSTreeVisitor<T> >
class AVLTree : public BSTree<T, Visitor>
{
public:
	typedef AVLTreeNode<T> AVLNode;
public:
	virtual Node* createNode(T val){ return new AVLNode(val); }

	virtual void insert(T key);
	virtual void insertNode(Node*& node, Node* z);
	virtual Node* remove(Node*& node, Node* z);

public:
	static void llrotate(AVLNode* node);
	static void rrrotate(AVLNode* node);
	static void lrrotate(AVLNode* node);
	static void rlrotate(AVLNode* node);
};

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::insert( T key )
{
	Node* z = createNode(key);
	if (z)
	{
		insertNode(m_root, z);

		//
	}
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::llrotate( AVLNode* node )
{
	AVLNode* b = node->left;
	node->left = b->right;
	b->right = node;
	node->factor = b->factor = 0;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::rrrotate( AVLNode* node )
{

}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::lrrotate( AVLNode* node )
{
	AVLNode* b, *c;
	b = node->left;
	c = b->right;
	b->right = c->left;
	c->left = b;
	node->left = c->right;
	c->right = node;
	if (c->factor == 1)
	{
		node->factor = -1;
		b->factor = 0;
	}
	else if (c->factor == 0)
	{
		node->factor = b->factor = 0;
	}
	else
	{
		node->factor = 0;
		b->factor = 1;
	}
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::rlrotate( AVLNode* node )
{

}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* AVLTree<T, Visitor>::remove( Node*& node, Node* z )
{
	return NULL;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::insertNode( Node*& node, Node* z )
{
	//BSTree<T, Visitor>::insertNode(node, z);
	AVLNode* x = static_cast<AVLNode* >(z);
	if (!node)
	{
		node = z;
		x->factor = 1;
		return;
	}
	AVLNode* a, *b, *c, *d;

}


#endif