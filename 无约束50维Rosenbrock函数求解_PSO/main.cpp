#include <iostream>
#include <algorithm>
#include <ctime>
#include "Rosenbrock.h"
#include "pso.h"

using namespace std;

int main()
{
    srand(time(0));

    Particle p1(3, -30, 30);
    p1.print();
    p1.move();
    p1.print();


    return 0;
}