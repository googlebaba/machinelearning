#pragma once
#include "Find_Base.h"
class Find_G:public Find_Base
{
public:
	typedef std::multimap<std::string,std::vector<std::string> > mult_map;
	friend class Find_Result;
	std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream&);						//ÿ��������붨��һ���������ݵĺ���
	void display()const{};//��ӡÿ���൱ǰ�ĳ�Ա
	Find_G();
	int count_line();	
private:
	std::string IntToStr(int);
	std::multimap<std::string,std::vector<std::string> > G_Set;
	int count_str;
};

