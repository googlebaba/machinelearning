#pragma once
#include "Find_G.h"
#include "Find_S.h"

class Find_Result
{
public:
	typedef std::multimap<std::string,std::vector<std::string> > multi;
	typedef std::vector<std::vector<std::string> > vec_vec;
	/**���캯��**/
	Find_Result():general(),spcial(){};

	/**������Ϳռ�**/
	void print_result(std::ifstream&);
private:

	/**�жϿռ��Ƿ��������**/
	bool tighter(const std::vector<std::string>&,const vec_vec&);

	/**������ز�Ŀռ�**/
	void print_Hidden(const multi&);
	/**intתΪString**/
	std::string IntToStr2(int);

	Find_G general;   //G�߽�
	Find_S spcial;   //S�߽�

	std::vector<std::string> s_set;   //S�߽�ļ���
	vec_vec g_set;   //G�߽�ļ���
};

