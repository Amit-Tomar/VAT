#-------------------------------------------------
#
# Project created by QtCreator 2014-01-16T02:15:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VAT
TEMPLATE = app


SOURCES += main.cpp\
        OpenGlSurface.cpp \
    MainWindow.cpp \
    DissimilarityMatrix.cpp

HEADERS  += OpenGlSurface.h \
    MathHelper.h \
    OpenGlSurface.h \
    MainWindow.h \
    DataPoint.h \
    DataSet.h \
    DissimilarityMatrix.h

FORMS += \
    MainWindow.ui
