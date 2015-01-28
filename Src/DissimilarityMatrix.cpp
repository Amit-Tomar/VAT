#include "DissimilarityMatrix.h"

DissimilarityMatrix::DissimilarityMatrix()
{
    maximumDistance = 0.0f;
    maximumDistanceIndex = 0;
}

void DissimilarityMatrix::normalizeMatrix()
{
    double maxDistance = -100000.0f;
    double minDistance =  100000.0f;

    // Find maximum distance
    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
            if( dissimilarityMatrix[i][j] > maxDistance )
                maxDistance = dissimilarityMatrix[i][j];
            if( dissimilarityMatrix[i][j] < minDistance )
                minDistance = dissimilarityMatrix[i][j];
        }
    }    

    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
        {
                dissimilarityMatrix[i][j] = (dissimilarityMatrix[i][j] - minDistance ) / (maxDistance - minDistance);
        }
    }      
}

void DissimilarityMatrix::randomRearrangeMatrix()
{
//    for( unsigned int i = 0 ; i < 3 ; ++i)
//    {
//        int randomColumn = (rand() % dissimilarityMatrixSize);

//        for( unsigned int j = 0 ; j < dissimilarityMatrixSize ; ++j)
//        {
//            double temp = dissimilarityMatrix[i][j];
//            dissimilarityMatrix[i][j] = dissimilarityMatrix[randomColumn][j];
//            dissimilarityMatrix[randomColumn][j] = temp;
//        }
//    }

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
    std::vector<unsigned int> vertices ;

    for(unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++ i )
    {
        vertices.push_back(i);
    }

    verticesChosen.push_back(maximumDistanceIndex);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), maximumDistanceIndex), vertices.end());

    while( 0 != vertices.size() )
    {
        double minimumDistance = 10.0f;
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


    double ** dissimilarityMatrix2 = (double **) malloc(sizeof(double*)*dissimilarityMatrixSize);

    for( unsigned int i = 0 ; i < dissimilarityMatrixSize ; ++i)
    {
        dissimilarityMatrix2[i] = (double *) malloc(sizeof(double) * dissimilarityMatrixSize );
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

// Allocate memory based on the data feature vectors read from file and
// calcualte the dissimilarities
void DissimilarityMatrix::allocateAndFill(DataSet<double,double> dataSet)
{
    dissimilarityMatrixSize = dataSet.getDataPointsList().size() ;
    dissimilarityMatrix = (double **) malloc(sizeof(double*)*dataSet.getDataPointsList().size());

    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        dissimilarityMatrix[i] = (double *) malloc(sizeof(double) * getSize() );
    }

    // Fill in the dissimilarity matrix
    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        for( unsigned int j = 0 ; j < getSize() ; ++j)
        {
            if( i == j )
                dissimilarityMatrix[i][j] = 0.0;
            else
            {
                dissimilarityMatrix[i][j] = dataSet.getDistanceBetweenPoints(dataSet.getDataPointsList()[i], dataSet.getDataPointsList()[j],DISTANCE_FUNCTION_TYPE);
            }
        }
    }
}


// Directly read the dissimilarity matrix from file
void DissimilarityMatrix::allocateAndFill()
{
    dissimilarityMatrixSize = DATA_SET_SIZE ;
    dissimilarityMatrix = (double **) malloc(sizeof(double*)*DATA_SET_SIZE);

    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        dissimilarityMatrix[i] = (double *) malloc(sizeof(double) * DATA_SET_SIZE );
    }

    // Fill in the dissimilarity matrix
    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        for( unsigned int j = 0 ; j < DATA_SET_SIZE ; ++j)
        {
             scanf("%lf",&dissimilarityMatrix[i][j]);
        }
    }
}

void DissimilarityMatrix::printSeriationOrder()
{
    std::cout << "Seriated order of clustering is : " ;

    for( int i = 0 ; i < verticesChosen.size() ; ++ i )
        std::cout << verticesChosen[i]+1 << " " ;

    std::cout << "\n" << std::endl ;
}
