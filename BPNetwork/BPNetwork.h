#pragma once
typedef double (*Func)(double x);
class BPNetwork
{
public:
	BPNetwork();
	~BPNetwork();

	/** ����������**/
	bool Create(int nIn,int nHid,int nOut);

	/** ����ѧϰ����**/
	void setSpeed(double speed);

	/**��������������С��ֵ**/
	void setMaxMinOut(double max,double min);

	/** ѵ��BP������**/
	int Train(double **input,double **output,int size);

	/**������ֵ����**/
	void setFuncC(Func f);

	/**������ֵ�����ĵ���**/
	void setFuncD(Func f);

	/**�Բ������ݽ��з���**/
	int Classify(double *input);
	
	/**���붯̬��ά����**/
	static double** Allocate2DArray(int x,int y);
private:
	/**�������Ȩֵ����**/
	void RandWeight(double **weight_arry,int In,int Out);

	/**���������ֵ����**/
	void RandThreshold(double *The,int num);

	/**���0��1�����ֵ**/
	double GetRandom();

	/**����ǰ�����**/
	void CaculateForward();

	/**�������**/
	void CaculateError();

	/**����Ȩֵ����**/
	void AjustWeightArray();

	/**������ֵ����**/
	void AjustThreshold();

	/**������������**/
	void SetM_taget(double *target);

	/**�ж����������ʵ������Ƿ���ͬ**/
	bool isCorrect(double *input);
private:
	int nInput;            //�����ĵ�Ԫ��
	int nHidden;           //���ز�ĵ�Ԫ����
	int nOutput;           //�����ĵ�Ԫ����
	double m_speed;        //ѧϰ����
	double MinOut;         //����������ֵ
	double MaxOut;         //�������С��ֵ

	double **m_wInToHide;  //����㵽���ز��Ȩֵ����
	double **m_wHideToOut; //���ز㵽������Ȩֵ����

	double *m_HideThresHold;   //���ز����ֵ����
	double *m_OutThreshold;    //��������ֵ����

	double *m_Target;      //Ŀ������
	double *m_OutError;    //��������
	double *m_HiddenError; //���ز����

	double *m_HideInput;   //���ز������ֵ
	double *m_HideOutput;  //���ز�����ֵ
	double *m_OutInput;    //����������ֵ
	double *m_OutOutput;   //���������ֵ
	double *m_InInput;     //����㵥Ԫ��ֵ

	Func m_ActiveFuncC;    //�����
	Func m_ActiveFuncD;	   //������ĵ���
};

