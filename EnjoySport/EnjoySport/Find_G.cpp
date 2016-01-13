#include "Find_G.h"
using namespace std;
std::multimap<std::string,std::vector<std::string> > Find_G::eval(std::ifstream& is)
{
	//int count_str = 0;
	count_str = 0;
	string line;
	map<string,vector<string> >S_Set;//S集
	vector<string>svec(6,"#");
	string G_number = "S"+ IntToStr(count_str);
	S_Set.insert(make_pair(G_number,svec));//初始化S集
	//vector<string>gvec(6,"?");
	//G_Set.insert(make_pair("G"+IntToStr(count_str),gvec));//初始化G集
	while(getline(is,line))
	{
		++count_str;
		string word;
		vector<string>curr_str;//当前的字符串
		istringstream stream(line.c_str());
		while(stream>>word)
			curr_str.push_back(word);
		if("Yes" == curr_str[6])//当结果为yes
		{
			typedef multimap<string,vector<string> >::iterator mul_iter;
			typedef multimap<string,vector<string> >::size_type sz_type;
			vector<string>::iterator curr_iter = curr_str.begin();
			pair<mul_iter,mul_iter> find_G = G_Set.equal_range("G"+IntToStr(count_str-1));
			sz_type size_g = G_Set.count("G"+IntToStr(count_str-1));
			mul_iter G_mul_iter = find_G.first;
			for (sz_type cnt = 0;cnt!=size_g;++cnt,++G_mul_iter)
			{
				G_Set.insert(make_pair("G"+IntToStr(count_str),G_mul_iter->second));
			}
			pair<mul_iter,mul_iter> find_G_after = G_Set.equal_range("G"+IntToStr(count_str));
			while(find_G_after.first!=find_G_after.second)//处理G函数，删除与正例不符的函数集
			{
				bool flag = true;
				//mul_iter temp_iter = find_G_after.first;
				curr_iter = curr_str.begin();
				vector<string>::const_iterator iter_G = find_G_after.first->second.begin();
				for(;iter_G!=find_G_after.first->second.end();++iter_G,++curr_iter)//遍历G的一个集合
				{
					if(*curr_iter!=*iter_G&&*iter_G!="?")//删除
					{
						find_G_after.first = G_Set.erase(find_G_after.first);
						flag = false;
						break;
					}
				}
				if(flag)
				++(find_G_after.first);
			}

			map<string,vector<string> >::const_iterator iter_S = S_Set.find("S"+IntToStr(count_str-1));//指向S集中最后一个键
			vector<string>::const_iterator iter_s_vec = iter_S->second.begin();
			for(curr_iter = curr_str.begin();curr_iter!=curr_str.end();++curr_iter,++iter_s_vec)//处理S集合
			{
				if(*iter_s_vec=="#")//如果这是第一个正例
				{					
					break;
				}else if(*curr_iter!=*iter_s_vec)
				{
					*curr_iter = "?";    //把与之前属性不同的属性替换为？
				}
			}
			S_Set.insert(make_pair("S"+IntToStr(count_str),curr_str));//把当前的一个curr_str插入
		}
		if("No" == curr_str[6])
		{
			map<string,vector<string> >::const_iterator iter_S = S_Set.find("S"+IntToStr(count_str-1));//指向S集中最后一个键
			vector<string>s_vec(iter_S->second);
			S_Set.insert(make_pair("S"+	IntToStr(count_str),s_vec));  //如果是反例则S集不变
			vector<string>::iterator curr_iter = curr_str.begin();
			typedef multimap<string,vector<string> >::const_iterator mul_iter;
			typedef multimap<string,vector<string> >::size_type sz_type;
			pair<mul_iter,mul_iter> find_G = G_Set.equal_range("G"+IntToStr(count_str-1));
			sz_type sz = G_Set.count("G"+IntToStr(count_str-1));
			mul_iter tmp_iter = find_G.first;
			for(sz_type cnt = 0;cnt!=sz;++cnt,++tmp_iter)
			{
				vector<string>::const_iterator G_iter = tmp_iter->second.begin();
				map<string,vector<string> >::const_iterator s_iter = S_Set.find("S"+IntToStr(count_str));
				vector<string>::const_iterator v_iter = s_iter->second.begin();//S集合
				int count = 0;
				for(curr_iter = curr_str.begin();curr_iter!=curr_str.end()-1;++curr_iter,++v_iter,++count,++G_iter)
				{
					if(*v_iter!=*curr_iter&&*v_iter!="?"&&*G_iter!=*v_iter)//创建新的G集
					{
						vector<string>copy_g(tmp_iter->second);
						copy_g[count] = *v_iter;
						G_Set.insert(make_pair("G"+IntToStr(count_str),copy_g));
					}
				}
			}
		}
	}
	is.clear();
	is.seekg(0,ios::beg);
	return G_Set;
}

Find_G::Find_G()
{
	count_str = 0;
	vector<string>svec(6,"?");
	G_Set.insert(make_pair("G0",svec));
}

int Find_G::count_line()
{
	return count_str;
}

std::string Find_G::IntToStr(int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;
	return str;
}
