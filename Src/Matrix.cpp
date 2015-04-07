#include "Matrix.h"

Matrix::Matrix()
{
    minimumDistance = 10000.0f;
    minimumDistanceIndex = 0;
    isAdjacency = false;
}

void Matrix::normalizeMatrix()
{
    double maxDistance = -100000.0f;
    double minDistance =  100000.0f;

    // Find maximum distance
    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
            if( matrixPtr[i][j] > maxDistance )
                maxDistance = matrixPtr[i][j];
            if( matrixPtr[i][j] < minDistance )
                minDistance = matrixPtr[i][j];
        }
    }

    std::cout << "Initial Max: " << maxDistance << std::endl;
    std::cout << "Initial Min: " << minDistance << std::endl;

    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
                matrixPtr[i][j] = (matrixPtr[i][j] - minDistance ) / (maxDistance - minDistance);
        }
    }
}

void Matrix::randomRearrangeMatrix()
{
//    for( unsigned int i = 0 ; i < 3 ; ++i)
//    {
//        int randomColumn = (rand() %  MatrixSize);

//        for( unsigned int j = 0 ; j <  MatrixSize ; ++j)
//        {
//            double temp =  Matrix[i][j];
//             Matrix[i][j] =  Matrix[randomColumn][j];
//             Matrix[randomColumn][j] = temp;
//        }
//    }

}

void Matrix::printMatrix()
{
    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
            if( i != j && j < matrixSize-1 )
                printf("%.5f,", matrixPtr[i][j] );
            else if ( i != j )
                printf("%.5f", matrixPtr[i][j] );
            else if( i == j && j != matrixSize-1 )
                std::cout << "0.00000," ;
            else
                std::cout << "0.00000" ;
        }

        std::cout << std::endl ;
    }
}

void Matrix::fillMaxInfo()
{
    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
            if( i !=j && matrixPtr[i][j] < minimumDistance )
            {
                minimumDistance = matrixPtr[i][j];
                minimumDistanceIndex = j ;
            }
        }
    }
}

void Matrix::applyVAT()
{
    std::vector<unsigned int> vertices ;

    for(unsigned int i = 0 ; i < matrixSize ; ++ i )
    {
        vertices.push_back(i);
    }

    std::cout << "First chosen vertex index " << minimumDistanceIndex + 1 << std::endl ;

    verticesChosen.push_back(minimumDistanceIndex);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), minimumDistanceIndex), vertices.end());

    while( 0 != vertices.size() )
    {
        double minimumDistance = 10000;
        unsigned int minimumDistanceVertex  = 0;

        // Apply VAT
        for( unsigned int i = 0 ; i < verticesChosen.size() ; ++i)
        {
            for( unsigned int j = 0 ; j < vertices.size() ; ++j)
            {
                if( verticesChosen[i] != vertices[j] && matrixPtr[verticesChosen[i]][vertices[j]] <= minimumDistance )
                {
                    minimumDistance = matrixPtr[verticesChosen[i]][vertices[j]];
                    minimumDistanceVertex = vertices[j] ;
                }
            }
        }

        verticesChosen.push_back(minimumDistanceVertex );
        vertices.erase(std::remove(vertices.begin(), vertices.end(), minimumDistanceVertex ), vertices.end());
    }//

    double **  Matrix2 = (double **) malloc(sizeof(double*)*matrixSize);

    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
         Matrix2[i] = (double *) malloc(sizeof(double) * matrixSize );
    }

    // Exchange Columns
    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
             Matrix2[i][j] = matrixPtr[verticesChosen[i]][verticesChosen[j]];
        }
    }

    // Exchange Columns back to original matrix
    for( unsigned int i = 0 ; i < matrixSize ; ++i)
    {
        for( unsigned int j = 0 ; j < matrixSize ; ++j)
        {
            matrixPtr[i][j] =  Matrix2[i][j];
        }
    }

    printSeriationOrder();
}

// Allocate memory based on the data feature vectors read from file and
// calcualte the dissimilarities
void Matrix::allocateAndFill(DataSet<double,double> dataSet)
{
    matrixSize = dataSet.getDataPointsList().size() ;
    DATA_SET_SIZE = matrixSize;
    matrixPtr = (double **) malloc(sizeof(double*)*dataSet.getDataPointsList().size());


    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        matrixPtr[i] = (double *) malloc(sizeof(double) * getSize() );
    }

    // Fill in the   matrix
    for( unsigned int i = 0 ; i < getSize() ; ++i)
    {
        for( unsigned int j = 0 ; j < getSize() ; ++j)
        {
            if( i == j )
                matrixPtr[i][j] = 0.0;
            else
            {
                matrixPtr[i][j] = dataSet.getDistanceBetweenPoints(dataSet.getDataPointsList()[i], dataSet.getDataPointsList()[j],DISTANCE_FUNCTION_TYPE);
            }
        }
    }
}


// Directly read the   matrix from file
void Matrix::allocateAndFill()
{
    matrixSize = DATA_SET_SIZE ;
    matrixPtr = (double **) malloc(sizeof(double*)*DATA_SET_SIZE);

    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        matrixPtr[i] = (double *) malloc(sizeof(double) * DATA_SET_SIZE );
    }

    // Fill in the   matrix
    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        for( unsigned int j = 0 ; j < DATA_SET_SIZE ; ++j)
        {
             scanf("%lf",&matrixPtr[i][j]);

             // Convert the adjacency information into the dissimilarity space
             if( isAdjacency )
             {
                if( i == j )
                    matrixPtr[i][j] = 0.0 ;
                else if ( matrixPtr[i][j] > 0.0 )
                        matrixPtr[i][j] = 0.0 ;
                else
                        matrixPtr[i][j] = 1.0 ;
             }
        }
    }
}

void Matrix::allocate()
{
    matrixSize = DATA_SET_SIZE ;
    matrixPtr = (double **) malloc(sizeof(double*)*DATA_SET_SIZE);

    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        matrixPtr[i] = (double *) malloc(sizeof(double) * DATA_SET_SIZE );
    }
}

void Matrix::printSeriationOrder()
{
    std::cout << "Seriated order of clustering is : " ;

    for( unsigned int i = 0 ; i < verticesChosen.size() ; ++ i )
        std::cout << verticesChosen[i]+1 << " " ;

    std::cout << "\n" << std::endl ;
}

