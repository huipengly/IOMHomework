#include <iostream>
#include <algorithm>
#include <ctime>
#include "pso.h"
#include "Rosenbrock.h"

using namespace std;

Particle::Particle() : x(NULL), v(NULL), bestx(NULL)
{

}

Particle::~Particle()
{
    if(x != NULL)
    {
        delete[] x;
    }
    if(bestx != NULL)
    {
        delete[] bestx;
    }
    if(v != NULL)
    {
        delete[] v;
    }
}

void Particle::print()
{
    for(int i = 0; i < d; i++)
    {
        cout << "x" << i+1 << " = " << x[i] << endl;
    }
    for(int i = 0; i < d; i++)
    {
        cout << "v" << i+1 << " = " << v[i] << endl;
    }
    cout << "value is " << value << endl;
}

void Particle::init(int dsize, double min, double max)
{
    d = dsize;
    x = new double[d];
    v = new double[d];
    bestx = new double[d];
    xmin = min;
    xmax = max;
    vmax = xmax - xmin;
    vmin = -vmax;
    c1 = 0.75;
    c2 = 0.75;
    omega = 1;
    for(int i = 0; i < d; i++)
    {
        x[i] = xmin + ((xmax - xmin) * (rand() / static_cast<double>(RAND_MAX)));
        v[i] = vmin + ((vmax - vmin) * (rand() / static_cast<double>(RAND_MAX)));
    }
    bestvalue = 1e10;
    //copy(x, x + d, bestx);  //初始化最优
    for(int i = 0; i < d; i++)
    {
        bestx[i] = x[i];
    }
}

void Particle::move()
{
    for(int i = 0; i < d; i++)
    {
        x[i] += v[i];
        if(x[i] > xmax)
        {
            x[i] = xmax;
        }
        if(x[i] < xmin)
        {
            x[i] = xmin;
        }
    }
}

double Particle::UpdateValue()
{
    value = Rosenbrock(x, d);
    if(value < bestvalue)
    {
        bestvalue = value;      //保存最优值
        //copy(x, x + d, bestx);  //保存最优的位置
        for(int i = 0; i < d; i++)
        {
            bestx[i] = x[i];
        }
    }
    return value;
}

void Particle::UpdateSpeed(double *bestpx)
{
    for(int i = 0; i < d; i++)
    {
        double kxi = (rand() / static_cast<double>(RAND_MAX));
        double eta = (rand() / static_cast<double>(RAND_MAX));
        v[i] = omega*v[i] + c1 * kxi * (bestx[i] - x[i]) + c2 * eta * (bestpx[i] - x[i]);//FIXME:段错误
    }
}

double* Particle::getx()
{
    return x;
}

PSO::PSO(int nsize, int dsize, int min, int max, int gen)
{
    n = nsize;
    this->dsize = dsize;
    this->min = min;
    this->max = max;
    this->gen = gen;
    p = new Particle[n];
	bestpx = new double[n];

    for(int i = 0; i < n; i++)
    {
        p[i].init(dsize, min, max);
    }

    bestpvalue = 1e10;
}

PSO::~PSO()
{
    if(p != NULL)
    {
        delete[] p;
    }
	if (bestpx != NULL)
	{
		delete[] bestpx;
	}
}

void PSO::print(int i)
{
    cout << "This is " << i + 1 << "'s generation" << endl;
    cout << "best value = " << bestpvalue << endl;
}

void PSO::findbest()
{
//    cout << "n = " << n << endl;
    for(int i = 0; i < n; i++)
    {
        double value = p[i].UpdateValue();
        double *tmpx;
        tmpx = p[i].getx();
        // cout << tmpx[0] << endl;
        // cout << "i = " << i << endl;
        if(bestpvalue > value)
        {
            //copy(tmpx, tmpx + dsize, bestpx);
            for(int j = 0; j < n; j++)
            {
//				cout << tmpx[j] << endl;
                bestpx[j] = tmpx[j];//FIXME:段错误
//				bestpx[j] = 0.5;
            }
            bestpvalue = value;
        }
    }
}

void PSO::SwarmMove()
{
    for(int i = 0; i < n; i++)
    {
        p[i].move();
    }
}

void PSO::SwarmUpdateSpeed()
{
    for(int i = 0; i < n; i++)
    {
        p[i].UpdateSpeed(bestpx);
    }
}

void PSO::run()
{

	////测试已知三维最优解
	//double *a = p[0].getx();
	//a[0] = 1;
	//a[1] = 1;
	//a[2] = 1;

	findbest();
    SwarmMove();
    findbest();
    for(int i = 0; i < gen; i++)
    {
        SwarmUpdateSpeed();
        SwarmMove();
        findbest();
        print(i);
    }

    cout << "final result is:" << endl;
    cout << "best value = " << bestpvalue << endl;
    for(int i = 0; i < dsize; i++)
    {
        cout << "x" << i+1 << " = " << bestpx[i] << endl;
    }
}