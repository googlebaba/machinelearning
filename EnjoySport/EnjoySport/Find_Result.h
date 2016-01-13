#pragma once
#include "Find_G.h"
#include "Find_S.h"

class Find_Result
{
public:
	typedef std::multimap<std::string,std::vector<std::string> > multi;
	typedef std::vector<std::vector<std::string> > vec_vec;
	/**构造函数**/
	Find_Result():general(),spcial(){};

	/**输出变型空间**/
	void print_result(std::ifstream&);
private:

	/**判断空间是否符合条件**/
	bool tighter(const std::vector<std::string>&,const vec_vec&);

	/**输出隐藏层的空间**/
	void print_Hidden(const multi&);
	/**int转为String**/
	std::string IntToStr2(int);

	Find_G general;   //G边界
	Find_S spcial;   //S边界

	std::vector<std::string> s_set;   //S边界的集合
	vec_vec g_set;   //G边界的集合
};

