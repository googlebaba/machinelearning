#pragma once
#include "Find_Base.h"
class Find
{
public:
	~Find(){decr_use();}
	Find(const Find &f):q(f.q),use(f.use){++*use;}
	Find& operator=(const Find&);
	Find(std::ifstream&);
	virtual std::multimap<std::string,std::vector<std::string> >
		eval(std::ifstream& in){return q->eval(in);}
	virtual void display(){return q->display();}
private:
	Find(Find_Base* f):q(f),use(new std::size_t(1)){}
	void decr_use()
	{
		if(--*use==0)
		{
			delete q;
			delete use;
		}
	}
	Find_Base *q;
	std::size_t *use;
};

