#include "testbase.h"
#include <assert.h>
#include <algorithm>

using namespace std;
TestPackage::TestPackage()
{

}

TestPackage::~TestPackage()
{
	clear();
}

TestPackage* TestPackage::instance()
{
	static TestPackage* sc_instance = NULL;
	if (!sc_instance)
		sc_instance = new TestPackage;
	return sc_instance;
}

void TestPackage::addItem( TestBase* item )
{
	assert(item);
	m_items.push_back(item);
}

void TestPackage::removeItem( TestBase* item )
{
	assert(item);
	vector<TestBase*>::iterator iter = find(m_items.begin(), m_items.end(), item);
	if (*iter)
		m_items.erase(iter);
}

TestBase* TestPackage::removeItem( int index )
{
	assert(index >= 0 && index < m_items.size());
	TestBase* item = m_items[index];
	m_items.erase(m_items.begin() + index);
	return item;
}

void TestPackage::deleteItem( int index )
{
	delete removeItem(index);
}

int TestPackage::count() const
{
	return m_items.size();
}

TestBase* TestPackage::getItem( int index )
{
	assert(index >= 0 && index < m_items.size());
	return m_items[index];
}

namespace
{
	void destoryItem(TestBase* item)
	{
		delete item;
	}
}
void TestPackage::clear()
{
	for_each(m_items.rbegin(), m_items.rend(), destoryItem);
	m_items.clear();
}

//////////////////////////////////////////////////////////////////////////
TestAddHelper::TestAddHelper( TestBase* item )
{
	TestPackage::instance()->addItem(item);
}
