#include <iostream>
#include "Rosenbrock.h"

using namespace std;

int main()
{
    double a[4] = {-1,1,1,1};

    cout << Rosenbrock(a,4) << endl;
}