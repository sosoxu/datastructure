#ifndef BSTREE_H_
#define BSTREE_H_

#include <stdio.h>
/*!*******************************************
\brief:Binary Search Tree
\author:sosoxu
\date:2016/11/1
**********************************************/

template<typename T>
class BSTNode
{
public:
	T key;
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;

public:
	BSTNode(T val, BSTNode* parent, BSTNode* left, BSTNode* right)
		:key(val), parent(parent), left(left), right(right){}
};

template<typename T>
class BSTreeVisitor
{
public:
	void operator()(BSTNode<T>* node)
	{
		stdvisitor(node);
	}
	void stdvisitor(BSTNode<T>* node)
	{
		printf("%d", (int)node->key);
	}
};

//如何提供一个visitor？

template<typename T, typename Visitor = BSTreeVisitor<T> >
class BSTree
{
public:
	typedef BSTNode<T> Node;
public:
	BSTree();
	BSTree(Visitor visitor);
	~BSTree();

    template<typename LVisitor>
    void preorder(LVisitor visitor);

    template<typename LVisitor>
    void inorder(LVisitor visitor);

    template<typename LVisitor>
    void postorder(LVisitor visitor);

	void preorderNonRec();
	void inorderNonRec();
	void postorderNonRec();

	Node* search(T key);
	Node* iterativeSearch(T key); 

	T maximum();
	T minimun();

	void insert(T key);
	void remove(T key);
	void destory();
	void dump();
private:
    template<typename LVisitor>
    void preorder(Node* node, LVisitor func) const;

    template<typename LVisitor>
    void inorder(Node* node, LVisitor func) const;

    template<typename LVisitor>
    void postorder(Node* node, LVisitor func) const;

	Node* search(Node* node, T key) const;
	Node* iterativeSearch(Node* node, T key) const;

	Node* minimum(Node* node);
	Node* maximum(Node* node);

	void insert(Node*& node, Node* z);
	Node* remove(Node*& node, Node* z);

private:
	Node* m_root;
    Visitor m_visitor;
};



template<typename T, typename Visitor>
void BSTree<T, Visitor>::dump()
{

}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::remove( Node*& node, Node* z )
{

}

template<typename T, typename Visitor>
void BSTree<T, Visitor>::remove( T key )
{

}

template<typename T, typename Visitor>
void BSTree<T, Visitor>::insert( Node*& node, Node* z )
{
	Node* insertNode = NULL;
	Node* tmp = node;
	while (tmp)
	{
		insertNode = tmp;
		if (tmp->key > z->key)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	z->parent = insertNode;
	if (!insertNode)
	{
		node = z;//without root on current branch
	}
	else if (insertNode->key > z->key)
	{
		insertNode->left  = z;
	}
	else
		insertNode->right = z;
}

template<typename T, typename Visitor>
void BSTree<T, Visitor>::insert( T key )
{
	Node* z = new Node(key, NULL, NULL, NULL);
	if (z)
	{
		insert(m_root, z);
	}
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::minimum( Node* node )
{
	if (!node)
		return NULL;
	while(!node->left)
	{
		node = node->left;
	}
}

template<typename T, typename Visitor>
T BSTree<T, Visitor>::minimun()
{
	Node* node = minimum(m_root);
	if (node)
		return node->key;
	return T();
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::maximum( Node* node )
{
	if (!node)
		return NULL;
	while (!node->right)
	{
		node = node->right;
	}
	return node;
}

template<typename T, typename Visitor>
T BSTree<T, Visitor>::maximum()
{
	Node* node = maximum(m_root);
	if (node)
		return node->key;
	return T();
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::iterativeSearch( Node* node, T key ) const
{
	while(node && node->key != key)
	{
		if (node->left < key)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::iterativeSearch( T key )
{
	iterativeSearch(m_root, key);
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::search( Node* node, T key ) const
{
	if (!node || node->key == key)
		return node;
	if (node->key < key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

template<typename T, typename Visitor>
typename BSTree<T, Visitor>::Node* BSTree<T, Visitor>::search( T key )
{
	return search(m_root, key);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::postorder( Node* node, LVisitor func ) const
{
	if (node)
	{
        postorder(node->left, func);
        postorder(node->right, func);
        func(node);
	}
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::postorder( LVisitor visitor )
{
    postorder(m_root, visitor);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::inorder( Node* node, LVisitor func ) const
{
	if (node)
	{
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
	}
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::inorder( LVisitor visitor )
{
    inorder(m_root, visitor);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::preorder( Node* node, LVisitor func ) const
{
	if (node)
	{
        func(node);
        preorder(node->left, func);
        preorder(node->right, func);
	}
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::preorder( LVisitor visitor)
{
    preorder(m_root, visitor);
}

template<typename T, typename Visitor>
BSTree<T, Visitor>::BSTree()
    :m_root(NULL), m_visitor(BSTreeVisitor<T>())
{

}

template<typename T, typename Visitor /*= stdvisitor<T> */>
BSTree<T, Visitor>::BSTree( Visitor visitor )
    :m_root(NULL), m_visitor(visitor)
{

}

template<typename T, typename Visitor>
BSTree<T, Visitor>::~BSTree()
{

}

#endif
