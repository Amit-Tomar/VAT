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
    drawVATAsRectangles = true ;
    renderingCircleSize = 5;

    bool flag = true;
    std::vector<double> readFeatureList;

    if( IS_FEATURE_VECTOR_FILE )
    {

        std::cout << "Parsing started.." << std::endl;

        while(flag)
        {
            double tempFeature;
            readFeatureList.clear();

            for( int i = 0 ; i < DIMENSIONS_IN_DATA ; ++i )
            {
                if( EOF != scanf("%lf",&tempFeature))
                    readFeatureList.push_back(tempFeature);
                else
                {
                    flag = false;
                    break;
                }
            }

            if( flag )
            {
                DataPoint<double> data(readFeatureList);
                dataSet.pushDataPoint(data);
            }
        }

        std::cout << "Parsing finished.." << std::endl;

        std::cout << DIMENSIONS_IN_DATA << " dimensional data with " << dataSet.getDataPointsList().size() << " vectors." << std::endl ;

        std::cout << "Randomizing data set.." << std::endl;
        dataSet.randomRearrangeDataset();

        std::cout << "Normalizing data set to commmon distribution.." << std::endl;
        dataSet.normalizeDataset();

        std::cout << "Allocating memory and filling dissimilarity matrix.." << std::endl;
        distanceMatrix.allocateAndFill(dataSet);
    }

    else
    {
        std::cout << "Parsing started.." << std::endl;
        std::cout << "Allocating memory and filling dissimilarity matrix.." << std::endl;
        distanceMatrix.allocateAndFill();
        std::cout << "Parsing finished.." << std::endl;
    }

    std::cout << "Normalizing dissimilarity matrix.." << std::endl;
    distanceMatrix.normalizeMatrix();

    std::cout << "Finding Maximum.." << std::endl;
    distanceMatrix.fillMaxInfo();

    std::cout << "Applying VAT.." << std::endl;
    distanceMatrix.applyVAT();

    std::cout << "Rendering.." << std::endl;
}

OpenGlSurface::~OpenGlSurface()
{
}


void OpenGlSurface::drawRectangles(std::vector<std::pair<GLdouble, GLdouble> > pointsList , GLdouble red, GLdouble green, GLdouble blue, GLdouble thickness)
{
        for ( unsigned int  i = 0; i < distanceMatrix.getSize(); ++i)
        {
             for ( unsigned int  j = 0; j < distanceMatrix.getSize(); ++j)
             {
                 // Enable blending for alpha component of glcolor to work properly
                 glEnable(GL_BLEND);
                 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                 glColor4f(0, 0, 0, 1 - distanceMatrix.getValue(i,j) );

                 double squareWidth = 1 / (double)distanceMatrix.getSize() ;

                 if( drawVATAsRectangles )
                    glRectf(i*squareWidth, j*squareWidth, (i+1)*squareWidth, (j+1)*squareWidth);
                 else
                 {
                     glEnable(GL_POINT_SMOOTH);
                     glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
                     glPointSize(renderingCircleSize);
                     glBegin(GL_POINTS);
                        glVertex3f(i*squareWidth, j*squareWidth,0);
                     glEnd();
                 }
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
    saveFrameBuffer();

    std::pair<GLdouble,GLdouble> pointClicked( (event->x()) / (double) viewPortWidth , (viewPortHeight-event->y()) / (double)viewPortHeight );
    controlPointsList.push_back(pointClicked);

    update();
}

void OpenGlSurface::keyPressEvent(QKeyEvent * keyevent)
{
    if( keyevent->key() == Qt::Key_T )
    {
        drawVATAsRectangles = !drawVATAsRectangles;
    }

    else if( keyevent->key() == Qt::Key_Up )
    {
        renderingCircleSize ++ ;
    }

    else if( keyevent->key() == Qt::Key_Down )
    {
        renderingCircleSize -- ;
    }
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
