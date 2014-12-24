#include "DissimilarityMatrix.h"

DissimilarityMatrix::DissimilarityMatrix()
{
    maximumDistance = 0.0f;
    maximumDistanceIndex = 0;
}

void DissimilarityMatrix::normalizeMatrix()
{
    float maxDistance = 0.0f;

    // Find maximum distance
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            if( dissimilarityMatrix[i][j] > maxDistance )
                maxDistance = dissimilarityMatrix[i][j];
        }
    }

    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
                dissimilarityMatrix[i][j] = dissimilarityMatrix[i][j] / maxDistance;
        }
    }
}

void DissimilarityMatrix::printMatrix()
{
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            std::cout << dissimilarityMatrix[i][j] << "  ";
        }

        std::cout << std::endl ;
    }
}

void DissimilarityMatrix::fillMaxInfo()
{
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            if( i !=j && dissimilarityMatrix[i][j] > maximumDistance )
            {
                maximumDistance = dissimilarityMatrix[i][j];
                maximumDistanceIndex = i ;
            }
        }
    }
}

void DissimilarityMatrix::applyVAT()
{
    std::vector<unsigned int> vertices, verticesChosen ;

    for(unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++ i )
    {
        vertices.push_back(i);
    }

    verticesChosen.push_back(maximumDistanceIndex);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), maximumDistanceIndex), vertices.end());

    while( 0 != vertices.size() )
    {
        float minimumDistance = 1.0f;
        unsigned int minimumDistanceVertex  = 0;

        // Apply VAT
        for( unsigned int i = 0 ; i < verticesChosen.size() ; ++i)
        {
            for( unsigned int j = 0 ; j < vertices.size() ; ++j)
            {
                if( verticesChosen[i] != vertices[j] && dissimilarityMatrix[verticesChosen[i]][vertices[j]] < minimumDistance )
                {
                    minimumDistance = dissimilarityMatrix[verticesChosen[i]][vertices[j]];
                    minimumDistanceVertex = vertices[j] ;
                }
            }
        }

        verticesChosen.push_back(minimumDistanceVertex );
        vertices.erase(std::remove(vertices.begin(), vertices.end(), minimumDistanceVertex ), vertices.end());
    }//


    float ** dissimilarityMatrix2 = (float **) malloc(sizeof(float*)*dissimilarityMatrixSize);

    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        dissimilarityMatrix2[i] = (float *) malloc(sizeof(float) * dissimilarityMatrixSize );
    }

    // Exchange Columns
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            dissimilarityMatrix2[i][j] = dissimilarityMatrix[verticesChosen[i]][verticesChosen[j]];
        }
    }

    // Exchange Columns back to original matrix
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            dissimilarityMatrix[i][j] = dissimilarityMatrix2[i][j];
        }
    }
}

void DissimilarityMatrix::allocateAndFill(DataSet<float,float> dataSet)
{
    dissimilarityMatrixSize = dataSet.getDataPointsList().size() ;
    dissimilarityMatrix = (float **) malloc(sizeof(float*)*dataSet.getDataPointsList().size());

    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        dissimilarityMatrix[i] = (float *) malloc(sizeof(float) * getSize() );
    }

    // Fill in the dissimilarity matrix
    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        for( unsigned int j = 0 ; j < getSize() ; ++j)
        {
            if( i == j )
                dissimilarityMatrix[i][j] = 0.0;
            else
                dissimilarityMatrix[i][j] = dataSet.getDistanceBetweenPoints(dataSet.getDataPointsList()[i], dataSet.getDataPointsList()[j]);
        }
    }
}
