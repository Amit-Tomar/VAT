#ifndef DISSIMILARITYMATRIX_H
#define DISSIMILARITYMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <DataSet.h>

class DissimilarityMatrix
{
public:
    DissimilarityMatrix();

    void normalizeMatrix();
    void setSize(int size) { dissimilarityMatrixSize = size ; }
    int  getSize() { return dissimilarityMatrixSize; }
    float getValue(int i, int j) { return dissimilarityMatrix[i][j] ; }
    void printMatrix();
    void fillMaxInfo();
    void applyVAT();
    void allocateAndFill(DataSet<float,float>);

private:

    float ** dissimilarityMatrix;
    unsigned int dissimilarityMatrixSize;
    float maximumDistance;
    int maximumDistanceIndex ;

};

#endif // DISSIMILARITYMATRIX_H
