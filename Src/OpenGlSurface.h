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

class OpenGlSurface : public QGLWidget
{
    Q_OBJECT
    
public:
    OpenGlSurface(int, int , int , int ,QGLWidget *parent = 0);
    ~OpenGlSurface();

    void drawRectangles (std::vector<std::pair<GLfloat,GLfloat> >, GLfloat,GLfloat,GLfloat,GLfloat );

public slots:

    void saveFrameBuffer();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int,int);
    void mousePressEvent(QMouseEvent *event);
    void draw();

private:
    std::vector<std::pair<GLfloat,GLfloat> > controlPointsList;
    std::vector<std::pair<GLfloat,GLfloat> > curvePointsList;

    int viewPortWidth;
    int viewPortHeight;

    DataSet <float,float> dataSet;
    DissimilarityMatrix distanceMatrix;
};

#endif // OpenGlSurface_H
