#include "glwidget.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "function.h"
#include "point.h"
#include "index.h"
#include "grammer.hpp"

std::string WrlFileName;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(6);

}

void GLWidget::setWRL(std::string filename)
{

    WrlFileName = filename;
   // std::cout<<"wrl: "<<WrlFileName<<'\n';

}


void GLWidget::initializeGL()
{
   // std::cout<<"initializeGL"<<'\n';
    function *GetData = new function;

    std::vector<Point> GetPoint;
    std::vector<Index> GetIndex;

   // std::cout<<"wrl file: "<<WrlFileName<<'\n';


    GetData->getPoint(WrlFileName, GetPoint);
    GetData->getIndex(WrlFileName, GetIndex);
    GetData->initialRotateMesh(GetPoint);
    GetData->minMax(GetPoint);
    GetData->divide_mesh(GetPoint,GetIndex);
    GetData->rotateMesh();
    //GetData.perspectiveTransformation();
    GetData->parallelTransformation();
    GetData->minMaxTransformated();
    GetData->normalise();

    int j = 0;
    for(unsigned int i=0; i<initialMiddleFaceP.size(); i++)
    {
        Ver[j] = initialMiddleFaceP[i].x; j++;
        //std::cout<<Ver[j]<<" here ";
        Ver[j] = initialMiddleFaceP[i].y; j++;
        //std::cout<<Ver[j]<<"  ";
        Ver[j] = initialMiddleFaceP[i].z; j++;
        //std::cout<<Ver[j]<<'\n';
        indices[i] = i;
    }

    j = 0;
    for(unsigned int i=0; i<MiddleFaceP.size(); i++)
    {
        V[j] = MiddleFaceP[i].x; j++;
        V[j] = MiddleFaceP[i].y; j++;
    }

    numTriangle = MiddleFaceP.size();

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);

    initGL();

}


void GLWidget::paintGL()
{

   // std::cout<<"paint"<<'\n';
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    draw();

}


void GLWidget::resizeGL(int w,int h)
{

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)w/h,0.1,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}


void GLWidget::initGL()
{

    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

                                                    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        // disable depth test, lighting, culling for wireframe drawing
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

        // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    //initLights();
}


void GLWidget::draw()
{
    // enable and specify pointers to vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Ver);

    glPushMatrix();

    //std::cout<<"okay it is here"<<'\n';
    glDrawElements(GL_TRIANGLES, numTriangle, GL_UNSIGNED_SHORT, indices);

    glPopMatrix();

    //glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}


//button trigger function

void GLWidget::plusXdistance(int dist){

    glTranslatef(dist,0.0,0.0);
}


void GLWidget::minusXdistance(int dist)
{
     glTranslatef(-dist,0.0,0.0);
}


void GLWidget::plusYdistance(int dist){

    glTranslatef(0.0,dist,0.0);
}


void GLWidget::minusYdistance(int dist)
{
     glTranslatef(0.0,-dist,0.0);
}


void GLWidget::plusZdistance(int dist){

   // makeCurrent();
    glTranslatef(0.0,0.0,-dist);
}


void GLWidget::minusZdistance(int dist)
{
     //makeCurrent();
     glTranslatef(0.0,0.0,dist);
}


void GLWidget::plusXrotation(int angle)
{
    glRotatef(angle,1.0,0.0,0.0);
}


void GLWidget::minusXrotation(int angle)
{
    glRotatef(-angle,1.0,0.0,0.0);
}


void GLWidget::plusYrotation(int angle)
{
    glRotatef(angle,0.0,1.0,0.0);
}


void GLWidget::minusYrotation(int angle)
{
    glRotatef(-angle,0.0,1.0,0.0);
}


void GLWidget::plusZrotation(int angle)
{
    glRotatef(angle,0.0,0.0,1.0);
}


void GLWidget::minusZrotation(int angle)
{
    glRotatef(-angle,0.0,0.0,1.0);
}


















