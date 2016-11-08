#ifndef PARAMSCONTROLS_H
#define PARAMSCONTROLS_H

#include <vector>
#include <string>
#include <map>

class TestBase;
class ParamItem
{
public:
	ParamItem(){}
	ParamItem(const std::string& cmd, const std::string& info)
	 :m_cmd(cmd), m_info(info) {}
	std::string getCmd() const { return m_cmd; }
	std::string getInfo() const { return m_info; }
	virtual ~ParamItem() {}
public:
	virtual void exec();
private:
protected:
	std::string m_cmd;
	std::string m_info;
};

/*
class ParamItemInfo : public ParamItem
{
public:
	ParamItemInfo(){}
	ParamItemInfo(const std::string&cmd, const std::string& info)
		: ParamItem(cmd), m_info(info) {}
	virtual void exec();
private:
	std::string m_info;
};
*/
class ParamItemTest : public ParamItem
{
public:
	ParamItemTest()
	 : m_item(NULL){}
	ParamItemTest(TestBase* item);
	virtual void exec();
private:
	TestBase* m_item;
};
class ParamsControls
{
public:
	ParamsControls();
	~ParamsControls();

	void exec(int argc, char* argv[]);
private:
	void init();
	bool handleCmd(const std::string& cmd);
private:
	//std::map<std::string, TestBase*> m_testItems; 
	std::map<std::string, ParamItem*> m_cmdItems;
	typedef std::map<std::string, ParamItem*> CmdMap;
};

#endif // PARAMSCONTROLS_H
