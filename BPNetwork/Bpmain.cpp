#include "BPNetwork.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

/**������**/
const int count_train = 101;
const int count_test = 49;
/**ѵ����������������**/
double **trainInput;
double **trainOutput;

/**������������������,��75�����ݣ�ÿ������4������ֵ**/
double testInput[count_test][4];
double testOutput[count_test];
double testTarget[count_test];

/**��ѵ������**/
bool readTrainFile(char* filename)
{
	ifstream infile;
	infile.open(filename);
	string kindstr;
	for(int i=0;i!=count_train;++i)
	{
		for(int j=0;j!=4;++j)
		{
			infile>>trainInput[i][j];
		}
		infile>>kindstr;
		if("setosa"==kindstr)
			trainOutput[i][0] = 1.0;
		else if ("versicolor"==kindstr)
			trainOutput[i][1] = 1.0;
		else if("virginica"==kindstr)
			trainOutput[i][2] = 1.0;
	}
	//fclose(stdin);

	return true;
}
/**�򿪲�������**/
bool readTestFile(char* filename)
{
	ifstream in;
	in.open(filename);
	string kindstr;
	for(int i=0;i!=count_test;++i)
	{
		for(int j=0;j!=4;++j)
		{
			in>>testInput[i][j];
		}
		in>>kindstr;
		if("setosa"==kindstr)
			testTarget[i] = 0;
		else if ("versicolor"==kindstr)
			testTarget[i] = 1;
		else if("virginica"==kindstr)
			testTarget[i] = 2;
	}
	//fclose(stdin);

	return true;
}
/*
bool readTestFile(char* filename)
{
	if(freopen(filename,"r",stdin)==NULL)
		return false;
	string kindstr;
	for(int i=0;i!=count_test;++i)
	{
		for(int j=0;j!=4;++j)
		{
			cin>>testInput[i][j];
		}
		cin>>kindstr;
		if("setosa"==kindstr)
			testTarget[i] = 0;
		else if ("versicolor"==kindstr)
			testTarget[i] = 1;
		else if("virginica"==kindstr)
			testTarget[i] = 2;
	}
	fclose(stdin);

	return true;
}*/
/**������Խ��**/
bool writeTestResult(char* filename)
{
	/*if(!freopen(filename,"w",stdout))
	{
		cout<<"�޷���������"<<endl;
		return false;
	}*/
	int err_count = 0;
	for(int i=0;i!=count_test;++i)
	{
		if(testTarget[i]!=testOutput[i])
			++err_count;
		if(testOutput[i]==0)
		   cout<<"setosa"<<endl;
		else if(testOutput[i]==1)
			cout<<"versicolor"<<endl;
		else if(testOutput[i]==2)
			cout<<"virginica"<<endl;
	}
	cout<<count_test<<"������ "<<err_count<<"���������"<<endl;
	cout<<"��ȷ�ʣ�"<<static_cast<double>(count_test-err_count)/static_cast<double>(count_test)<<endl;
	//fclose(stdout);
	return true;
}

/**����������Ӧ�ĵ�����**/
double ActiveFunc1(double x)		//s�ͺ���
{
	return 1.0 / (1.0 + exp(-x));
}
double ActiveFuncD1(double x)
{
	return exp(-x) / pow(1.0 + exp(-x), 2);
}
double ActiveFunc2(double x)		//���Һ���
{
	return sin(x);
}
double ActiveFuncD2(double x)
{
	return cos(x);
}
double ActiveFunc3(double x)		//˫�����к���
{
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
double ActiveFuncD3(double x)
{
	return 4.0 / pow(exp(x) + exp(-x), 2);
}
double ActiveFunc4(double x)		//�����к���
{
	return atan(x);
}
double ActiveFuncD4(double x)
{
	return 1.0 / (1.0 + x * x);
}
int main(){
	trainInput = BPNetwork::Allocate2DArray(count_train,4);
	trainOutput = BPNetwork::Allocate2DArray(count_train,3);

	int nHidden;   //���ز����Ŀ
	int nFunc;
	
	cout<<"ѡ�񼤻��"<<endl;
	cout<<"1. s�ͺ���  2. ���Һ���  3. ˫�����к���  4. �����к���"<<endl;
	cin>>nFunc;
	cout<<"�������ز����Ŀ��";
	cin>>nHidden;
	double speed;  //ѧϰ����
	cout<<"����ѧϰ����(0~0.1)��";
	cin>>speed;
	if(!readTrainFile("train.dat"))
	{
		cout<<"�޷���ѵ��������"<<endl;
		return -1;
	}
	if(!readTestFile("test.txt"))
	{
		cout<<"�޷��򿪲���������"<<endl;
		return -1;
	}
	BPNetwork Bp;
	Bp.Create(4,nHidden,3);
	Bp.setSpeed(speed);     //����ѧϰ����
	switch(nFunc)
	{
	case 1:
		Bp.setFuncC(ActiveFunc1);
		Bp.setFuncD(ActiveFuncD1);
		Bp.setMaxMinOut(1.0,0.0);
		break;
	case 2:
		Bp.setFuncC(ActiveFunc2);
		Bp.setFuncD(ActiveFuncD2);
		Bp.setMaxMinOut(1.0,-1.0);
		break;
	case 3:
		Bp.setFuncC(ActiveFunc3);
		Bp.setFuncD(ActiveFuncD3);
		Bp.setMaxMinOut(1.0,-1.0);
		break;
	case 4:
		Bp.setFuncC(ActiveFunc4);
		Bp.setFuncD(ActiveFuncD4);
		Bp.setMaxMinOut(1.57,-1.57);
		break;
	default:
		break;
	}

	/**ѵ��������**/
	cout<<"����ѧϰ ���Ե�..."<<endl;
	int diedai = Bp.Train(trainInput,trainOutput,count_train);
	for(int i=0;i!=count_test;++i)
	{
		testOutput[i] = Bp.Classify(testInput[i]);
	}
	/**������Խ��**/
	writeTestResult("testResult.txt");
	cout<<"��������"<<diedai<<"�ε���"<<endl;
	return 0;
}