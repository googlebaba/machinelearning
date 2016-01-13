#include "Find_Result.h"
using namespace std;
void Find_Result::print_result(std::ifstream& in)
{
//	inline std::string operator+(std::string str1,int n);
	//typedef multimap<string,vector<string> > multi;
	typedef multimap<string,vector<string> >::size_type sz_type;
	multi g_mul_map = general.eval(in);
	multi s_map = spcial.eval(in);
	int size_s = spcial.s_count();
	sz_type entries = g_mul_map.count("G"+ IntToStr2(general.count_line()));
	multi::const_iterator iter1 = g_mul_map.find("G"+IntToStr2(general.count_line()));
	vec_vec temp_vec;

	for(sz_type cnt = 0;cnt!=entries;++cnt,++iter1)
	{
		temp_vec.push_back(iter1->second);
	}
	g_set = temp_vec;


	/**输出S集**/
	iter1 = g_mul_map.find("G"+IntToStr2(general.count_line()));
	multi::const_iterator iter_s = s_map.find("S"+IntToStr2(size_s));
	s_set = iter_s->second;   //保存S边界
	vector<string>::const_iterator map_s_iter = iter_s->second.begin();
	cout<<"S"<<size_s<<" {<";
	for(;map_s_iter!=iter_s->second.end();++map_s_iter)
	{
		cout<<*map_s_iter<<" ";
	}
	cout<<">}"<<endl;
	cout<<"\n"<<endl;

	/**输出隐藏层**/
	print_Hidden(s_map);

	/**输出G集**/
	cout<<"\n\n"<<endl;
	cout<<"G"<<general.count_line()<<" {";
	for(sz_type cnt = 0;cnt!=entries;++cnt,++iter1)
	{
		vector<string>::const_iterator vec_iter = iter1->second.begin();
		cout<<"<";
		for(;vec_iter!=iter1->second.end();++vec_iter)
		cout<<*vec_iter<<" ";
		cout<<">";
	}
	cout<<"}";
}

bool Find_Result::tighter(const std::vector<std::string>& vec,const vec_vec& G_bianjie)
{
	bool flag = false;
	for(vector<string>::size_type ix = 0;ix!=vec.size();++ix)
	{
		if(vec[ix]!="?")
			for(size_t x=0;x!=G_bianjie.size();++x)
				for(size_t y =0;y!=G_bianjie[0].size();++y)
					if(vec[ix]==G_bianjie[x][y])
						flag = true;
	}
	return flag;
}

void Find_Result::print_Hidden(const multi& s_Map)
{
	typedef vector<vector<string> > Hidden_vec;   //隐藏层的空间
	int size_s = spcial.s_count();
	multi::const_iterator iter_s = s_Map.find("S"+IntToStr2(size_s));
	vector<string>::size_type cnt = iter_s->second.size();//属性的个数
	for(vector<string>::size_type sz = 0;sz!=cnt;++sz)
	{
		vector<string> s_vec(iter_s->second);     //取得S集
		if(s_vec[sz]!="?")
		{
			s_vec[sz] = "?";               //放宽条件
		if(tighter(s_vec,g_set))
		{
			cout<<"<";
			for(vector<string>::iterator iter = s_vec.begin();
				iter!=s_vec.end();++iter)
			{
				cout<<*iter<<" ";
			}
			cout<<">\t";
		}
		}
	}
}
std::string Find_Result::IntToStr2(int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;
	return str;
}