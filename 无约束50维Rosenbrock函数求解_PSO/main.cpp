#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "Rosenbrock.h"
#include "pso.h"

using namespace std;
using namespace chrono;

int main()
{
    srand(time(0));

	auto start = system_clock::now();

    PSO pso(40, 50, -30, 30, 1000);
    pso.run();

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "»¨·ÑÁË"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "Ãë" << endl;
	cout << "press any key to kill me..." << endl;
	getchar();

    return 0;
}
