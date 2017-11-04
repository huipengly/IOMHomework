#include <iostream>
#include "data.h"
using namespace std;
int main()
{
    for(int i = 0; i < 51; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cout << CustomDemand[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}