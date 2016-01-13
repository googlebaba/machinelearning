#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
class Find_Base
{
	friend class Find;
protected:
	virtual ~Find_Base(){};
private:
	virtual std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream&) = 0;						//每个基类必须定义一个处理数据的函数
	virtual void
		display()const = 0;   //打印每个类当前的成员
};
inline std::string operator+(const std::string& str1,int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;
	return str1+str;
}
