#ifndef GLWIDGET1_H
#define GLWIDGET1_H
#include <QGLWidget>
#include <QTimer>
#include <string>

extern std::string WrlFileName1;
extern QString imagename;

struct Image {

   int sizeX;

   int sizeY;

   char *data;

};


class GLWidget1 : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget1(QWidget *parent = 0);


    GLfloat vertices2[100000];
    GLushort indices[100000];
    GLfloat V[100000];
    GLfloat Ver[100000];
    int numTriangle;
    int maxVertices;
    int maxIndices;
    float cameraDistance=0.0;
    GLuint texName;

    int ImageLoad(const char *filename, Image *image);
    Image * loadTexture();
    void setWRL(std::string filename);
    void initializeGL();
    void initialize(std::string filename);
    void paintGL();
    void resizeGL(int,int);
    void init();
    void display();
    void enableLight();
    void disableLight();
    void lightOnOf();
    //void initGL();
    //void displayCB();
    //void draw();
    //void initSharedMem();
    //void keyboardFunc (unsigned char, int, int);

    //direction moving buttons
     void plusXdistance1(int dist);
     void minusXdistance1(int dist);
     void plusYdistance1(int dist);
     void minusYdistance1(int dist);
     void plusZdistance1(int dist);
     void minusZdistance1(int dist);
    //rotation buttons
     void plusXrotation1(int angle);
     void minusXrotation1(int angle);
     void plusYrotation1(int angle);
     void minusYrotation1(int angle);
     void plusZrotation1(int angle);
     void minusZrotation1(int angle);

private:
     QTimer timer1;

};

#endif // GLWIDGET1_H
