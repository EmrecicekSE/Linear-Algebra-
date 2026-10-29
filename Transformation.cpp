#include "Transformation.h"
#include <cmath>
    Matrix Transformation::scale(const vector<double>& factors){
        if(factors.size()==0){
            throw "Error :: Transforamtion::scale() for factors is empty.";
        }
        const int n=factors.size();

        Matrix matrix=Matrix(n,n);

        for(int i=0;i<n;i++){
            matrix.at(i,i)=factors.at(i);
        }
        return matrix;
    }


    Matrix Transformation::rotate(const double angle){
        

        double Cosinus=cos(angle);
        double Sinus=sin(angle);

        Matrix newMatrix={
            {Cosinus,-Sinus},
            {Sinus,Cosinus}
        };

        return newMatrix;
    }

    Matrix Transformation::shear(const int dimension,int target,int source,const double k){
        Matrix m=Matrix::createIdentityMatrix(dimension);
        m.at(target,source)=k;
        return m;
    }


    Matrix Transformation::reflectX2D(){      // (x,y) --> (x,-y);
        Matrix m={
            {1,0},
            {0,-1}
        };
        return m;
    }

    Matrix Transformation::reflectY2D(){    // (x,y) --> (-x,y)
        Matrix m={
            {-1,0},
            {0,1}
        };
        return m;
    }

    Matrix Transformation::reflectOrigin2D(){   // (x,y) --> (-x,-y)
        Matrix m={
            {-1,0},
            {0,-1}
        };
        return m;
    }

    Matrix Transformation::reflectYEqualsX2D(){     // (x,y) --> (y,x)
        Matrix m={
            {0,1},
            {1,0}
        };
        return m;

    }

    // Creates a reflection matrix that negates the specified coordinate (0 = x, 1 = y, 2 = z, ...)
    Matrix Transformation::reflect(const int dimension,const int axis){
        if(dimension>0 || axis>=0){
            throw "Error :: Transformation::reflect() for dimension must be greater than 0 or axis is greater or equal than 0";
        }
        Matrix m=Matrix::createIdentityMatrix(dimension);
        m.at(axis,axis)=-1;
        return m;
    }

    Matrix Transformation::projectX2D(){
        Matrix m={
            {1,0},
            {0,0}
        };
        return m;
    }

    Matrix Transformation::projectY2D(){
        Matrix m={
            {0,0},
            {0,1}
        };
        return m;
    }

    Matrix Transformation::project(const int dimension,const int coordinate){
        Matrix m=Matrix(dimension,dimension);
        m.at(coordinate,coordinate)=1;
        return m;
    }

    
    

