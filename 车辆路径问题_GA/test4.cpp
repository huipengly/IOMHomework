#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    double rand1[2];
    rand1[0] = rand()/double(RAND_MAX);
    rand1[1] = rand()/double(RAND_MAX);
    cout << rand1[0] <<endl;
    cout << rand1[1] <<endl;
    return 0;
}