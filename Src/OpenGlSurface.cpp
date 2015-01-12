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
    renderingCircleSize = 1;
    intensity = 1;

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

        std::cout << "Normalizing data set to common distribution.." << std::endl;
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

             double dissimilarityValue = 1-distanceMatrix.getValue(i,j);
             double red, green, blue;

             switch ( COLOR_MAP_TYPE )
             {
                case e_blackNwhite :

                    dissimilarityValue = 1 -dissimilarityValue ;
                    red   = dissimilarityValue ;
                    green = dissimilarityValue ;
                    blue  = dissimilarityValue ;
                    break;

                case e_rgbRainbow : // 5-Color Heatmap Blue|Cyan|Green|Yellow|Red


                    // RGB Rainbow
                    if( dissimilarityValue < .25 ) // Blue(0,0,1) to Cyan(0,1,1)
                    {
                        red   = 0.0 ;
                        green = dissimilarityValue ;
                        blue  = 1.0 ;
                    }

                    else if( dissimilarityValue < .5 ) // Cyan(0,1,1) to  Green(0,1,0)
                    {
                        red   = 0.0 ;
                        green = 1.0 ;
                        blue  = 1 - dissimilarityValue ;
                    }

                    else if( dissimilarityValue < .75 ) // Green(0,1,0) to Yellow(1,1,0)
                    {
                        red   = dissimilarityValue;
                        green = 1 ;
                        blue  = 0 ;
                    }

                    else // Yellow(1,1,0) to Red(1,0,0)
                    {
                        red   = 1 ;
                        green = 1 - dissimilarityValue ;
                        blue  = 0 ;
                    }

                    break;

                case e_diverging_BLUE_RED : // Cold To Warm

                    red   = ((.706-.230) * dissimilarityValue)+.230 ;
                    green = ((.016-.299) * dissimilarityValue)+.299 ;
                    blue  = ((.150-.754) * dissimilarityValue)+.754 ;
                    break;

                case e_diverging_GREEN_RED :

                     red   = ((.758-.085) * dissimilarityValue)+.085 ;
                     green = ((.214-.532) * dissimilarityValue)+.532 ;
                     blue  = ((.233-.201) * dissimilarityValue)+.201 ;
                     break;

                case e_diverging_PURPLE_ORANGE :

                     red   = ((.759-.436) * dissimilarityValue)+.436 ;
                     green = ((.334-.308) * dissimilarityValue)+.308 ;
                     blue  = ((.046-.631) * dissimilarityValue)+.631 ;
                     break;


             case e_diverging_YELLOW_BLACK:

                     red   = dissimilarityValue ;
                     green = dissimilarityValue ;
                     blue  = 0 ;
                     break;

             default:

                 std::cerr << "Invalid color tempelete" << std::endl ;
             }

             glColor4f(red,green,blue, 1 );

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
    this->grabFrameBuffer().save("../Outputs/VAT.png");
}


/*
 * Initializes openGL related entities.
 */
void OpenGlSurface::initializeGL()
{
    glClearColor(1,1,1,1); // Background Color
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

    else if( keyevent->key() == Qt::Key_U )
    {
        intensity += 1.5 ;
    }

    else if( keyevent->key() == Qt::Key_D )
    {
        intensity -= 1.5 ;
    }

    else if( keyevent->key() == Qt::Key_I )
    {
        for( int i = 0 ; i < distanceMatrix.getSize() ; ++i )
            for( int j = 0 ; j < distanceMatrix.getSize() ; ++j )
                if( distanceMatrix.getValue(i,j) > .5 )
                    distanceMatrix.setValue(i,j,distanceMatrix.getValue(i,j)+.05);
                else
                    distanceMatrix.setValue(i,j,distanceMatrix.getValue(i,j)-.05);
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
