#pragma once
#include "Find_Base.h"
class Find_S:public Find_Base
{
public:
	friend class Find_Result;
	std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream&);						//ÿ��������붨��һ���������ݵĺ���
	
	void display()const;//��ӡÿ���൱ǰ�ĳ�Ա
	Find_S();
	int s_count();
private:
	std::vector<std::string> delete_ele(std::vector<std::string>);
	std::string IntToStr(int);
	std::multimap<std::string,std::vector<std::string> > s_set;
	int count;
};

