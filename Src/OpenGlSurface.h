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

    void setDrawingAlgoBernstein(bool);
    void drawRectangles (std::vector<std::pair<GLfloat,GLfloat> >, GLfloat,GLfloat,GLfloat,GLfloat );
    void drawPolygon    (std::vector<std::pair<GLfloat,GLfloat> >, GLfloat,GLfloat,GLfloat,GLfloat );
    void setScale(int);
    void setRotation(int,int);
    void setTranslateX(int);
    void setTranslateY(int);

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
    int angle;

    GLfloat scale;
    GLfloat translateX;
    GLfloat translateY;

    bool rotationAxisX;
    bool rotationAxisY;
    bool rotationAxisZ;
    bool useBernsteinAlgo;

    DataSet <float,float> irisDataSet;
    DissimilarityMatrix distanceMatrix;
};

#endif // OpenGlSurface_H
