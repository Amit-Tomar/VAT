/**
 * @file    OpenGlSurface.cpp
 * @author  Amit Tomar
 * @version 1.0
 *
 * Class definitions for class OpenGlSurface
 */

#include "OpenGlSurface.h"

/*
 * Constructor
 *
 * @param  x X coordinate of left-top corner of widget
 * @param  y Y coordinate of left-top corner of widget
 * @param  width Width of widget
 * @param  height Height of widget
 * @param  parent Pointer to parent widget
 */
OpenGlSurface::OpenGlSurface(int x , int y, int width, int height, QGLWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    distanceMatrix.setSize(0);
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    setGeometry(x,y,width,height);
    initializeGL();

    // Parse and fillin the data sets
    float f1,f2,f3,f4,f5,f6,f7;

    std::cout << "Parsing started.." << std::endl;


    /* For ecoli
    while( EOF != scanf("%f %f %f %f %f %f %f %*[^\n]",&f1,&f2,&f3,&f4,&f5,&f6,&f7) )
    {
        std::vector<float> features ;
        features.push_back(f1);
        features.push_back(f2);
        features.push_back(f3);
        features.push_back(f4);
        features.push_back(f5);
        features.push_back(f6);
        features.push_back(f7);

        DataPoint<float> data(features);

        irisDataSet.pushDataPoint(data);
        std::cout << "Parsing " << f1 << std::endl;
    }*/


    /* For iris */
    while( EOF != scanf("%f,%f,%f,%f,%*[^\n]",&f1,&f2,&f3,&f4) )
    {
        std::vector<float> features ;
        features.push_back(f1);
        features.push_back(f2);
        features.push_back(f3);
        features.push_back(f4);

        DataPoint<float> data(features);

        dataSet.pushDataPoint(data);
        //std::cout << "Parsing " << f1 << std::endl;
    } //*/

    std::cout << "Parsing finished.." << std::endl;

    distanceMatrix.allocateAndFill(dataSet);
    distanceMatrix.normalizeMatrix();
    distanceMatrix.fillMaxInfo();
    distanceMatrix.applyVAT();
}

OpenGlSurface::~OpenGlSurface()
{
}


void OpenGlSurface::drawRectangles(std::vector<std::pair<GLfloat, GLfloat> > pointsList , GLfloat red, GLfloat green, GLfloat blue, GLfloat thickness)
{
        for ( unsigned int  i = 0; i < distanceMatrix.getSize(); ++i)
        {
             for ( unsigned int  j = 0; j < distanceMatrix.getSize(); ++j)
             {
                 // Enable blending for alpha component of glcolor to work properly
                 glEnable(GL_BLEND);
                 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                 glColor4f(0, .5, 0, 1 - distanceMatrix.getValue(i,j) );
                 float squareWidth = 1 / (float)distanceMatrix.getSize() ;

                 glRectf(i*squareWidth, j*squareWidth, (i+1)*squareWidth, (j+1)*squareWidth);

                 glEnd();
             }
        }

        update();
}

void OpenGlSurface::saveFrameBuffer()
{
    this->grabFrameBuffer().save("../Outputs/output.png");
}


/*
 * Initializes openGL related entities.
 */
void OpenGlSurface::initializeGL()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_POINT_SMOOTH);
    glLoadIdentity();
    glOrtho(0,1,1,0,0,1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    update();
}

/*
 * Overriden from OpenGlWidget, gets called on repaint events
 */
void OpenGlSurface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1,1,0,0,1);
    draw();
    update();
}

/*
 * Overriden from OpenGlWidget, gets called on widget resize events.
 *
 * @param  width New width of the widget
 * @param  height New Height of the widget
 */
void OpenGlSurface::resizeGL(int width, int height)
{
    glViewport(0, 0, width , height );
    viewPortWidth = width ;
    viewPortHeight = height;
    update();
}

/*
 * Overriden from OpenGlWidget, gets called on mouse events.
 *
 * @param  event Pointer to the event object containing all mouse event related information.
 */
void OpenGlSurface::mousePressEvent(QMouseEvent *event)
{

    std::pair<GLfloat,GLfloat> pointClicked( (event->x()) / (float) viewPortWidth , (viewPortHeight-event->y()) / (float)viewPortHeight );
    controlPointsList.push_back(pointClicked);

    update();
}

/*
 * Write necessary drawing code in this function.
 */
void OpenGlSurface::draw()
{
    // Draw Control Points
    drawRectangles(controlPointsList,1,0,0,4);

    update();
}
