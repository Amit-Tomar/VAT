#ifndef Matrix_H
#define Matrix_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

#include "DataSet.hpp"
#include "GlobalSettingsData.h"

class Matrix
{
public:
    Matrix();

    void normalizeMatrix();
    void randomRearrangeMatrix();
    void setSize(int size) { matrixSize = size ; }
    unsigned int  getSize() { return matrixSize; }
    double getValue(int i, int j) { return matrixPtr[i][j] ; }
    void setValue(int i, int j,double value) { matrixPtr[i][j] = value ; }
    void printMatrix();
    void fillMaxInfo();
    void applyVAT();
    void allocateAndFill(DataSet<double,double>);
    void allocateAndFill();
    void allocate();
    void printSeriationOrder();
    void setAdjacency(){ isAdjacency = true; }

private:

    double ** matrixPtr;
    unsigned int matrixSize;
    double minimumDistance;
    int minimumDistanceIndex ;
    bool isAdjacency;
    std::vector<unsigned int> verticesChosen;
};

#endif // Matrix
