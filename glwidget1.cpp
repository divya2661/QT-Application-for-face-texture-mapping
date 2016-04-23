#include "glwidget1.h"
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

std::string WrlFileName1;
QString imagename;
bool lightOn=true;

GLWidget1::GLWidget1(QWidget *parent) : QGLWidget(parent)
{
    connect(&timer1,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer1.start(10);
}

int GLWidget1::ImageLoad(const char *filename,Image *image)
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


Image* GLWidget1::loadTexture(){

    Image *image1;

    // allocate space for texture

    image1 = (Image *) malloc(sizeof(Image));

    if (image1 == NULL) {

        printf("Error allocating space for image");

        exit(0);

    }

    std::string file = imagename.toUtf8().constData();
    const char *myfile = file.c_str();

    if (!ImageLoad(myfile,image1)) {

        exit(1);

    }

    return image1;

}


void GLWidget1::initializeGL()
{

    glClearColor(1,1,0,1);

   // std::cout<<"initializeGL1"<<'\n';
    function *GetData = new function;

    std::vector<Point> GetPoint;
    std::vector<Index> GetIndex;

    //std::cout<<"wrl file: "<<WrlFileName1<<'\n';


    GetData->getPoint(WrlFileName1, GetPoint);
    GetData->getIndex(WrlFileName1, GetIndex);
    GetData->initialRotateMesh(GetPoint);
    GetData->minMax(GetPoint);
    GetData->divide_mesh(GetPoint,GetIndex);
    GetData->rotateMesh();
   // GetData->perspectiveTransformation();
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
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT1);
//    // Properties of the objects' materials
//    glMaterialfv(GL_FRONT, GL_SPECULAR, specularity); // Reflectance
//    glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

//    glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient);
//    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
//    glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpecular);
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
    init();

}


void GLWidget1::paintGL()
{

    display();

}


void GLWidget1::resizeGL(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)w/h,0.1,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}


void GLWidget1::init()
{
    glShadeModel(GL_FLAT);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // 4-byte pixel alignment
    glClearColor (0.0, 0.0, 0.0, 0.0);
                                                // enable /disable features
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    Image *image1 = loadTexture();

    if(image1 == NULL){

        printf("Image was not returned from loadTexture\n");

        exit(0);

    }

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,image1->data);

}


void GLWidget1::display(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();


   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);

   glBegin(GL_TRIANGLES);
   for (unsigned int i = 0; i < MiddleFaceP.size(); i++) {
      glTexCoord2f(V[i*2],V[i*2+1]);
      glVertex3f(Ver[i*3],Ver[i*3+1],Ver[i*3+2]);
   }


   glEnd();

   glPopMatrix();
   //glutSwapBuffers();
}


void GLWidget1::lightOnOf(){

    if(lightOn==true)
    {
        qDebug("if..");
        lightOn=false;
    }
    else
    {
        qDebug("else..");
        lightOn=true;
    }
}

//button trigger function

void GLWidget1::plusXdistance1(int dist){

    glTranslatef(dist,0.0,0.0);
}


void GLWidget1::minusXdistance1(int dist)
{
     glTranslatef(-dist,0.0,0.0);
}


void GLWidget1::plusYdistance1(int dist){

    glTranslatef(0.0,dist,0.0);
}


void GLWidget1::minusYdistance1(int dist)
{
     glTranslatef(0.0,-dist,0.0);
}


void GLWidget1::plusZdistance1(int dist){

   // std::cout<<"plusZdist: "<<dist<<'\n';
    glTranslatef(0.0,0.0,-dist);
}


void GLWidget1::minusZdistance1(int dist)
{
     glTranslatef(0.0,0.0,dist);
}


void GLWidget1::plusXrotation1(int angle)
{
    glRotatef(angle,1.0,0.0,0.0);
}


void GLWidget1::minusXrotation1(int angle)
{
    glRotatef(-angle,1.0,0.0,0.0);
}


void GLWidget1::plusYrotation1(int angle)
{
    glRotatef(angle,0.0,1.0,0.0);
}


void GLWidget1::minusYrotation1(int angle)
{
    glRotatef(-angle,0.0,1.0,0.0);
}


void GLWidget1::plusZrotation1(int angle)
{
    glRotatef(angle,0.0,0.0,1.0);
}


void GLWidget1::minusZrotation1(int angle)
{
    glRotatef(-angle,0.0,0.0,1.0);
}

void GLWidget1::enableLight(){
    glEnable(GL_LIGHTING);
}

void GLWidget1::disableLight(){
    glDisable(GL_LIGHTING);
}

