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
    copy(x, x + d, bestx);  //初始化最优
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
        copy(x, x + d, bestx);  //保存最优的位置
    }
    return value;
}

void Particle::UpdateSpeed(double *bestpx)
{
    for(int i = 0; i < d; i++)
    {
        double kxi = (rand() / static_cast<double>(RAND_MAX));
        double eta = (rand() / static_cast<double>(RAND_MAX));
        v[i] = omega*v[i] + c1 * kxi * (bestx[i] - x[i]) + c2 * eta * (bestpx[i] - x[i]);
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
}

void PSO::print()
{
    cout << "This is " << gen + 1 << "'s generation" << endl;
    cout << "best value = " << bestpvalue << endl;
}

void PSO::findbest()
{
    for(int i = 0; i < n; i++)
    {
        double value = p[i].UpdateValue();
        if(bestpvalue > value)
        {
            copy(p[i].getx(), p[i].getx() + dsize, bestpx);
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
    SwarmMove();
    findbest();
    for(int i = 0; i < gen; i++)
    {
        SwarmUpdateSpeed();
        SwarmMove();
        findbest();
        print();
    }

    cout << "final result is:" << endl;
    cout << "best value = " << bestpvalue << endl;
    for(int i = 0; i < 0; i++)
    {
        cout << "x" << i+1 << " = " << bestpx[i] << endl;
    }
}