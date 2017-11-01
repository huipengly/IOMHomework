#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>

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

public:
    Chromosome(int size)
    {
        mSize = size;
        if(mSize >= 0)
        {
            mGene = new int[mSize];
            for(int i = 0; i < mSize; i++)
            {
                mGene[i] = i + 1;
            }
            srand(time(0));
            random_shuffle(mGene, mGene+mSize);
        }
    }

    Chromosome()
    {

    }

    ~Chromosome()
    {
        delete[] mGene;
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
    //TODO:不要搞成类内的
    double **mCustomerDis;
    Customer *mCustomer;
    int mCapacity;

public:
    GeneticAlgorithm(int NP, int NG, int GeneSize, int PM, int PC, double **CustomerDis, Customer *customer, int capacity)
        : mNP(NP), mNG(NG), mGeneSize(GeneSize), mPM(PM), mPC(PC), mGeneration(1), mCustomerDis(CustomerDis), mCustomer(customer), mCapacity(capacity)
    {
        mPopulation = new Chromosome[mNP];
        for(int i = 0; i < mNP; i++)
        {
           // Chromosome *tmp = new Chromosome(mGeneSize);
            mPopulation[i] = *(new Chromosome(mGeneSize));
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

    //设置单个染色体得分
    void setChromosomeScore(Chromosome chro)
    {
        int *gene = chro.GetGene();
        int size = chro.GetSize();
        if(gene == NULL)
        {
            int CarNum = 0;
            int sumDemand = 0;
            int sumDis = 0;
            for(int i = 0; i < size; i++)
            {
                sumDemand += mCustomer[gene[i]].GetDemand();
                if(sumDemand > mCapacity)//超出一辆车载重
                {
                    i--;    //回退，当前需求由下一辆车来满足
                    sumDemand = 0;
                    sumDis += mCustomerDis[0][gene[i-1]];    //加上最后一个点回起始点的距离
                    CarNum++;    //车辆使用数目
                }
                else
                {
                    if(sumDemand == 0)
                    {
                        sumDis += mCustomerDis[0][gene[i]];
                    }
                    else
                    {
                        sumDis += mCustomerDis[gene[i]][gene[i-1]];
                    }
                }
            }
           //TODO: chro.SetScore()
        }
    }
};

int main()
{
    //读数据
    int dimension = 2;
    int capacity = 160;
    Customer *customer = new Customer[dimension];
    customer[0].SetX(0);
    customer[0].SetY(0);
    customer[1].SetX(1);
    customer[1].SetY(0);
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
    
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
           cout << CustomerDis[i][j] << " ";
        }
        cout << endl;
    }

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

    return 0;
}