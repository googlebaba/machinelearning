#pragma once
#include "Find_Base.h"
class Find_S:public Find_Base
{
public:
	friend class Find_Result;
	std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream&);						//每个基类必须定义一个处理数据的函数
	
	void display()const;//打印每个类当前的成员
	Find_S();
	int s_count();
private:
	std::vector<std::string> delete_ele(std::vector<std::string>);
	std::string IntToStr(int);
	std::multimap<std::string,std::vector<std::string> > s_set;
	int count;
};

