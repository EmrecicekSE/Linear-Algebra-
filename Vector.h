#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <initializer_list>
#pragma once
#include "Matrix.h"
#include <cmath>
#include "cmath"

using namespace std;

class Vector {
private:
    vector<double> data;

    static Matrix vectorsToMatrix(const vector<Vector>& vectors); 

public:

    // Constructors
    Vector(int size, double initialValue = 0.0);
    Vector(initializer_list<double> values);
    Vector(const vector<double>& values);
    
    // Basic methods
    int size() const;
    bool isEmpty()const;

    double& at(int index);
    double at(int index) const;

    void printVector() const;

    // Vector operations
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector operator*(double scalar) const;

    // Linear Algebra operations
    double dot(const Vector& other) const; 

    // Utility
    bool isZeroVector() const;

    static bool isIndependent(const vector<Vector>& vectors);

    static bool isLinearCombination(
        const Vector& target,
        const vector<Vector>& vectors
    );

    static bool doesSpan(const vector<Vector>& vectors);

    static bool isBasis(const vector<Vector>& vectors);

    static vector<Vector> getBasis(const vector<Vector>& vectors);

    static bool isOrthonormal(const vector<Vector>& vectors);   // hem orthogonal ve birim vektör olmadıdır örn: ||v1|| = 1

    static bool isOrthogonal(const vector<Vector>& vectors);    // iç çarpımlar 0 ( sıfır )

    double norm()const; // bu ise norm(uzunluk) almadır ||v|| = 5 

    static double angleVector(const Vector& v1,const Vector& v2);

};

#endif