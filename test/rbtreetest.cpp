#include "rbtreetest.h"
#include "rbtree.h"

using namespace DT;
REGISTER_TEST(RBTreeTest)
RBTreeTest::RBTreeTest()
{
	m_name = "rb";
	m_info = "red black tree";
}

RBTreeTest::~RBTreeTest()
{

}

void RBTreeTest::test()
{
	RBTree<int> tree;
	tree.insert(1);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	tree.insert(9);
	tree.insert(7);
	tree.insert(2);
	tree.insert(5);
	tree.insert(8);
	/*
	tree.insert(6);
	tree.insert(7);
	tree.insert(1);
	tree.insert(10);
	*/
	printf("\nmax : %d, min : %d\n", tree.maximum(), tree.minimun());
	printf("\ndepth : %d, count : %d\n", tree.depth(), tree.count());
	printf("\nlevelorder:\n");
	tree.levelorder(BSTreeVisitor<int>(), 10);
	printf("\npreorder\n");
	tree.preorder(BSTreeVisitor<int>());
	printf("\npreordernonrec\n");
	tree.preorderNonRec(BSTreeVisitor<int>(), 10);
	printf("\ninorder\n");
	tree.inorder(BSTreeVisitor<int>());
	printf("\ninordernonrec\n");
	tree.inorderNonRec(BSTreeVisitor<int>(), 10);
	printf("\npostorder\n");
	tree.postorder(BSTreeVisitor<int>());
}
