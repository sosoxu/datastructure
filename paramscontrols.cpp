#include "paramscontrols.h"
#include "testbase.h"
#include <iostream>

using namespace std;
//////////////////////////////////////////////////////////////////////////
void ParamItem::exec()
{
	cout << m_info << endl;

}

//////////////////////////////////////////////////////////////////////////
void ParamItemTest::exec()
{
	if (m_item)
		m_item->test();
}

ParamItemTest::ParamItemTest( TestBase* item )
	: m_item(item)
{
	if (item)
	{
		m_cmd = item->name();
		m_info = item->info();
	}
}

//////////////////////////////////////////////////////////////////////////
ParamsControls::ParamsControls()
{
	init();
}

ParamsControls::~ParamsControls()
{

}

void ParamsControls::init()
{
	TestPackage* package = TestPackage::instance();
	int cnt = package->count();
	string testnames;
	for (int i = 0; i < cnt; ++i)
	{
		TestBase* item = package->getItem(i);
		//m_testItems[item->name()] = item;
		m_cmdItems[item->name()] = new ParamItemTest(item);
		testnames = testnames + item->name() + " : " + item->info() + "\n";
	}

	//read file
	ParamItem* pItem = NULL;
	pItem = new ParamItem("version", "1.0.0");
	m_cmdItems[pItem->getCmd()] = pItem;
	testnames = testnames + pItem->getCmd() + " : " +  pItem->getInfo() + "\n";
	m_cmdItems["-v"] = pItem;

	pItem = new ParamItem("author", "sosoxu");
	m_cmdItems[pItem->getCmd()] = pItem;
	testnames = testnames + pItem->getCmd() + " : " +  pItem->getInfo() + "\n";

	pItem = new ParamItem("email", "none");
	m_cmdItems[pItem->getCmd()] = pItem;
	testnames = testnames + pItem->getCmd() + " : " +  pItem->getInfo() + "\n";

	pItem = new ParamItem("exit", "exit");
	m_cmdItems[pItem->getCmd()] = pItem;
	testnames = testnames + pItem->getCmd() + " : " +  pItem->getInfo() + "\n";

	pItem = new ParamItem("help", "you can input : \n" + testnames);
	m_cmdItems[pItem->getCmd()] = pItem;
	testnames = testnames + pItem->getCmd() + " : " +  pItem->getInfo() + "\n";
	m_cmdItems["-h"] = pItem;
}

void ParamsControls::exec( int argc, char* argv[] )
{
	if (argc == 1)
	{
		cout << "please input -h or help to get info" << endl;
		while (1)
		{
			string buff;
			cin >> buff;
			if (!handleCmd(buff))
				break;
		}
	}
	else if (argc >= 2)
	{
		string buff = argv[1];
		handleCmd(buff);
	}
}

bool ParamsControls::handleCmd( const std::string& cmd )
{
	CmdMap::iterator iter;
	for (CmdMap::iterator iter = m_cmdItems.begin(); iter != m_cmdItems.end(); ++iter)
	{
		if (cmd.compare(iter->first) == 0)
		{
			iter->second->exec();
			if (cmd.compare("exit") == 0)
				return false;
		}
	}
	return true;
}



