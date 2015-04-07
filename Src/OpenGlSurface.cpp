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
    dissimilarityMatrix.setSize(0);
    adjacencyMatrix.setSize(0);
    adjacencyMatrix.setAdjacency();
    alpha = 1.0f;
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    setGeometry(x,y,width,height);
    initializeGL();
    draw2DVAT = true ;
    renderingCircleSize = 1;
    intensity = 1;
    sceneScale = 1;
    drawGraphLayoutLines = false;

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

        //std::cout << "Randomizing data set.." << std::endl;
        //dataSet.randomRearrangeDataset();

        std::cout << "Normalizing data set to common distribution.." << std::endl;
        dataSet.normalizeDataset();

        std::cout << "Allocating memory and filling dissimilarity matrix.." << std::endl;
        dissimilarityMatrix.allocateAndFill(dataSet);

        std::cout << "Allocating memory and filling adjacency matrix.." << std::endl;
        adjacencyMatrix.allocateAndFill();
        std::cout << "Parsing finished.." << std::endl;
    }

    else
    {
        std::cout << "Parsing started.." << std::endl;
        std::cout << "Allocating memory and filling dissimilarity matrix.." << std::endl;
        dissimilarityMatrix.allocateAndFill();
        std::cout << "Parsing finished.." << std::endl;

        std::cout << "Allocating memory and filling adjacency matrix.." << std::endl;
        adjacencyMatrix.allocateAndFill();
        std::cout << "Parsing finished.." << std::endl;
    }

    std::cout << "Normalizing dissimilarity matrix.." << std::endl;
    dissimilarityMatrix.normalizeMatrix();

    unifiedMatrix.allocate();

    // Fill in the combined matrix
    for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
    {
        for( unsigned int j = 0 ; j < DATA_SET_SIZE ; ++j)
        {
           unifiedMatrix.setValue(i,j, (dissimilarityMatrix.getValue(i,j) * alpha) + (adjacencyMatrix.getValue(i,j)*(1-alpha)) );
        }
    }

    std::cout << "Finding Maximum.." << std::endl;
    unifiedMatrix.fillMaxInfo();

    unifiedMatrix.printMatrix();

    std::cout << "Applying VAT.." << std::endl;
    unifiedMatrix.applyVAT();

    std::cout << "Rendering.." << std::endl;
    dissimilarityMatrix.printSeriationOrder();
}

OpenGlSurface::~OpenGlSurface()
{

}

void OpenGlSurface::saveFrameBuffer()
{
    this->grabFrameBuffer().save("../Outputs/VAT.png");

    QImage image(dissimilarityMatrix.getSize()*ONE_PIXEL_BLOCK, dissimilarityMatrix.getSize()*ONE_PIXEL_BLOCK, QImage::Format_RGB32);

    for( int i = 0 ; i < dissimilarityMatrix.getSize()*ONE_PIXEL_BLOCK ; i+=ONE_PIXEL_BLOCK )
    {
        for( int j = 0 ; j < dissimilarityMatrix.getSize()*ONE_PIXEL_BLOCK ; j+=ONE_PIXEL_BLOCK )
        {
            for( int k = i ; k < i+ONE_PIXEL_BLOCK ; k++ )
                for( int l = j ; l < j+ONE_PIXEL_BLOCK ; l++ )
                {
                    double dissimilarity = dissimilarityMatrix.getValue(i/ONE_PIXEL_BLOCK,j/ONE_PIXEL_BLOCK);
                    image.setPixel(k, l, qRgb(dissimilarity*255,dissimilarity*255,dissimilarity*255));
                }
        }
    }


    image.save("test.JPG");
}


/*
 * Initializes openGL related entities.
 */
void OpenGlSurface::initializeGL()
{
    glClearColor(1,1,1,1); // Background Color
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE); // Automatically normalizes the normal vectors

    if( !draw2DVAT )
    {
       GLfloat mat_specular[]   = { .21,.21,.21, 1 };
       GLfloat mat_shininess[]  = { 90.0 };
       GLfloat light_position[] = { 0, 0, 2.0, 0.0 };
       glClearColor (0.0, 0.0, 0.0, 0.0);

// Bright Light k
#if 1
       GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
#endif

       glShadeModel (GL_SMOOTH);
       glEnable(GL_COLOR_MATERIAL);
       //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
       glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
       glLightfv(GL_LIGHT0, GL_POSITION, light_position);

       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);
       glEnable(GL_DEPTH_TEST);
    }
}

/*
 * Overriden from OpenGlWidget, gets called on repaint events
 */
void OpenGlSurface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    

    draw2DVAT ? glOrtho(0,1,1,0,0,100) : gluPerspective(50,width/height,1,100);

    glMatrixMode(GL_MODELVIEW);
}

void OpenGlSurface::wheelEvent(QWheelEvent * event)
{
    //if( event->Whee )
}

/*
 * Overriden from OpenGlWidget, gets called on mouse events.
 *
 * @param  event Pointer to the event object containing all mouse event related information.
 */
void OpenGlSurface::mousePressEvent(QMouseEvent *mouseEvent)
{
    saveFrameBuffer();
    lastPos = mouseEvent->pos();
}


void OpenGlSurface::mouseMoveEvent(QMouseEvent *mouseEvent)
{
         int dx = mouseEvent->x() - lastPos.x();
         int dy = mouseEvent->y() - lastPos.y();

         if (mouseEvent->buttons() & Qt::LeftButton) {

             setXRotation(sceneXRot + 8 * dy);
             setYRotation(sceneYRot + 8 * dx);

         } else if (mouseEvent->buttons() & Qt::RightButton) {

             setXRotation( sceneXRot + 8 * dy );
             setZRotation( sceneZRot + 8 * dx );
         }
         lastPos = mouseEvent->pos();
}

void OpenGlSurface::keyPressEvent(QKeyEvent * keyevent)
{
    // Toggles view b/w 2D and 3D
    // Update light and the projections for 2D-3D views
    if( keyevent->key() == Qt::Key_T )
    {
        draw2DVAT = !draw2DVAT;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        draw2DVAT ? glOrtho(0,1,1,0,0,100) : gluPerspective(50,width() /height(),1,100);

        glMatrixMode(GL_MODELVIEW);
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
        for( int i = 0 ; i < dissimilarityMatrix.getSize() ; ++i )
            for( int j = 0 ; j < dissimilarityMatrix.getSize() ; ++j )
                if( dissimilarityMatrix.getValue(i,j) > .5 )
                    dissimilarityMatrix.setValue(i,j,dissimilarityMatrix.getValue(i,j)+.05);
                else
                    dissimilarityMatrix.setValue(i,j,dissimilarityMatrix.getValue(i,j)-.05);
    }

    else if( keyevent->key() == Qt::Key_L )
    {
        drawGraphLayoutLines = !drawGraphLayoutLines;
    }

    else if( keyevent->key() == Qt::Key_S )
    {
        alpha += .1;

        alpha > 1 ? alpha = 1 : 0;

        // Fill in the combined matrix
        for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
        {
            for( unsigned int j = 0 ; j < DATA_SET_SIZE ; ++j)
            {
               unifiedMatrix.setValue(i,j, (dissimilarityMatrix.getValue(i,j) * alpha) + (adjacencyMatrix.getValue(i,j)*(1-alpha)) );
            }
        }

        std::cout << "Finding Maximum.." << std::endl;
        unifiedMatrix.fillMaxInfo();

        std::cout << "Applying VAT.." << std::endl;
        unifiedMatrix.applyVAT();
    }

    else if( keyevent->key() == Qt::Key_A )
    {
        alpha -= .1;

        alpha < 0 ? alpha = 0 : 0;

        // Fill in the combined matrix
        for( unsigned int i = 0 ; i < DATA_SET_SIZE ; ++i)
        {
            for( unsigned int j = 0 ; j < DATA_SET_SIZE ; ++j)
            {
               unifiedMatrix.setValue(i,j, (dissimilarityMatrix.getValue(i,j) * alpha) + (adjacencyMatrix.getValue(i,j)*(1-alpha)) );
            }
        }

        unifiedMatrix.printSeriationOrder();

        std::cout << "Finding Maximum.." << std::endl;
        unifiedMatrix.fillMaxInfo();

        std::cout << "Applying VAT.." << std::endl;
        unifiedMatrix.applyVAT();
    }

    std::cout << "Current Alpha : " << alpha << std::endl ;
}

/*
 * Write necessary drawing code in this function.
 */
void OpenGlSurface::draw()
{
    glLoadIdentity();

    if( !draw2DVAT )
    {
        // Re-position Camera
        gluLookAt(0,1.5,1.5,0,0,0,0,1,0);

        glScalef(sceneScale,sceneScale,sceneScale);

        glRotatef(sceneXRot / 16.0, 1.0, 0.0, 0.0);
        glRotatef(sceneYRot / 16.0, 0.0, 1.0, 0.0);
        glRotatef(sceneZRot / 16.0, 0.0, 0.0, 1.0);

        glRotatef(90, 0, 0 ,1);
        glTranslatef(-.5,-.5,0);
    }

    for ( unsigned int  i = 0; i < dissimilarityMatrix.getSize(); ++i)
    {
         for ( unsigned int  j = 0; j < dissimilarityMatrix.getSize(); ++j)
         {
             // Enable blending for alpha component of glcolor to work properly
             glEnable(GL_BLEND);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

             //double dissimilarityValue = dissimilarityMatrix.getValue(i,j);
             double dissimilarityValue = unifiedMatrix.getValue(i,j);
             double red, green, blue;

             switch ( COLOR_MAP_TYPE )
             {
                case e_blackNwhite :

                    red   = dissimilarityValue ;
                    green = dissimilarityValue ;
                    blue  = dissimilarityValue ;
                    break;

                case e_rgbRainbow : // 5-Color Heatmap Blue|Cyan|Green|Yellow|Red

                    // To reverse the color encoding direction
                    dissimilarityValue = 1-dissimilarityMatrix.getValue(i,j);

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

                 // To reverse the color encoding direction
                 dissimilarityValue = 1-dissimilarityMatrix.getValue(i,j);

                    red   = ((.706-.230) * dissimilarityValue)+.230 ;
                    green = ((.016-.299) * dissimilarityValue)+.299 ;
                    blue  = ((.150-.754) * dissimilarityValue)+.754 ;
                    break;

                case e_diverging_GREEN_RED :

                 // To reverse the color encoding direction
                 dissimilarityValue = 1-dissimilarityMatrix.getValue(i,j);

                     red   = ((.758-.085) * dissimilarityValue)+.085 ;
                     green = ((.214-.532) * dissimilarityValue)+.532 ;
                     blue  = ((.233-.201) * dissimilarityValue)+.201 ;
                     break;

                case e_diverging_PURPLE_ORANGE :

                 // To reverse the color encoding direction
                 dissimilarityValue = 1-dissimilarityMatrix.getValue(i,j);

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

             double squareWidth = 1 / (double)dissimilarityMatrix.getSize() ;

             if( draw2DVAT )
             {
                 // Height Mapping
#if 0
                 glBegin(GL_POINTS);
                    glVertex3f(i*squareWidth, j*squareWidth,dissimilarityValue);
                    glVertex3f((i+1)*squareWidth, j*squareWidth,dissimilarityValue);
                    glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,dissimilarityValue);
                    glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,dissimilarityValue);
                    glVertex3f(i*squareWidth, (j+1)*squareWidth,dissimilarityValue);
                    glVertex3f(i*squareWidth, j*squareWidth,dissimilarityValue);
#endif

                 glRectf(i*squareWidth, j*squareWidth, (i+1)*squareWidth, (j+1)*squareWidth);

                 if (drawGraphLayoutLines)
                 {
                     glColor3f(0,0,0);
                     glBegin(GL_LINES);
                         glVertex2d(i*squareWidth, j*squareWidth);
                         glVertex2d(i*squareWidth, j*squareWidth+10);
                     glEnd();

                     glColor3f(0,0,0);
                     glBegin(GL_LINES);
                         glVertex2d(i*squareWidth, j*squareWidth);
                         glVertex2d(i*squareWidth+10, j*squareWidth);
                     glEnd();
                 }


#if 0
                 glEnd();
#endif
             }

             else
             {
                 if( i == dissimilarityMatrix.getSize()-1 || j == dissimilarityMatrix.getSize()-1  )
                     continue;

                 glEnable(GL_POINT_SMOOTH);
                 glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
                 glPointSize(renderingCircleSize);

                 float vector1[3], vector2[3];
                 vector1[0] = i*squareWidth - (i+1)*squareWidth;
                 vector1[1] = 0.0f;
                 vector1[2] = dissimilarityMatrix.getValue(i,j) - dissimilarityMatrix.getValue(i+1,j);

                 vector2[0] = 0.0f;
                 vector2[1] = j*squareWidth - (j+1)*squareWidth;
                 vector2[2] = dissimilarityMatrix.getValue(i,j) - dissimilarityMatrix.getValue(i,j+1);

                 calculateNormal(vector1,vector2);

                 glBegin(GL_TRIANGLES);
                    glVertex3f(i*squareWidth, j*squareWidth,1-dissimilarityMatrix.getValue(i,j));
                    glVertex3f(i*squareWidth, (j+1)*squareWidth,1-dissimilarityMatrix.getValue(i,j+1));
                    glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,1-dissimilarityMatrix.getValue(i+1,j+1));

                    // Generating Mesh Data

                    //std::cout << i*squareWidth << " " << j*squareWidth << " " << distanceMatrix.getValue(i,j) << std::endl ;
                    //std::cout << i*squareWidth << " " << (j+1)*squareWidth << " " << distanceMatrix.getValue(i,j+1) << std::endl ;
                    //std::cout << (i+1)*squareWidth << " " << (j+1)*squareWidth << " " << distanceMatrix.getValue(i+1,j+1) << std::endl ;

                    glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,1-dissimilarityMatrix.getValue(i+1,j+1));
                    glVertex3f((i+1)*squareWidth, j*squareWidth,1-dissimilarityMatrix.getValue(i+1,j));
                    glVertex3f(i*squareWidth, j*squareWidth,1-dissimilarityMatrix.getValue(i,j));
                 glEnd();
             }
         }
    }

    update();
}

void OpenGlSurface::generateMesh()
{
//    for ( unsigned int  i = 0; i < distanceMatrix.getSize(); ++i)
//    {
//         for ( unsigned int  j = 0; j < distanceMatrix.getSize(); ++j)
//         {
//             double squareWidth = 1 / (double)distanceMatrix.getSize() ;

//             if( i == distanceMatrix.getSize()-1 || j == distanceMatrix.getSize()-1  )
//                 continue;

//             glBegin(GL_TRIANGLES);
//                glVertex3f(i*squareWidth, j*squareWidth,1-distanceMatrix.getValue(i,j));
//                glVertex3f(i*squareWidth, (j+1)*squareWidth,1-distanceMatrix.getValue(i,j+1));
//                glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,1-distanceMatrix.getValue(i+1,j+1));

//                // Generating Mesh Data

//                std::cout << i*squareWidth << " " << j*squareWidth << " " << distanceMatrix.getValue(i,j) << std::endl ;
//                std::cout << i*squareWidth << " " << (j+1)*squareWidth << " " << distanceMatrix.getValue(i,j+1) << std::endl ;
//                std::cout << (i+1)*squareWidth << " " << (j+1)*squareWidth << " " << distanceMatrix.getValue(i+1,j+1) << std::endl ;

//                glVertex3f((i+1)*squareWidth, (j+1)*squareWidth,1-distanceMatrix.getValue(i+1,j+1));
//                glVertex3f((i+1)*squareWidth, j*squareWidth,1-distanceMatrix.getValue(i+1,j));
//                glVertex3f(i*squareWidth, j*squareWidth,1-distanceMatrix.getValue(i,j));
//             glEnd();
//         }
//    }
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void OpenGlSurface::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != sceneXRot) {
        sceneXRot = angle;
        updateGL();
    }
}

void OpenGlSurface::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != sceneYRot) {
        sceneYRot = angle;
        updateGL();
    }
}

void OpenGlSurface::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != sceneZRot) {
        sceneZRot = angle;
        updateGL();
    }
}

void OpenGlSurface::calculateNormal(float * vector1, float * vector2)
{
    float vCross[3], normalizationValue;

    // Cross product
    vCross[0] = vector1[1] * vector2[2] - vector2[1] * vector1[2];
    vCross[1] = vector2[0] * vector1[2] - vector1[0] * vector2[2];
    vCross[2] = vector1[0] * vector2[1] - vector2[0] * vector1[1];

    // Value to do normalization with
    normalizationValue = sqrt( vCross[0]*vCross[0] + vCross[1]*vCross[1] + vCross[2]*vCross[2] );

     float normal[3];
     normal[0] = vCross[0]/normalizationValue;
     normal[1] = vCross[1]/normalizationValue;
     normal[2] = vCross[2]/normalizationValue;

     glNormal3f(normal[0],normal[1],normal[2]);
}
