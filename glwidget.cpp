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
#include "errordialog.h"
#include "dialog.h"
#include "window.h"
#include <QProcess>
#include <QApplication>

std::string WrlFileName;
QString imagename0;
int textureError=0;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(10);

}

int GLWidget::ImageLoad(const char *filename,Image0 *image)
{

    //std::cout<<"load texture"<<'\n';
    FILE *file;

       unsigned long size; // size of the image in bytes.

       unsigned long i; // standard counter.

       unsigned short int planes; // number of planes in image (must be 1)

       unsigned short int bpp; // number of bits per pixel (must be 24)

       char temp; // temporary color storage for bgr-rgb conversion.

       // make sure the file is there.

       if ((file = fopen(filename, "rb"))==NULL){

           printf("File Not Found : %s\n",filename);

           return 0;

       }

       // seek through the bmp header, up to the width/height:

       fseek(file, 18, SEEK_CUR);

           // read the width


       if ((i = fread(&image->sizeX, sizeof(int), 1, file)) != 1) {

           printf("Error reading width from %s.\n", filename);

           return 0;

       }

       //printf("Width of %s: %lu\n", filename, image->sizeX);

       // read the height

       if ((i = fread(&image->sizeY, sizeof(int), 1, file)) != 1) {

           printf("Error reading height from %s.\n", filename);

           return 0;

       }

      printf("Height of %s: %lu\n", filename, image->sizeY);

       // calculate the size (assuming 24 bits or 3 bytes per pixel).

       size = image->sizeX * image->sizeY * 3;

       // read the planes

       if ((fread(&planes, 2, 1, file)) != 1) {

           printf("Error reading planes from %s.\n", filename);

                                                                                                                                                                                                        return 0;

       }

       if (planes != 1) {

           printf("Planes from %s is not 1: %u\n", filename, planes);

           return 0;

       }

       // read the bitsperpixel

       if ((i = fread(&bpp, 2, 1, file)) != 1) {

           printf("Error reading bpp from %s.\n", filename);

           return 0;

       }

       if (bpp != 24) {

           printf("Bpp from %s is not 24: %u\n", filename, bpp);

           return 0;

       }

       // seek past the rest of the bitmap header.
       //QImage img = QImage(filename);


       fseek(file, 24, SEEK_CUR);

       // read the data.
       std::cout<<"size: "<<size<<'\n';
       image->data = (char *) malloc(size);

       if (image->data == NULL) {

           printf("Error allocating memory for color-corrected image data");

           return 0;

       }

       if ((i = fread(image->data, size, 1, file)) != 1) {

           printf("Error reading image data from %s.\n", filename);

           return 0;

       }

       for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)

           temp = image->data[i];

           image->data[i] = image->data[i+2];

           image->data[i+2] = temp;

       }

       // we're done.

       return 1;

   }

Image0* GLWidget::loadTexture(){

    Image0 *image1;

    // allocate space for texture

    image1 = (Image0 *) malloc(sizeof(Image0));

    if (image1 == NULL) {

        printf("Error allocating space for image");

        exit(0);

    }

    std::string file = imagename0.toUtf8().constData();
    const char *myfile = file.c_str();

    if (!ImageLoad(myfile,image1)) {

        ErrorDialog ed;
        ed.setModal(true);

        ed.setmsg("Please check your image file format. Internal structure is not bmp.");
        if(ed.exec()==QDialog::Accepted)
        {
            QProcess::startDetached(QApplication::applicationFilePath());
            exit(12);
        }
    }


    return image1;

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


    bool p = GetData->getPoint(WrlFileName, GetPoint);
    bool i = GetData->getIndex(WrlFileName, GetIndex);

    if(p==1 && i==1){

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
        Image0 *image1 = loadTexture();
        initGL();
    }
    else
    {
        ErrorDialog ed;
        ed.setModal(true);

        ed.setmsg("Parsing error. Could not parse the wrl file");
        if(ed.exec()==QDialog::Accepted)
        {
            QProcess::startDetached(QApplication::applicationFilePath());
            exit(12);
        }
    }

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


















