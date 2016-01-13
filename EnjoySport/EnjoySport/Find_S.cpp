#include "Find_S.h"
using namespace std;
std::multimap<std::string,std::vector<std::string> > Find_S::eval(std::ifstream& is)
{
	//int count = 0;
	string line;
	vector<string>currfind;
	vector<string>prefind;
	while(getline(is,line))
	{
		++count;
		currfind.clear();
		istringstream stream(line);
		string word;
		while(stream>>word)
			currfind.push_back(word);
		if(1==count)
		{
			prefind = currfind;
			s_set.insert(make_pair("S"+IntToStr(count),delete_ele(prefind)));
			continue;
		}
		vector<string>::iterator pre_iter = prefind.begin();
		vector<string>::iterator curr_iter = currfind.begin();
		if(currfind[6]=="No")  //判断最后一个元素是否为yes
			{
				s_set.insert(make_pair("S"+IntToStr(count),delete_ele(prefind)));
				continue;
			}
		for(;pre_iter!=prefind.end();++pre_iter,++curr_iter)
		{
			if(*pre_iter!=*curr_iter)
			{
				*pre_iter = "?";                       //如果有不同的项则替换为？
				
			}
		}
		s_set.insert(make_pair("S"+IntToStr(count),delete_ele(prefind)));
	}
	is.clear();
	is.seekg(0,ios::beg);
	return s_set;    //返回更改后的h
}

void Find_S::display() const
{
	multimap<string,vector<string> >::const_iterator iter = s_set.begin();
	for(;iter!=s_set.end();++iter)
	{
		vector<string>::const_iterator vec_iter = iter->second.begin();
		while(vec_iter!=iter->second.end())
		{
			cout<<*vec_iter++<<endl;
		}
	}
}

Find_S::Find_S()
{
	count = 0;
	vector<string>svec(6,"#");
	s_set.insert(make_pair("S0",svec));
}

int Find_S::s_count()
{
	return count;
}
std::string Find_S::IntToStr(int n)
{
	std::stringstream ss;
	std::string str;
	ss<<n;
	ss>>str;
	return str;
}

std::vector<std::string> Find_S::delete_ele(std::vector<std::string> curr_vec)
{
	curr_vec.erase(curr_vec.end()-1);
	return curr_vec;
}

