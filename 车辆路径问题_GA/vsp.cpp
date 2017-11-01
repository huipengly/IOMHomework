#include <iostream>
#include <algorithm>
#include<ctime>
#include<cstdlib>

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

    
};

int main()
{
    int size = 15;
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

    return 0;
}