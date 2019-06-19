#include <iostream>
#include "operatii.hpp"

using namespace std;

int main()
{
    Matrix a;
    Matrix b;
    Matrix c;
    Matrix d;
    cin>>a;
    a.adjoint(a);
    c=a;
    cout<<c;
    return 0;
}
