#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "C:\Users\Raluca\Desktop\New folder\matrice\test\catch.hpp"
#include "C:\Users\Raluca\Desktop\New folder\matrice\operatii.hpp"
#include<vector>
#include<fstream>

//in this function check if two matrices are equal
int equall(Matrix a1, Matrix b2){
  int ok = 1;
  vector<vector<float> >a;
  vector<vector<float> >b;
  a=a1.getMatrix();
  b=b2.getMatrix();

  for(int i = 0; i < a1.getNumberLines();i++)
    for(int j = 0; j< a1.getNumberColumns();j++)
        if(a[i][j] != b[i][j])
            {ok = 0;
            }
  return ok;

}

TEST_CASE() {
    Matrix matrix1;
    int nrLines, nrColumns;
    ifstream fisier("data1.txt");
    //read the first matrix
    fisier >> nrLines;
    fisier >> nrColumns;
    matrix1.setNumberLines(nrLines);
    matrix1.setNumberColumns(nrColumns);
    vector<vector<float> >matrixAux;
    matrixAux.resize(nrLines);
    float termen;
    for (int i = 0; i < nrLines; i++)
    {matrixAux[i].resize(nrColumns);
        for(int j = 0; j < nrColumns; j++)
            fisier>>matrixAux[i][j];

    }
    matrix1.setMatrix(matrixAux);

    //operator=
    Matrix equalMatrix;
    equalMatrix = matrix1;

    //read the second matrix
    Matrix matrix2;
    int nrLines1,nrColumns1;
    fisier >> nrLines1;
    fisier >> nrColumns1;
    matrix1.setNumberLines(nrLines1);
    matrix1.setNumberColumns(nrColumns1);
    vector<vector<float> >matrixAux1;
    matrixAux1.resize(nrLines1);
    for (int i = 0; i < nrLines1; i++)
    {matrixAux1[i].resize(nrColumns);
        for(int j = 0; j < nrColumns1; j++)
            fisier>>matrixAux1[i][j];
    }
    matrix2.setMatrix(matrixAux1);

    //read the matrix sum
    Matrix matrixSum;
    int nrLinesSum,nrColumnsSum;
    fisier >> nrLinesSum;
    fisier >> nrColumnsSum;
    matrix1.setNumberLines(nrLinesSum);
    matrix1.setNumberLines(nrColumnsSum);
    vector<vector<float> >matrixAuxSum;
    matrixAuxSum.resize(nrLinesSum);
    for (int i = 0; i < nrLinesSum; i++)
    {matrixAuxSum[i].resize(nrColumnsSum);
        for(int j = 0; j < nrColumnsSum; j++)
            fisier>>matrixAuxSum[i][j];
    }

    matrixSum.setMatrix(matrixAuxSum);

    //operator+
    Matrix result;
    result = matrix1 + matrix2;

    //read the matrix difference
    Matrix matrixDifference;
    int nrLinesDifference,nrColumnsDifference;
    fisier >> nrLinesDifference;
    fisier >> nrColumnsDifference;
    matrix1.setNumberLines(nrLinesDifference);
    matrix1.setNumberColumns(nrColumnsDifference);
    vector<vector<float> >matrixAuxDifference;
    matrixAuxDifference.resize(nrLinesDifference);
    for (int i = 0; i < nrLinesDifference; i++)
    {matrixAuxDifference[i].resize(nrColumnsDifference);
        for(int j = 0; j < nrColumnsDifference; j++)
            fisier>>matrixAuxDifference[i][j];
    }
    matrixDifference.setMatrix(matrixAuxDifference);
    cout<<matrixDifference;

    //operator-
    Matrix result1;
    result1=matrix1-matrix2;

    //read the matrix product
    Matrix matrixProduct;
    int nrLinesProduct,nrColumnsProduct;
    fisier >> nrLinesProduct;
    fisier >> nrColumnsProduct;
    matrix1.setNumberLines(nrLinesProduct);
    matrix1.setNumberColumns(nrColumnsProduct);
    vector<vector<float> >matrixAuxProduct;
    matrixAuxProduct.resize(nrLinesProduct);
    for (int i = 0; i < nrLinesProduct; i++)
    {matrixAuxProduct[i].resize(nrColumnsProduct);
        for(int j = 0; j < nrColumnsProduct; j++)
            fisier>>matrixAuxProduct[i][j];
    }
    matrixProduct.setMatrix(matrixAuxProduct);

    //operator*
    Matrix result2;
    result2 = matrix1 * matrix2;

    REQUIRE( equall(matrix1,equalMatrix) == 1);
    REQUIRE( equall(result,matrixSum) == 1);
    REQUIRE( equall(result1,matrixDifference) == 1);
    REQUIRE( equall(result2,matrixProduct) == 1);


    fisier.close();
}
