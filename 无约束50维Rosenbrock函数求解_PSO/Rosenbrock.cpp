#include "Rosenbrock.h"
#include <math.h>
#include <iostream>

using namespace std;

double Rosenbrock(double *x, int n)
{
    if(n == 2)
    {
        return (100*pow(x[n - 1]-pow(x[n - 2], 2), 2) + pow(x[n - 2] - 1, 2));
    }
    else if (n > 2)
    {
        return ((100*pow(x[n - 1]-pow(x[n - 2], 2), 2) + pow(x[n - 2] - 1, 2)) + Rosenbrock(x, n - 1));
    }
    else
    {
        cout << "Rosenbrock have a wrong input n" << endl;
        return -1;
    }
}