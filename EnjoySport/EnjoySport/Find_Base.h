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
		eval(std::ifstream&) = 0;						//ÿ��������붨��һ���������ݵĺ���
	virtual void
		display()const = 0;   //��ӡÿ���൱ǰ�ĳ�Ա
};
inline std::string operator+(const std::string& str1,int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;
	return str1+str;
}
