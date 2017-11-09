#include <iostream>
#include <algorithm>
#include <ctime>
#include "Rosenbrock.h"
#include "pso.h"

using namespace std;

int main()
{
    srand(time(0));

    // Particle p1;
    // p1.init(3, -30, 30);
    // p1.UpdateValue();
    // p1.print();
    // p1.move();
    // p1.UpdateValue();
    // p1.print();

    // PSO pso(2, 3, -30, 30);
    // pso.print();

    PSO pso(10, 2, -30, 30, 10);
    pso.run();

    return 0;
}