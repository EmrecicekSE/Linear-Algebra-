#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"

struct Transformation{

    //Scaling
    static Matrix scale(const vector<double>& factors);

    //Rotation
    static Matrix rotate(const double angle);

    //Shear

    static Matrix shear(int dimension,int target,int source,const double k);
    

    // Reflection
  static  Matrix reflectX2D();
  static  Matrix reflectY2D();
   static  Matrix reflectOrigin2D(); 
   static Matrix reflectYEqualsX2D();

  static Matrix reflect(const int dimension,const int axix);

    //Projection
   static Matrix projectX2D();
   static Matrix projectY2D();
    static Matrix project(const int dimension,const int coordinate);
};



#endif