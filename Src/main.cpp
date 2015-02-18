/**
 * @file    main.cpp
 * @author  Amit Tomar
 * @version 1.0
 *
 * Main File for instantiating the widget
 */

#include "OpenGlSurface.h"
#include <QApplication>
#include <OpenGlSurface.h>
#include "GlobalSettingsData.h"

int main(int argc, char *argv[])
{

    std::cout << "Usage: ./VAT [F|D] [Dimensions|DataSetSize] [DissimilarityType] < InputFile" << std::endl ;
    std::cout << "F: Feature vector file, D: Dissimilarity file" << std::endl;
    std::cout << "E: Euclidean, O: Cosine, J: Jaccard, M: Manhattan, C: Canberra, B: Mahalanobis, P: Pearson \n\n" << std::endl;

    if (argc < 3)
    {
            std::cerr << "Less arguments passed than expected. Exiting.." << std::endl;
            return 1;
    }

    if( 0 == strcmp( "F", argv[1] ) || 0 == strcmp( "f", argv[1] ) )
    {
        IS_FEATURE_VECTOR_FILE = true;
        DIMENSIONS_IN_DATA = atoi(argv[2]);

        if( 0 == strcmp( "E", argv[3] ) || 0 == strcmp( "e", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_euclidean;
        }
        else if( 0 == strcmp( "O", argv[3] ) || 0 == strcmp( "o", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_cosine;
        }

        else if( 0 == strcmp( "J", argv[3] ) || 0 == strcmp( "j", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_jaccard;
        }

        else if( 0 == strcmp( "M", argv[3] ) || 0 == strcmp( "m", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_manhattan;
        }

        else if( 0 == strcmp( "C", argv[3] ) || 0 == strcmp( "c", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_canberra;
        }

        else if( 0 == strcmp( "B", argv[3] ) || 0 == strcmp( "B", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_mahalanobis;
        }

        else if( 0 == strcmp( "P", argv[3] ) || 0 == strcmp( "p", argv[3] ) )
        {
            DISTANCE_FUNCTION_TYPE = e_pearson;
        }

        else
        {
            std::cerr << "Invalid distance function type" << std::endl ;
        }
    }
    else if ( 0 == strcmp("D" , argv[1] ) || 0 == strcmp( "d", argv[1] ))
    {
        IS_FEATURE_VECTOR_FILE = false;
        DATA_SET_SIZE = atoi(argv[2]);
    }
    else
    {
        std::cerr << "Invalid file input type" << std::endl ;
    }


    QApplication a(argc, argv);

    OpenGlSurface *surface = new OpenGlSurface(0,0,650,650);

    surface->show();

    return a.exec();
}
