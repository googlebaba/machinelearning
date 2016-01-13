#include "Find_Result.h"
using namespace std;
ifstream& open_file(ifstream& in,string filename)
{
	in.close();
	in.clear();
	in.open(filename.c_str());
	return in;
}
int main()
{
	ifstream infile;
	string filename("Weather.txt");
	//cout<<"Enter the filename you want to open!"<<endl;
	//cin>>filename;
	open_file(infile,filename);
	Find_Result result;
	result.print_result(infile);
	while(1);
	return 0;
}