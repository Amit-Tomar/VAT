/**
 * @file    OpenGlSurface.h
 * @author  Amit Tomar
 * @version 1.0
 *
 * Class decleration for class OpenGlSurface
 */


#ifndef OpenGlSurface_H
#define OpenGlSurface_H

#include <QGLWidget>
#include <iostream>
#include <QMouseEvent>
#include <vector>
#include <cmath>
#include <QSlider>
#include <QHBoxLayout>
#include <DataSet.h>
#include <DissimilarityMatrix.h>

#define DIMENSIONS_IN_DATA 13

class OpenGlSurface : public QGLWidget
{
    Q_OBJECT
    
public:
    OpenGlSurface(int, int , int , int ,QGLWidget *parent = 0);
    ~OpenGlSurface();

    void drawRectangles (std::vector<std::pair<GLdouble,GLdouble> >, GLdouble,GLdouble,GLdouble,GLdouble );

public slots:

    void saveFrameBuffer();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int,int);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent*);
    void draw();

private:
    std::vector<std::pair<GLdouble,GLdouble> > controlPointsList;
    std::vector<std::pair<GLdouble,GLdouble> > curvePointsList;

    int viewPortWidth;
    int viewPortHeight;

    DataSet <double,double> dataSet;
    DissimilarityMatrix distanceMatrix;

    bool drawVATAsRectangles;
    int renderingCircleSize;
};

#endif // OpenGlSurface_H
