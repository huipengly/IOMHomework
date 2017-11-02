#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "data.h"

using namespace std;

class Customer
{
protected:
    int mx;
    int my;
    int mdemand;
    int mnum;
public:
    int GetX()
    {
        return mx;
    }

    int GetY()
    {
        return my;
    }

    int GetDemand()
    {
        return mdemand;
    }

    int GetNum()
    {
        return mnum;
    }

    void SetX(int x)
    {
        mx = x;
    }
    
    void SetY(int y)
    {
        my = y;
    }

    void SetDemand(int demand)
    {
        mdemand = demand;
    }

    void SetNum(int num)
    {
        mnum = num;
    }
};

class Chromosome
{
protected:
    int *mGene;
    double mScore;
    int mSize;
    int mCarNum;    //车辆使用数目
    double mSumDis;
    int *mPlan;     //记录每辆车起点基因段
    //TODO:不要搞成类内的，初始化
    double **mCustomerDis;
    Customer *mCustomer;
    int mCapacity;

public:
	Chromosome(int size, double **customerDis, Customer *customer, int capacity) : mScore(0), mCarNum(0), mSumDis(0), mCustomerDis(customerDis), mCustomer(customer), mCapacity(capacity)
    {
        mSize = size;
        if(mSize >= 0)
        {
            mPlan = new int[mSize];
            mGene = new int[mSize];
            for(int i = 0; i < mSize; i++)
            {
                mGene[i] = i + 1;
            }
            srand(time(0));
            random_shuffle(mGene, mGene+mSize);
        }
    }

    Chromosome() : mScore(0), mCarNum(0), mSumDis(0)
    {

    }

    ~Chromosome()
    {
        delete[] mGene;
        delete[] mPlan;
    }

    void print()
	{
		for (int i = 0; i < mSize; i++)
		{
			cout << mGene[i] + 1 << " ";
		}
		cout << endl;
		cout << "NO.1 Car's Customer : ";
		for (int i(0), j(0); j < mSize; j++)
		{
			if (mPlan[i] == j)
			{
				//cout << "| ";
				cout << endl;
				cout << "NO." << i + 1 << " Car's Customer : ";
				i++;
			}
			cout << mGene[j] + 1 << " ";
		}
		cout << endl;
        cout << "mSize = " << mSize << endl;
        cout << "mCarNum = " << mCarNum << endl;
        cout << "mSumDis = " << mSumDis << endl;
    }

    int *GetGene()
    {
        return mGene;
    }

    double GetScore()
    {
        return mScore;
    }
    
    void SetScore(double score)
    {
        mScore = score;
    }

    int GetSize()
    {
        return mSize;
    }

    Chromosome &operator=(const Chromosome &obj)//克隆
    {
        mScore = obj.mScore;
        mSize = obj.mSize;
        
        delete[] mGene;
        mGene = new int[mSize];

        for(int i = 0; i < mSize; i++)
        {
            mGene[i] = obj.mGene[i];
        }

        return *this;
    }

    void mutation()//变异 2-opt
    {
        int rand1 = rand()%mSize;
        int rand2 = rand()%mSize;
        if(rand1 != rand2)
        {
            int tmp = mGene[rand1];
            mGene[rand1] = mGene[rand2];
            mGene[rand2] = tmp;
        }
    }

    //设置单个染色体得分
    void CalculateDistance()
    {
      //  int *gene = chro.GetGene();
      //  int size = chro.GetSize();
        int sumDemand = 0;
        if(mGene != NULL)
        {
            for(int i = 0; i < mSize; i++)
            {
                sumDemand += mCustomer[mGene[i]].GetDemand();
                if(sumDemand > mCapacity)//超出一辆车载重
                {
                    mPlan[mCarNum] = i;
                    i--;    //回退，当前需求由下一辆车来满足
                    sumDemand = 0;
                    mSumDis += mCustomerDis[0][mGene[i-1]];    //加上最后一个点回起始点的距离
                    mCarNum++;
                }
                else
                {
					if (sumDemand == mCustomer[mGene[i]].GetDemand())
                    {
                        mSumDis += mCustomerDis[0][mGene[i]];
                    }
                    else
                    {
                        mSumDis += mCustomerDis[mGene[i]][mGene[i-1]];
                    }
                }
				if ((i + 1) == mSize)
				{
					mSumDis += mCustomerDis[0][mGene[i]];
				}
            }
        }
    }
};

class GeneticAlgorithm
{
protected:
    Chromosome *mPopulation; //种群
    int mNP;                //种群个数
    int mNG;                //最大进化代数
    int mGeneSize;          //基因长度，定长
    int mPM;                //变异率
    int mPC;                //交叉率
    int mGeneration;        //进化代数
	double **mCustomerDis;
	Customer *mCustomer;
	int mCapacity;

public:
    GeneticAlgorithm(int NP, int NG, int GeneSize, int PM, int PC, double **customerDis, Customer *customer, int capacity)
		: mNP(NP), mNG(NG), mGeneSize(GeneSize), mPM(PM), mPC(PC), mGeneration(1), mCustomerDis(customerDis), mCustomer(customer), mCapacity(capacity)
    {
        mPopulation = new Chromosome[mNP];
        for(int i = 0; i < mNP; i++)
        {
           // Chromosome *tmp = new Chromosome(mGeneSize);
			mPopulation[i] = *(new Chromosome(mGeneSize, mCustomerDis, mCustomer, mCapacity));
        }
    }

    ~GeneticAlgorithm()
    {
        delete[] mPopulation;
    }

    Chromosome *GetPopulation()
    {
        return mPopulation;
    }

    void print()
    {
        cout << mPopulation << endl;
    }

    //计算种群得分
    void CaculteScore()
    {

    }


};

int main()
{
    //读数据
    int dimension = 51;
    int capacity = 160;
    Customer *customer = new Customer[dimension];
    for(int i = 0; i < dimension; i++)
    {
        customer[i].SetX(CustomerNode[i][1]);
        customer[i].SetY(CustomerNode[i][2]);
        customer[i].SetNum(i);
        customer[i].SetDemand(CustomerDemand[i][1]);
    }
    double **CustomerDis = new double*[dimension];//客户到客户间的距离
    for(int i = 0; i < dimension; i++)
    {
        CustomerDis[i] = new double[dimension];
    }
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            CustomerDis[i][j] = sqrt(pow((customer[i].GetX() - customer[j].GetX()), 2) + \
                                     pow((customer[i].GetY() - customer[j].GetY()), 2));
        }
    }

	Chromosome chro(3-1, CustomerDis, customer, capacity);
	//int *a = chro.GetGene();
	//for (int i = 0; i < chro.GetSize(); i++)
	//{
	//	cout << "a[" << i << "]= " << a[i] << endl;
	//}
    chro.CalculateDistance();
    chro.print();

    
     //for(int i = 0; i < dimension; i++)
     //{
     //   cout << customer[i].GetDemand() << " ";
     //    cout << endl;
     //}

//测试克隆
/*    int size = 15;
    Chromosome test(size);
    int *a = test.GetGene();
    for(int i = 0; i < test.GetSize(); i++)
    {
        cout << "a[" << i << "]= " << a[i] << endl;
    }
    int s = 3;
    Chromosome test2(s);
    int *b = test2.GetGene();
    for(int i = 0; i < test2.GetSize(); i++)
    {
        cout << "b[" << i << "]= " << b[i] << endl;
    }
    test2 = test;
    int *c = test2.GetGene();
    for(int i = 0; i < test2.GetSize(); i++)
    {
        cout << "c[" << i << "]= " << c[i] << endl;
    }
*/

//测试变异
/*    int size = 10;
    Chromosome test3(size);
    int *d = test3.GetGene();
    for(int i = 0; i < test3.GetSize(); i++)
    {
        cout << "d[" << i << "]= " << d[i] << endl;
    }
    test3.mutation();
    int *e = test3.GetGene();
    for(int i = 0; i < test3.GetSize(); i++)
    {
        cout << "e[" << i << "]= " << e[i] << endl;
    }
*/

//测试类指针
/*    int size = 4;
    Chromosome *test;
    test = new Chromosome(size);
    int *a = test->GetGene();
    for(int i = 0; i < test->GetSize(); i++)
    {
        cout << "a[" << i << "]= " << a[i] << endl;
    }
*/

//测试初始化种群
/*    GeneticAlgorithm Gtest(15,1,115,0,0);
    Gtest.print();
    Chromosome *Gp = Gtest.GetPopulation();
    cout << Gp[10].GetSize() << endl;
*/
	cout << "press any key to continue..." << endl;
	getchar();
    return 0;
}