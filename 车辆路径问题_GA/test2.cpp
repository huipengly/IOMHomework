#include <iostream>
#include <algorithm>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
//    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int *a;
    a = new int[9];

    for (unsigned i = 0; i < 9; i++)
    {
        a[i] = i + 1;
        cout << a[i];
    }
    cout << endl;
    srand(time(0));
    random_shuffle(a,a+9);

    for (unsigned i = 0; i < 9; i++)
    {
        cout << a[i];
    }
    cout << endl;
    random_shuffle(a,a+9);

    for (unsigned i = 0; i < 9; i++)
    {
        cout << a[i];
    }
    cout << endl;
    random_shuffle(a,a+9);

    for (unsigned i = 0; i < 9; i++)
    {
        cout << a[i];
    }
    cout << endl;
}