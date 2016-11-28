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
	static AVLNode* BSTNode2AVLNode(Node* node);
};

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::BSTNode2AVLNode( Node* node )
{
	return static_cast<AVLNode*>(node);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
void AVLTree<T, Visitor>::updateHeight(AVLNode* node)
{
	AVLNode* left = BSTNode2AVLNode(node->left);
	AVLNode* right = BSTNode2AVLNode(node->right);
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

//              G                                  P
//            /     \                             /      \
//           P     Gr     =>            X        G
//        /     \                             /          /    \
//      X      Pr                         Xl       Pr    Gr
//     / 
//    Xl
template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::llrotate( AVLNode* node )
{
    AVLNode* b = BSTNode2AVLNode(node->left);
	node->left = b->right;
	b->right = node;

    updateHeight(node);
    updateHeight(b);
    return b;
}

//         G                                      P
//       /      \                                 /     \
//     Gl     P          =>              G      X
//              /   \                         /   \       \
//            Pl   X                     Gl   Pl     Xr
//                    \
//                   Xr
template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::rrrotate( AVLNode* node )
{
    AVLNode* b = BSTNode2AVLNode(node->right);
    node->right = b->left;
    b->left = node;

    updateHeight(node);
    updateHeight(b);
    return b;
}

//          G                                   G                               X           
//        /      \                               /    \                           /     \
//       P     Gr                          X     Gr                     P      G
//      /   \               =>             /   \                =>      /    \     /   \
//     Pl   X                            P    Xr                     Pl   Xl  Xr  Gr
//          /   \                          /   \
//        Xl   Xr                      Pl  Xl
template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::lrrotate( AVLNode* node )
{
    node->left = rrrotate(BSTNode2AVLNode(node->left));
    return llrotate(node);
}

//          G                               G                                       X
//        /      \                          /     \                                   /     \
//       Gl     P                      Gl     X                              G      P
//               /   \        =>                /   \                 =>      /   \     /   \
//             X    Pr                       Xl    P                      Gl   Xl  Xr  Pr 
//           /   \                                      /   \
//        Xl    Xr                                  Xr   Pr
template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename AVLTree<T, Visitor>::AVLNode* AVLTree<T, Visitor>::rlrotate( AVLNode* node )
{
    node->right = llrotate(BSTNode2AVLNode(node->right));
    return rrrotate(node);
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* AVLTree<T, Visitor>::remove( Node*& node, Node* z )
{
	if (node == NULL || z == NULL)
		return NULL;
	if (node->key > z->key)
	{
		node->left = remove(node->left, z);
		if (height(BSTNode2AVLNode(node->right)) - height(BSTNode2AVLNode(node->left)) == 2)
		{
			Node* n = node->right;
			if (height(BSTNode2AVLNode(n->left)) > height(BSTNode2AVLNode(n->right)))
				node = rlrotate(BSTNode2AVLNode(node));
			else
				node = rrrotate(BSTNode2AVLNode(node));
		}
	}
	else if (node->key < z->key)
	{
		if (height(BSTNode2AVLNode(node->left)) - height(BSTNode2AVLNode(node->left)) == 2)
		{
			Node* n = node->left;
			if (height(BSTNode2AVLNode(n->left)) > height(BSTNode2AVLNode(n->right)))
				node = llrotate(BSTNode2AVLNode(node));
			else
				node = lrrotate(BSTNode2AVLNode(node));
		}
	}
	else
	{
		if (node->left && node->right)
		{
			Node* n = maximum(node->left);
			node->key = n->key;
			node->left = remove(node->left, n);
		}
		else
		{
			Node* tmp = node;
			node = node->left ? node->left : node->right;
			delete tmp;
		}
	}

	return node;
}

template<typename T, typename Visitor /*= BSTreeVisitor<T> */>
typename BSTree<T, Visitor>::Node* AVLTree<T, Visitor>::insertNode( Node*& node, Node* z )
{
	AVLNode* x = BSTNode2AVLNode(z);
    AVLNode* n = BSTNode2AVLNode(node);
	if (!node)
	{
        node = z;
		n = static_cast<AVLNode* >(node);
    }
    else if (z->key < node->key)
    {
        node->left = insertNode(node->left, z);
        if (height(BSTNode2AVLNode(node->left)) - height(BSTNode2AVLNode(node->right)) == 2)
        {
            if (z->key < node->left->key)
                node = llrotate(n);
            else
                node = lrrotate(n);
			n = BSTNode2AVLNode(node);
        }
    }
    else if (z->key > node->key)
    {
        node->right = insertNode(node->right, z);
        if (height(BSTNode2AVLNode(node->right)) - height(BSTNode2AVLNode(node->left)) == 2)
        {
            if (z->key > node->right->key)
                node = rrrotate(n);
            else
                node = rlrotate(n);
			n = BSTNode2AVLNode(node);
        }
    }

    updateHeight(n);
    return node;
}


#endif
