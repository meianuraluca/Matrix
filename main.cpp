#include <iostream>
#include "operatii.hpp"

using namespace std;

int main()
{
    Matrix a;
    Matrix b;
    Matrix c;
    Matrix d;
    a.matrixReading();
    c = a.inverse();
    cout<<c;
    return 0;
}
