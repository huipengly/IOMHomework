#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Chromosom
{
protected:
    int *mGene;
    double mScore;
    int mSize;

public:
    Chromosom(int size)
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

    Chromosom()
    {

    }

    ~Chromosom()
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

    Chromosom &operator=(const Chromosom &obj)//克隆
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
    Chromosom *mPopulation; //种群
    int mNP;                //种群个数
    int mNG;                //最大进化代数
    int mGeneSize;          //基因长度，定长
    int mPM;                //变异率
    int mPC;                //交叉率
    int mGeneration;        //进化代数

public:
    GeneticAlgorithm(int NP, int NG, int GeneSize, int PM, int PC)
        : mNP(NP), mNG(NG), mGeneSize(GeneSize), mPM(PM), mPC(PC), mGeneration(1)
    {
        mPopulation = new Chromosom[mNP];
        for(int i = 0; i < mNP; i++)
        {
            Chromosom *tmp = new Chromosom(mGeneSize);
            mPopulation[i] = *tmp;
        }
    }

    ~GeneticAlgorithm()
    {
        delete[] mPopulation;
    }

    Chromosom *GetPopulation()
    {
        return mPopulation;
    }

    void print()
    {
        cout << mPopulation << endl;
    }
};

int main()
{
//测试克隆
/*    int size = 15;
    Chromosom test(size);
    int *a = test.GetGene();
    for(int i = 0; i < test.GetSize(); i++)
    {
        cout << "a[" << i << "]= " << a[i] << endl;
    }
    int s = 3;
    Chromosom test2(s);
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
    Chromosom test3(size);
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
    Chromosom *test;
    test = new Chromosom(size);
    int *a = test->GetGene();
    for(int i = 0; i < test->GetSize(); i++)
    {
        cout << "a[" << i << "]= " << a[i] << endl;
    }
*/

//测试初始化种群
/*    GeneticAlgorithm Gtest(15,1,115,0,0);
    Gtest.print();
    Chromosom *Gp = Gtest.GetPopulation();
    cout << Gp[10].GetSize() << endl;
*/

    return 0;
}