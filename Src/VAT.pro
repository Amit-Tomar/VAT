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
    DissimilarityMatrix.cpp \
    GlobalSettingsData.cpp

HEADERS  += OpenGlSurface.h \
    OpenGlSurface.h \
    DissimilarityMatrix.h \
    DataSet.hpp \
    DataPoint.hpp \
    Statistics.h \
    GlobalSettingsData.h

FORMS +=
