#ifndef RBTREE_H_
#define RBTREE_H_

#include "bstree.h"

template<typename T>
class RBTreeNode : public BSTNode<T>
{
public:
	bool color; // 0 red;1 black
public:
	RBTreeNode(T val, RBTreeNode* parent = NULL, RBTreeNode* left = NULL, RBTreeNode* right = NULL, bool color = 0)
		:BSTNode<T>(val, parent, left, right), color(color){}
};

template<typename T, typename Visitor = BSTreeVisitor<T> >
class RBTree : public BSTree<T, Visitor>
{
public:
	typedef RBTreeNode<T> RBNode;
	typedef typename BSTree<T, Visitor>::Node Node;
public:
	virtual Node* createNode(T val){ return new RBTreeNode<T>(val); }

	virtual void insert(T key);
	virtual Node* insertNode(Node*& node, Node* z);
	virtual Node* remove(Node*& node, Node* z);
};

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void RBTree<T, Visitor>::insert( T key )
{

}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* RBTree<T, Visitor>::insertNode( Node*& node, Node* z )
{
	return NULL;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* RBTree<T, Visitor>::remove( Node*& node, Node* z )
{
	return NULL;
}

#endif