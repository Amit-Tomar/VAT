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

extern int DIMENSIONS_IN_DATA ;

int main(int argc, char *argv[])
{

    std::cout << "Usage: ./VAT [F|D] [Dimensions|DataSetSize] < InputFile" << std::endl ;
    std::cout << "F: Feature vector file, D: Dissimilarity file\n\n\n" << std::endl;

    if (argc < 3)
    {
            std::cerr << "Less arguments passed than expected. Exiting.." << std::endl;
            return 1;
    }

    if( 0 == strcmp( "F", argv[1] ) || 0 == strcmp( "f", argv[1] ) )
    {
        IS_FEATURE_VECTOR_FILE = true;
        DIMENSIONS_IN_DATA = atoi(argv[2]);
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

    OpenGlSurface *surface = new OpenGlSurface(0,0,600,600);

    surface->show();    

    return a.exec();
}
