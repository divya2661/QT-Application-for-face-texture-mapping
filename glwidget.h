#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include <string>

extern std::string WrlFileName;
extern QString imagename0;
extern int textureError;

struct Image0 {

   int sizeX;

   int sizeY;

   char *data;

};


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:

    explicit GLWidget(QWidget *parent = 0);

    GLfloat vertices2[100000];
    GLushort indices[100000];
    GLfloat V[100000];
    GLfloat Ver[100000];
    int numTriangle;
    int maxVertices;
    int maxIndices;
    float cameraDistance=0.0;
    GLuint texName;


    int ImageLoad(const char *filename, Image0 *image);
    Image0 * loadTexture();
    void setWRL(std::string filename);
    void initializeGL();
    void initialize(std::string filename);
    void paintGL();
    void resizeGL(int,int);
    void initGL();
    void draw();

    //void displayCB();
    //void init();
    //void display();
   // void initSharedMem();
    //void keyboardFunc (unsigned char, int, int);

   //direction moving buttons
    void plusXdistance(int dist);
    void minusXdistance(int dist);
    void plusYdistance(int dist);
    void minusYdistance(int dist);
    void plusZdistance(int dist);
    void minusZdistance(int dist);
   //rotation buttons
    void plusXrotation(int angle);
    void minusXrotation(int angle);
    void plusYrotation(int angle);
    void minusYrotation(int angle);
    void plusZrotation(int angle);
    void minusZrotation(int angle);


private:

    QTimer timer;
    QTimer itime;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
};

#endif // GLWIDGET_H
