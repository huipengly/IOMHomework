#include <iostream>
#include <algorithm>
#include <ctime>
#include "pso.h"
#include "Rosenbrock.h"

using namespace std;

Particle::Particle(int size, double min, double max)
{
    d = size;
    x = new double[d];
    v = new double[d];
    bestx = new double[d];
    xmin = min;
    xmax = max;
    vmax = xmax - xmin;
    vmin = -vmax;
    for(int i = 0; i < d; i++)
    {
        x[i] = xmin + ((xmax - xmin) * (rand() / static_cast<double>(RAND_MAX)));
        v[i] = vmin + ((vmax - vmin) * (rand() / static_cast<double>(RAND_MAX)));
    }
}

Particle::~Particle()
{
    delete[] x;
    delete[] bestx;
    delete[] v;
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
    double value;
    value = Rosenbrock(x, d);
    if(value < bestvalue)
    {
        bestvalue = value;      //保存最优值
        copy(x, x + d, bestx);  //保存最优的位置
    }
    return value;
}

