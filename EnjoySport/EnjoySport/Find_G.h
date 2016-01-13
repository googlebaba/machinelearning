#pragma once
#include "Find_Base.h"
class Find_G:public Find_Base
{
public:
	typedef std::multimap<std::string,std::vector<std::string> > mult_map;
	friend class Find_Result;
	std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream&);						//每个基类必须定义一个处理数据的函数
	void display()const{};//打印每个类当前的成员
	Find_G();
	int count_line();	
private:
	std::string IntToStr(int);
	std::multimap<std::string,std::vector<std::string> > G_Set;
	int count_str;
};

