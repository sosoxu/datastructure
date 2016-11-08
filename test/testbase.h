#ifndef TESTBASE
#define TESTBASE

/*!*******************************************
\brief: register test to package
\author:sosoxu
\date:2016/11/8
**********************************************/
#include <vector>

#define REGISTER_TEST(test) \
	TestAddHelper instance_##test(new test);

class TestBase
{
public:
    TestBase(){}
    virtual ~TestBase(){}
public:
    virtual void test(){}
	virtual const char* name() const { return m_name; }
	virtual const char* info() const { return m_info; }
protected:
	const char* m_name;
	const char* m_info;
};

class TestPackage
{
public:
	virtual ~TestPackage();
	static TestPackage* instance();

	void addItem(TestBase* item);
	void removeItem(TestBase* item);
	TestBase* removeItem(int index);
	void deleteItem(int index);
	int count() const;
	TestBase* getItem(int index);
	void clear();

protected:
	TestPackage();
private:
	std::vector<TestBase*> m_items;
};

class TestAddHelper
{
public:
	TestAddHelper(TestBase* item);
};

#endif // TESTBASE

