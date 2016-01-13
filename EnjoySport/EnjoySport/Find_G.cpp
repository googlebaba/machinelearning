#include "Find_G.h"
using namespace std;
std::multimap<std::string,std::vector<std::string> > Find_G::eval(std::ifstream& is)
{
	//int count_str = 0;
	count_str = 0;
	string line;
	map<string,vector<string> >S_Set;//S��
	vector<string>svec(6,"#");
	string G_number = "S"+ IntToStr(count_str);
	S_Set.insert(make_pair(G_number,svec));//��ʼ��S��
	//vector<string>gvec(6,"?");
	//G_Set.insert(make_pair("G"+IntToStr(count_str),gvec));//��ʼ��G��
	while(getline(is,line))
	{
		++count_str;
		string word;
		vector<string>curr_str;//��ǰ���ַ���
		istringstream stream(line.c_str());
		while(stream>>word)
			curr_str.push_back(word);
		if("Yes" == curr_str[6])//�����Ϊyes
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
			while(find_G_after.first!=find_G_after.second)//����G������ɾ�������������ĺ�����
			{
				bool flag = true;
				//mul_iter temp_iter = find_G_after.first;
				curr_iter = curr_str.begin();
				vector<string>::const_iterator iter_G = find_G_after.first->second.begin();
				for(;iter_G!=find_G_after.first->second.end();++iter_G,++curr_iter)//����G��һ������
				{
					if(*curr_iter!=*iter_G&&*iter_G!="?")//ɾ��
					{
						find_G_after.first = G_Set.erase(find_G_after.first);
						flag = false;
						break;
					}
				}
				if(flag)
				++(find_G_after.first);
			}

			map<string,vector<string> >::const_iterator iter_S = S_Set.find("S"+IntToStr(count_str-1));//ָ��S�������һ����
			vector<string>::const_iterator iter_s_vec = iter_S->second.begin();
			for(curr_iter = curr_str.begin();curr_iter!=curr_str.end();++curr_iter,++iter_s_vec)//����S����
			{
				if(*iter_s_vec=="#")//������ǵ�һ������
				{					
					break;
				}else if(*curr_iter!=*iter_s_vec)
				{
					*curr_iter = "?";    //����֮ǰ���Բ�ͬ�������滻Ϊ��
				}
			}
			S_Set.insert(make_pair("S"+IntToStr(count_str),curr_str));//�ѵ�ǰ��һ��curr_str����
		}
		if("No" == curr_str[6])
		{
			map<string,vector<string> >::const_iterator iter_S = S_Set.find("S"+IntToStr(count_str-1));//ָ��S�������һ����
			vector<string>s_vec(iter_S->second);
			S_Set.insert(make_pair("S"+	IntToStr(count_str),s_vec));  //����Ƿ�����S������
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
				vector<string>::const_iterator v_iter = s_iter->second.begin();//S����
				int count = 0;
				for(curr_iter = curr_str.begin();curr_iter!=curr_str.end()-1;++curr_iter,++v_iter,++count,++G_iter)
				{
					if(*v_iter!=*curr_iter&&*v_iter!="?"&&*G_iter!=*v_iter)//�����µ�G��
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
