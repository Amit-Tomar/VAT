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
    GlobalSettingsData.cpp \
    Matrix.cpp

HEADERS  += OpenGlSurface.h \
    OpenGlSurface.h \
    DataSet.hpp \
    DataPoint.hpp \
    Statistics.h \
    GlobalSettingsData.h \
    Matrix.h

FORMS +=

LIBS += -lGLU
