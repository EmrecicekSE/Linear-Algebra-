#ifndef MATRIX_H
#define MATRIX_H

#pragma once
#include <vector>
#include <initializer_list>


using namespace std;

class Vector;


class Matrix{
    private:
        int rows;
        int cols;
        vector<vector<double> > matrix;

        void fillMatrix(double initial_val);
        vector<double> getRowArray(const int i)const;
        vector<double> getColumnArray(int j)const;
        double calculate(vector<double>& v1, vector<double>& v2);
        bool isValidColumnForRREF(vector<double>& v)const;
        Matrix makeIdentityMatrix()const;

    public:
        Matrix(int rows, int cols, double initial_val = 0.0);
        Matrix(initializer_list<initializer_list<double> > values);

        int getRows()const;
        int getColumns()const;

        const double& at(int i, int j)const;
        double& at(int i, int j);

        void print()const;
        double trace()const;
        bool isSameSize(const Matrix& A)const;
        Matrix add(const Matrix& A);
        Matrix subtarct(const Matrix& A);
        Matrix skalerMultiply(const double k);
        Matrix matrixMultiplaction(const Matrix& A);
        Matrix transpose()const;
        static Matrix createZeroMatrix(const int row,const int column);


        bool isSquare()const;
        bool isIdentity()const;

        void swapRows(const int i, const int j);
        void scaleRow(const int i, const double k);
        void scaleMatrix(const double k);
        void addRow(const int targetRow, const int sourceRow, const double scalar);

        bool isRowZero(const int rowIndex)const;
        bool isColumnZero(const int columnIndex)const;
        bool isRef()const;
        bool isRRef()const;
        bool isLowerMatrix()const;
        bool isUpperMatrix()const;
        bool isSymmetricMatrix()const;
        bool hasUniqueSolutionForSquareMatrix()const;
        bool isInvertible()const;
        bool hasNonTrivialSolutionsForSquareMatrix()const;
        

        Matrix toUpperTriangular(int& swapCount)const;  
        Matrix toUpperTriangular()const;
        Matrix toLowerTriangular()const;
        Matrix toRowEchelon()const;
        Matrix toREF()const;
        Matrix toRREF()const;

        Matrix solveMatrix(const Matrix& B)const;
        double determinant()const;
        Matrix inverse()const;

        Matrix getMinorMatrix(int row, int col)const;
        double minor(int row, int col)const;
        double cofactor(int row, int col)const;
        Matrix cofactorMatrix()const;
        Matrix adj()const;

        static Matrix createIdentityMatrix(const int n);

        int rank()const;
        int nullity()const;
        vector<Vector> getColumnSpaceBasis()const;
        vector<Vector> getRowSpaceBasis()const;
        vector<Vector> getNullSpaceBasis() const;

};

#endif // MATRIX_H