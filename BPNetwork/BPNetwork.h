#pragma once
typedef double (*Func)(double x);
class BPNetwork
{
public:
	BPNetwork();
	~BPNetwork();

	/** 创建神经网络**/
	bool Create(int nIn,int nHid,int nOut);

	/** 设置学习速率**/
	void setSpeed(double speed);

	/**设置输出的最大最小阈值**/
	void setMaxMinOut(double max,double min);

	/** 训练BP神经网络**/
	int Train(double **input,double **output,int size);

	/**设置阈值函数**/
	void setFuncC(Func f);

	/**设置阈值函数的导数**/
	void setFuncD(Func f);

	/**对测试数据进行分类**/
	int Classify(double *input);
	
	/**申请动态二维数组**/
	static double** Allocate2DArray(int x,int y);
private:
	/**随机分配权值矩阵**/
	void RandWeight(double **weight_arry,int In,int Out);

	/**随机分配阈值向量**/
	void RandThreshold(double *The,int num);

	/**获得0到1的随机值**/
	double GetRandom();

	/**进行前向计算**/
	void CaculateForward();

	/**计算误差**/
	void CaculateError();

	/**调整权值矩阵**/
	void AjustWeightArray();

	/**调整阈值矩阵**/
	void AjustThreshold();

	/**设置期望向量**/
	void SetM_taget(double *target);

	/**判断期望输出与实际输出是否相同**/
	bool isCorrect(double *input);
private:
	int nInput;            //输入层的单元数
	int nHidden;           //隐藏层的单元个数
	int nOutput;           //输出层的单元个数
	double m_speed;        //学习速率
	double MinOut;         //输出的最大阈值
	double MaxOut;         //输出的最小阈值

	double **m_wInToHide;  //输入层到隐藏层的权值矩阵
	double **m_wHideToOut; //隐藏层到输出层的权值矩阵

	double *m_HideThresHold;   //隐藏层的阈值数组
	double *m_OutThreshold;    //输出层的阈值数组

	double *m_Target;      //目标向量
	double *m_OutError;    //输出层误差
	double *m_HiddenError; //隐藏层误差

	double *m_HideInput;   //隐藏层的输入值
	double *m_HideOutput;  //隐藏层的输出值
	double *m_OutInput;    //输出层的输入值
	double *m_OutOutput;   //输出层的输出值
	double *m_InInput;     //输入层单元的值

	Func m_ActiveFuncC;    //激活函数
	Func m_ActiveFuncD;	   //激活函数的导数
};

