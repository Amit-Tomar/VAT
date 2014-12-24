/**
 * @file    main.cpp
 * @author  Amit Tomar
 * @version 1.0
 *
 * Main File for instantiating the widget
 */

#include "OpenGlSurface.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    //mw.setWindowFlags(Qt::SplashScreen);

    mw.show();

    return a.exec();
}
