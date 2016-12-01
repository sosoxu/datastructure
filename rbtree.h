#ifndef RBTREE_H_
#define RBTREE_H_

#include "bstree.h"

namespace DT{
#define rb_red 0
#define rb_black 1

template<typename T>
class RBTreeNode : public BSTNode<T>
{
public:
    static const bool red = false;
    static const bool black = true;
	bool color; // 0 red;1 black
public:
	RBTreeNode(T val, RBTreeNode* parent = NULL, RBTreeNode* left = NULL, RBTreeNode* right = NULL, bool color = 0)
		:BSTNode<T>(val, parent, left, right), color(color){}
	virtual void dump()
	{
		printf("%d(%c)  ", (int)key, color == red ? 'r' : 'b');
	}
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

public:
	Node* leftrotate(Node*& root, Node* node);
    Node* rightrotate(Node*& root, Node* node);
    void insertFixup(Node*& root, Node* z);

    static RBNode* BSTNode2RBNode(Node* node);
    static bool getColor(Node* node);
};

template<typename T, typename Visitor>
typename RBTree<T,Visitor>::RBNode* RBTree<T, Visitor>::BSTNode2RBNode(Node *node)
{
    return static_cast<RBNode*>(node);
}

template<typename T, typename Visitor>
bool RBTree<T, Visitor>::getColor(Node *node)
{
    RBNode* rbnode = BSTNode2RBNode(node);
    if (rbnode)
        return rbnode->color;
    return RBNode::black;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename DT::RBTree<T, Visitor>::Node* DT::RBTree<T, Visitor>::rightrotate( Node*& root, Node* node )
{
	Node* y = node->left;
	node->left = y->right;
	if (y->right)
		y->right->parent = node;
	y->parent = node->parent;
	if (!node->parent)
		root = y;
	else
		if (node == node->parent->left)
			node->parent->left = y;
		else
			node->parent->right = y;
	y->right = node;
	node->parent = y;
	return y;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename DT::RBTree<T, Visitor>::Node* DT::RBTree<T, Visitor>::leftrotate( Node*& root, Node* node )
{
	Node* y = node->right;
	node->right = y->left;
	if (y->left)
		y->left->parent = node;
	y->parent = node->parent;
	if (!node->parent)
		root = y;
	else
	{
		if (node == node->parent->left)
			node->parent->left = y;
		else
			node->parent->right = y;
	}
	y->left = node;
	node->parent = y;
	return y;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void RBTree<T, Visitor>::insert( T key )
{
	Node* z = createNode(key);
	insertNode(BSTree<T,Visitor>::m_root, z);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* RBTree<T, Visitor>::insertNode( Node*& node, Node* z )
{
    Node* y = NULL;
    Node* x = node;
    while (x)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y)
        node = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    RBNode* rbnode = BSTNode2RBNode(z);
    rbnode->color = RBNode::red;
	insertFixup(node, z);
    return node;
}


template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void RBTree<T, Visitor>::insertFixup(Node*& root, Node* z)
{
	RBNode* rbz = BSTNode2RBNode(z);
	RBNode* p = NULL;
    while ((p = BSTNode2RBNode(rbz->parent)) && p->color == RBNode::red)
	{
		RBNode* g = BSTNode2RBNode(p->parent);
		if (p == g->left)
		{
			RBNode* sp = BSTNode2RBNode(g->right);
			if (sp && sp->color == RBNode::red)	//parent sibling : red
			{
				sp->color = RBNode::black;
				p->color = RBNode::black;
				g->color = RBNode::red;
				rbz = g;
				continue;
			}

			if (p->right == rbz)
			{
				RBNode* t = p;
				BSTNode2RBNode(leftrotate(root, p));
				p = rbz;
				rbz = t;
			}

			p->color = RBNode::black;
			g->color = RBNode::red;
			BSTNode2RBNode(rightrotate(root, g));
		}
		else
		{
			RBNode* sp = BSTNode2RBNode(g->left);
			if (sp && sp->color == RBNode::red)	//parent sibling : red
			{
				sp->color = RBNode::black;
				p->color = RBNode::black;
				g->color = RBNode::red;
				rbz = g;
				continue;
			}

			if (p->left == rbz)
			{
				RBNode* t = p;
				BSTNode2RBNode(rightrotate(root, p));
				p = rbz;
				rbz = t;
			}

			p->color = RBNode::black;
			g->color = RBNode::red;
			BSTNode2RBNode(leftrotate(root, g));
		}
	}
	RBNode* rbroot = BSTNode2RBNode(root);
	rbroot->color = RBNode::black;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* RBTree<T, Visitor>::remove( Node*& node, Node* z )
{
	return NULL;
}
}
#endif
