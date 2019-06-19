#ifndef OPERATII_HPP_INCLUDED
#define OPERATII_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
class Matrix
{
private:
    int numberLines,numberColumns;
    vector<vector<float> > matrix;
public:
    Matrix();
    Matrix(int,int );
    void matrixReading();
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
    friend istream& operator >>(istream&,Matrix&);
    friend ostream& operator <<(ostream&, Matrix&);
    Matrix operator=(const Matrix&);
    Matrix getCofactor(Matrix,int,int,int);
    float determinant();
    Matrix transposed();
    Matrix inverse();
    void adjoint(Matrix);
    int getNumberLines(){return numberLines;}
    int getNumberColumns(){return numberColumns;}
    void setNumberLines(int nrLines){numberLines = nrLines;}
    void setNumberColumns(int nrColumns){numberColumns = nrColumns;}
    void setMatrix(vector<vector<float> > matrixAux){matrix = matrixAux; }
    vector<vector<float> > getMatrix(){return matrix;}
};
//class constructor without parameters
Matrix::Matrix()
{
    numberLines = 0;
    numberColumns = 0;
}
//class contructor with parameters
Matrix::Matrix(int lines, int columns)
{
    numberLines = lines;
    numberColumns = columns;
}
// overloading the operator >>
istream& operator>> (istream&in,Matrix& matrixAux)
{
    cout<<"The number of lines is: ";
    in>> matrixAux.numberLines;
    cout<<"The number of columns is: ";
    in>>matrixAux.numberColumns;
    matrixAux.matrix.resize(matrixAux.numberLines);
    for(int i = 0; i < matrixAux.numberLines; i++)
    {
        matrixAux.matrix[i].resize(matrixAux.numberLines);
        for(int j = 0; j < matrixAux.numberLines; j++)
            in>>matrixAux.matrix[i][j];
    }
    return in;
}
//overloading the operator <<
ostream& operator<<(ostream&out, Matrix& matrixAux)
{
    for(int i = 0; i < matrixAux.numberLines; i++)
    {
        for(int j = 0; j < matrixAux.numberColumns; j++)
            out<<matrixAux.matrix[i][j]<<" ";
        out<<endl;
    }
    return out;
}
//function in which I read the data in the file about an object
void Matrix::matrixReading()
{
    ifstream fisier("data.txt");
    fisier >> numberLines;
    fisier >> numberColumns;
    float termen;
    for (int i = 0; i < numberLines; i++)
    {
        vector<float> linie;
        for(int j = 0; j < numberColumns; j++)
        {
            fisier>>termen;
            linie.push_back(termen);

        }
        matrix.push_back(linie);
    }
}
//overloading the operator =
Matrix Matrix::operator=(const Matrix& matrixAux)
{
    if (this != &matrixAux)
    {
        matrix = matrixAux.matrix;
        numberLines = matrixAux.numberLines;
        numberColumns = matrixAux.numberColumns;
    }
    return *this;

}
//overloading the operator +
Matrix Matrix::operator+(Matrix& matrixAux)
{
    Matrix result;
    for(int i = 0; i < numberLines; i++)
    {
        vector<float> vectorAux;
        for(int j = 0; j < numberColumns; j++)
        {
            float termen = matrix[i][j] + matrixAux.matrix[i][j];
            vectorAux.push_back(termen);
        }
        result.matrix.push_back(vectorAux);
    }
    result.numberLines = numberLines;
    result.numberColumns = numberColumns;
    return result;
}
//overloading the operator -
Matrix Matrix::operator-(Matrix& matrixAux)
{
    Matrix result;
    for(int i = 0; i < numberLines; i++)
    {
        vector<float> vectorAux;
        for(int j = 0; j < numberColumns; j++)
        {
            float  termen = matrix[i][j] - matrixAux.matrix[i][j];
            vectorAux.push_back(termen);
        }
        result.matrix.push_back(vectorAux);
    }
    result.numberLines = numberLines;
    result.numberColumns = numberColumns;
    return result;
}
//overloading the operator *
Matrix Matrix::operator*(Matrix& matrixAux)
{
    Matrix result;
    for(int i = 0; i < numberLines; i++)
    {
        vector<float> vectorAux;
        for(int j = 0; j < matrixAux.numberColumns; j++)
        {
            float sum = 0;
            for(int k = 0; k < matrixAux.numberColumns; k++)
                sum += matrix[i][k] * matrixAux.matrix[k][j];
            vectorAux.push_back(sum);
        }
        result.matrix.push_back(vectorAux);
    }
    return result;
}
//in this function I create the transposed matrix
Matrix Matrix::transposed()
{
    Matrix matrixTransposed;

    for(int i = 0; i < numberLines; i++)
    {
        vector<float> vectorAux;

        for(int j = 0; j < numberColumns; j++)
        {

            vectorAux.push_back(matrix[j][i]);

        }
        matrixTransposed.matrix.push_back(vectorAux);

    }
    matrixTransposed.numberLines = numberLines;
    matrixTransposed.numberColumns = numberColumns;

    return matrixTransposed;
}
//function to get cofactor of matrix
Matrix Matrix::getCofactor(Matrix matrixTrans,int line, int column, int nrLines)
{
    Matrix matrixAux;
    matrixAux.matrix.resize(nrLines-1);
    for(int i = 0; i < nrLines-1; i++)
        matrixAux.matrix[i].resize(nrLines-1);
    int i = 0, j = 0;
    for (int row = 0; row < nrLines; row++)
    {
        for (int col = 0; col < nrLines; col++)
        {
            if (row != line && col != column)
            {
                matrixAux.matrix[i][j] = matrixTrans.matrix[row][col];
                j = j + 1;
                if (j == nrLines - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    matrixAux.numberColumns = nrLines - 1;
    matrixAux.numberLines = nrLines - 1;
    return matrixAux;
}
//calculate the matrix determinant by using the getCofactor function
float Matrix::determinant()
{   Matrix matrixAux;
        matrixAux.matrix.resize(numberColumns);
    for(int i = 0; i < numberColumns; i++)
        matrixAux.matrix[i].resize(numberColumns);
    int determ = 0;
    if (numberColumns == 1)
        return matrix[0][0];
    int sign = 1;
    for (int i = 0; i < numberColumns; i++)
    {   matrixAux = getCofactor((*this), 0, i, numberColumns);
        determ += sign * matrix[0][i] * matrixAux.determinant();
        sign = -sign;
    }

    return determ;
}
////in this function I create the adjoint matrix
void Matrix::adjoint(Matrix matrixTrans)
{
    if (numberColumns == 1)
    {
        matrix[0][0] = 1;
        return;
    }
    Matrix matrixAux;
    int sign = 1;
    matrix.resize(numberColumns);
    for (int i = 0; i < numberLines; i++)
    {
        matrix[i].resize(numberColumns);
        for (int j = 0; j < numberLines; j++)
        {
            matrixAux = getCofactor(matrixTrans,i, j, numberLines);
            sign = ((i+j)%2==0)? 1: -1;
            matrix[i][j] = (sign)*(matrixAux.determinant());

        }
    }
}
//in this function I create the inverse matrix using the functions defined above
Matrix Matrix::inverse()
{   cout<<"intru aici"<<endl;
    Matrix matrixAdj,matrixInv;
    matrixAdj.numberColumns = numberColumns;
    matrixAdj.numberLines = numberLines;
    matrixInv.numberColumns = numberColumns;
    matrixInv.numberLines = numberLines;
    matrixInv.matrix.resize(numberColumns);
    float determ = determinant();
    for(int i = 0; i < numberColumns; i++)
        matrixInv.matrix[i].resize(numberColumns);
    matrixAdj.adjoint(transposed());
    for (int i = 0; i < numberColumns; i++)
    {
        for (int j = 0; j < numberColumns; j++)
            matrixInv.matrix[i][j] = matrixAdj.matrix[i][j] / determ;
    }

    return matrixInv;
}
#endif // OPERATII_HPP_INCLUDED
