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
        printf("%d ", (int)node->key);
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

    //DLR
    template<typename LVisitor>
    void preorder(LVisitor visitor);

    //LDR
    template<typename LVisitor>
    void inorder(LVisitor visitor);

    //LRD
    template<typename LVisitor>
    void postorder(LVisitor visitor);

    //NonRec : non recurse
	template<typename LVisitor>
	void preorderNonRec(LVisitor visitor, int max_node);

	template<typename LVisitor>
	void inorderNonRec(LVisitor visitor, int max_node);

	template<typename LVisitor>
	void postorderNonRec(LVisitor visitor, int max_node);

    template<typename LVisitor>
    void levelorder(LVisitor visitor, int max_node);

	Node* search(T key);
	Node* iterativeSearch(T key); 

	T maximum();
	T minimun();

	void insert(T key);
	void remove(T key);
	void destory();
	void dump();

    int depth();
    int count();
private:
    template<typename LVisitor>
    void preorder(Node* node, LVisitor func) const;

    template<typename LVisitor>
    void inorder(Node* node, LVisitor func) const;

    template<typename LVisitor>
    void postorder(Node* node, LVisitor func) const;

	template<typename LVisitor>
	void preorderNonRec(Node* node, LVisitor func, int max_node);
	
	template<typename LVisitor>
	void inorderNonRec(Node* node, LVisitor func, int max_node);

	template<typename LVisitor>
	void postorderNonRec(Node* node, LVisitor func, int max_node);

    template<typename LVisitor>
    void levelorder(Node* node, LVisitor visitor, int max_node);

	Node* search(Node* node, T key) const;
	Node* iterativeSearch(Node* node, T key) const;

	Node* minimum(Node* node);
	Node* maximum(Node* node);

	void insert(Node*& node, Node* z);
    Node* remove(Node*& node, Node* z);

    int depth(Node* node, int max_node);
    int count(Node* node, int max_node);
private:
	Node* m_root;
    Visitor m_visitor;
};

namespace {
  template<typename T>
  class StaticsCount
  {
  public:
      StaticsCount(int &val)
          :m_count(val){}
      void operator()(BSTNode<T>* node)
      {
          ++m_count;
      }
	  void reset() { m_count = 0; }
	  int getCount() const { return m_count; }
  public:
      int& m_count;
  };
}
template<typename T, typename Visitor>
int BSTree<T, Visitor>::count(Node *node, int max_node)
{
    if (!node)
        return 0;

	int sum = 0;
    StaticsCount<T> sc(sum);
    levelorder(node, sc, max_node);
    return sc.m_count;
}

template<typename T, typename Visitor>
int BSTree<T, Visitor>::count()
{
    return count(m_root, 50);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::levelorder(Node* node, LVisitor visitor, int max_node)
{
    if (!node)
        return;
    Node** stack = new Node*[max_node];
    int top, bottom;
    top = 0;
    bottom = top + 1;
    stack[top] = node;
    Node* p = NULL;
    while (top < bottom)
    {
        p = stack[top++];
        visitor(p);
        if (p->left)
            stack[bottom++] = p->left;
        if (p->right)
            stack[bottom++] = p->right;
    }
    delete[] stack;
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::levelorder(LVisitor visitor, int max_node)
{
    levelorder(m_root, visitor, max_node);
}

template<typename T, typename Visitor>
int BSTree<T, Visitor>::depth( Node* node, int max_node )
{
    if (!node)
        return 0;
    Node** stack = new Node*[max_node];
    int* ma = new int[max_node];
    int top = 0, bottom = 0, level = 1;
    stack[top] = node;
    ma[top] = level;
    bottom = top + 1;
    Node* p = NULL;
    int tl = 1;
    while (top < bottom)
    {
        p = stack[top];
        tl = ma[top];
        ++top;
        //if (top == bottom)
        //    ++level;
        if (p->left)
        {
            stack[bottom] = p->left;
            ma[bottom] = tl + 1;
            ++bottom;
        }
        if (p->right)
        {
            stack[bottom] = p->right;
            ma[bottom] = tl + 1;
            ++bottom;
        }
    }
    level = ma[--top];
    delete[] stack;
    delete[] ma;
    return level;

}

template<typename T, typename Visitor>
int BSTree<T,Visitor>::depth()
{
    return depth(m_root, 50);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::preorderNonRec(Node* node, LVisitor func, int max_node)
{
	if (!node)
		return;
	//assert(max_node > 0);
	Node** stack = new Node*[max_node];
	int top = 0;
	stack[++top] = node;
	while (top > 0)
	{
		Node* p = stack[top--];
		func(p);
		if (p->right)
			stack[++top] = p->right;
		if (p->left)
			stack[++top] = p->left;
	}
	delete[] stack;
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::inorderNonRec(Node* node, LVisitor func, int max_node)
{
    if (!node)
        return;
    Node** stack = new Node*[max_node];
    int top = 0;
    Node* p = node;
    do
    {
        while(p)
        {
           stack[++top] = p;
           p = p->left;
        }
        if (!top)
            break;
        p = stack[top--];
        func(p);
        p = p->right;
    } while(top >= 0);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::postorderNonRec(Node* node, LVisitor func, int max_node)
{

}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::postorderNonRec( LVisitor visitor, int max_node )
{

}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::inorderNonRec( LVisitor visitor, int max_node )
{
    inorderNonRec(m_root, visitor, max_node);
}

template<typename T, typename Visitor>
template<typename LVisitor>
void BSTree<T, Visitor>::preorderNonRec( LVisitor visitor, int max_node )
{
	preorderNonRec(m_root, visitor, max_node);
}

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
    while(node->left)
	{
		node = node->left;
	}
    return node;
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
    while (node->right)
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
