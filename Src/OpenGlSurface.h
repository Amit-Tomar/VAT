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
#include <GL/glu.h>
#include "DataSet.hpp"
#include "DissimilarityMatrix.h"
#include "GlobalSettingsData.h"

class OpenGlSurface : public QGLWidget
{
    Q_OBJECT
    
public:
    OpenGlSurface(int, int , int , int ,QGLWidget *parent = 0);
    ~OpenGlSurface();

public slots:

    void saveFrameBuffer();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int,int);
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent*);
    void draw();
    void generateMesh();

private:

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void calculateNormal(float *, float*);

    float sceneXRot;
    float sceneYRot;
    float sceneZRot;

    float sceneScale;

    QPoint lastPos;

    int viewPortWidth;
    int viewPortHeight;

    DataSet <double,double> dataSet;
    DissimilarityMatrix distanceMatrix;

    bool drawVATAsRectangles;
    int renderingCircleSize;
    double intensity;
};

#endif // OpenGlSurface_H
