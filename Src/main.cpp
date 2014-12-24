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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpenGlSurface *surface = new OpenGlSurface(0,0,600,600);

    surface->show();

    QObject::connect(&a,SIGNAL(aboutToQuit()),surface,SLOT(saveFrameBuffer()));

    return a.exec();
}
