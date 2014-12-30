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
    if (argc < 2)
    {
            std::cerr << "Less arguments passed than expected. Exiting.." << std::endl;
            return 1;
    }

    DIMENSIONS_IN_DATA = atoi(argv[1]);

    QApplication a(argc, argv);

    OpenGlSurface *surface = new OpenGlSurface(0,0,600,600);

    surface->show();    

    return a.exec();
}
