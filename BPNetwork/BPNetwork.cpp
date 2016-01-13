#include "BPNetwork.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
BPNetwork::BPNetwork()
{
	nInput = 4;           
	nHidden = 5;           
	nOutput = 6;          
	m_speed = 0.05;        

	m_wInToHide = NULL;  
	m_wHideToOut = NULL; 

	m_HideThresHold = NULL;   
	m_OutThreshold = NULL;

	m_Target = NULL;      
	m_OutError = NULL;    
	m_HiddenError = NULL; 

	m_HideInput = NULL;   
	m_HideOutput = NULL;  
	m_OutInput = NULL;    
	m_OutOutput = NULL;   

	m_ActiveFuncC = NULL;    
	m_ActiveFuncD = NULL;
}

BPNetwork::~BPNetwork()
{
	if(m_HideThresHold!=NULL)
		delete []m_HideThresHold;   //���ز����ֵ����
	if(m_OutThreshold!=NULL)
		delete []m_OutThreshold;    //��������ֵ����
	if(m_HideInput!=NULL)
		delete []m_HideInput;   //���ز������ֵ
	if(m_HideOutput!=NULL)
		delete []m_HideOutput;  //���ز�����ֵ
	if(m_OutInput!=NULL)
		delete []m_OutInput;    //����������ֵ
	if(m_OutOutput!=NULL)
		delete []m_OutOutput;   //���������ֵ

	if(m_Target!=NULL)
		delete []m_Target;
	if(m_OutError != NULL)
		delete []m_OutError;    
	if(m_HiddenError!=NULL)
		delete []m_HiddenError;

	if(m_wInToHide!=NULL){
	    for(int i =0;i<nInput;++i)
		delete []m_wInToHide[i];
		delete []m_wInToHide;
	}
	if(m_wHideToOut!=NULL)
	{
		for (int i=0;i<nHidden;++i)
		   delete []m_wHideToOut[i];
		delete []m_wHideToOut;
	}	    
}

bool BPNetwork::Create(int nIn,int nHid,int nOut)
{
	nInput = nIn;          //��ʼ��������Ĳ���           
	nHidden = nHid;           
	nOutput = nOut;
	/**���䶯̬�ռ�**/
	m_wInToHide = Allocate2DArray(nInput,nHidden);
	m_wHideToOut = Allocate2DArray(nHidden,nOutput);
	m_HideThresHold = new double[nHidden];   //���ز����ֵ����
	m_OutThreshold = new double[nOutput];    //��������ֵ����

	m_Target = new double[nOutput];      //Ŀ������
	m_OutError = new double[nOutput];    //��������
	m_HiddenError = new double[nHidden]; //���ز����

	m_InInput = new double[nInput];
	m_HideInput = new double[nHidden];   //���ز������ֵ
	m_HideOutput = new double[nHidden];  //���ز�����ֵ
	m_OutInput = new double[nOutput];    //����������ֵ
	m_OutOutput = new double[nOutput];   //���������ֵ

	/**��������������**/
	memset(m_Target,0,sizeof(double)*nOutput);
	memset(m_OutError,0,sizeof(double)*nOutput);
	memset(m_HiddenError,0,sizeof(double)*nHidden);
	memset(m_InInput,0,sizeof(double)*nInput);
	memset(m_HideInput,0,sizeof(double)*nHidden);
	memset(m_HideOutput,0,sizeof(double)*nHidden);
	memset(m_OutInput,0,sizeof(double)*nOutput);
	memset(m_OutOutput,0,sizeof(double)*nOutput);

	/**�������Ȩֵ����**/
	RandWeight(m_wInToHide,nInput,nHidden);
	RandWeight(m_wHideToOut,nHidden,nOutput);

	/**���������ֵ����**/
	RandThreshold(m_HideThresHold,nHidden);
	RandThreshold(m_OutThreshold,nOutput);

	return true;
}

void BPNetwork::setSpeed(double speed)
{
	m_speed = speed;
}

void BPNetwork::setMaxMinOut(double max,double min)
{
	MaxOut = max;
	MinOut = min;
}

int BPNetwork::Train(double **input,double **output,int size)
{
	int count = 0; //���ڼ�¼��������
	while(count<=500)
	{

		++count;
		for(int i =0;i!=size;++i)
		{
			memcpy(m_InInput,input[i],sizeof(double)*nInput);   //���������ĵ�Ԫ
			/**����Ŀ������**/
			SetM_taget(output[i]);    
			/**����ǰ�����**/
			CaculateForward();
				if(!isCorrect(output[i]))
				{
				/**���㷴�򴫲����**/
				CaculateError();

				/**����Ȩֵ����**/
				AjustWeightArray();

				/**������ֵ����**/
				AjustThreshold();

				}
		}
	}
	return count;        //���ص�������
}

void BPNetwork::setFuncC(Func f)
{
	m_ActiveFuncC = f;
}

void BPNetwork::setFuncD(Func f)
{
	m_ActiveFuncD = f;
}

int BPNetwork::Classify(double *input)
{
	int kind =0;
	memcpy(m_InInput,input,sizeof(double)*nInput);

	/**����ǰ�����**/
	CaculateForward();
	
	for(int i=0;i!=nOutput-1;++i)
	{
		if(m_OutOutput[i]<m_OutOutput[i+1])
			kind = i+1;
	}
	
	return kind;
}

double** BPNetwork::Allocate2DArray(int x,int y)
{
	double** tempArry;
	tempArry = new double*[x];
	for(int i = 0;i!=x;++i)
	{
		tempArry[i] = new double[y];
		memset(tempArry[i],0,sizeof(double)*y);
	}
	return tempArry;
}

void BPNetwork::RandWeight(double **weight_arry,int In,int Out)
{
	srand((unsigned)time(NULL));
	for(int ix = 0;ix!=In;++ix)
		for(int iy = 0;iy!=Out;++iy)
			weight_arry[ix][iy] = GetRandom()*0.1-0.05;
}

void BPNetwork::RandThreshold(double *The,int num)
{
	 srand((unsigned)time(NULL)); 
	 for (int ix=0;ix!=num;++ix)
	 {
		 The[ix] = GetRandom();
	 }
}

double BPNetwork::GetRandom()
{
	return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

void BPNetwork::CaculateForward()
{  
	memset(m_HideInput,0,sizeof(double)*nHidden);
	memset(m_OutInput,0,sizeof(double)*nOutput);
	/**�������������**/
	for(int i=0;i!=nHidden;++i)
	{
		for(int j=0;j!=nInput;++j)
			m_HideInput[i] += m_wInToHide[j][i]*m_InInput[j];
		/**�������ز����ֵ**/
		m_HideInput[i] += m_HideThresHold[i];
		/**�������ز�����**/
		m_HideOutput[i] = m_ActiveFuncC(m_HideInput[i]);
	}

	/**�������������**/
	for (int i =0;i!=nOutput;++i)
	{
		for (int j=0;j!=nHidden;++j)
		{
			m_OutInput[i] += m_wHideToOut[j][i]*m_HideOutput[j];
		}
		m_OutInput[i] += m_OutThreshold[i];
		m_OutOutput[i] = m_ActiveFuncC(m_OutInput[i]);
	}
}

void BPNetwork::CaculateError()
{
	/**���������Ԫ�ķ��򴫲����**/
	for(int i=0;i!=nOutput;++i)
	{
		m_OutError[i] = m_ActiveFuncD(m_OutInput[i])*(m_Target[i]-m_OutOutput[i]);
	}

	/**�������ز�ķ��򴫲����**/
	for(int i=0;i!=nHidden;++i)
	{
		double temp = 0.0;
		for(int j=0;j!=nOutput;++j)
		{
			temp += m_wHideToOut[i][j]*m_OutError[j];
		}
		m_HiddenError[i] = m_ActiveFuncD(m_HideInput[i])*temp;
	}
}

void BPNetwork::AjustWeightArray()
{
     /**��������㵽���ز������Ȩֵ**/
	for(int i=0;i!=nInput;++i)
		for (int j=0;j!=nHidden;++j)
		{
			m_wInToHide[i][j] += m_speed*m_HiddenError[j]*m_InInput[i];
		}
	/**�������ز㵽����������Ȩֵ**/
	for (int i=0;i!=nHidden;++i)
	{
		for (int j=0;j!=nOutput;++j)
		{
			m_wHideToOut[i][j] += m_speed*m_OutError[j]*m_HideOutput[i];
		}
	}
}

void BPNetwork::AjustThreshold()
{
	/**�������ز����ֵ**/
	for(int i=0;i!=nHidden;++i)
	{
		m_HideThresHold[i] += m_speed*m_HiddenError[i];
	}

	/**������������ֵ**/
	for(int i=0;i!=nOutput;++i)
	{
		m_OutThreshold[i] += m_speed*m_OutError[i];
	}
}

void BPNetwork::SetM_taget(double *target)
{
	int max = 0;
	for(int i =0;i!=nOutput;++i)   //�ҵ��ĸ���1
		if(target[i] == 1)
			max = i;          
	for(int i =0;i!=nOutput;++i)
		m_Target[i] = MinOut;
	m_Target[max] = MaxOut;
}

bool BPNetwork::isCorrect(double *input)
{
	int max = 0;
	for(int i = 1;i!=nOutput;++i)
        if(m_OutOutput[max]<m_OutOutput[i])
			max = i;
	if(input[max]==1.0)
		return true;
	return false;
}
