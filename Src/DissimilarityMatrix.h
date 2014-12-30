#ifndef DISSIMILARITYMATRIX_H
#define DISSIMILARITYMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

#include "DataSet.hpp"
#include "GlobalSettingsData.h"

class DissimilarityMatrix
{
public:
    DissimilarityMatrix();

    void normalizeMatrix();
    void randomRearrangeMatrix();
    void setSize(int size) { dissimilarityMatrixSize = size ; }
    int  getSize() { return dissimilarityMatrixSize; }
    double getValue(int i, int j) { return dissimilarityMatrix[i][j] ; }
    void printMatrix();
    void fillMaxInfo();
    void applyVAT();
    void allocateAndFill(DataSet<double,double>);
    void allocateAndFill();

private:

    double ** dissimilarityMatrix;
    unsigned int dissimilarityMatrixSize;
    double maximumDistance;
    int maximumDistanceIndex ;

};

#endif // DISSIMILARITYMATRIX_H
