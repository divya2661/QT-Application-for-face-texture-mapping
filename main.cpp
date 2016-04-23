#include "window.h"
#include <QApplication>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <QDebug>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QDesktopWidget>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/bind.hpp>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativedebug.h>
//header file to define grammer for parsing
#include "grammer.hpp"
#include "function.h"
#include "point.h"
#include "index.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    //QDeclarativeDebuggingEnabler enabler;
    glutInit(&argc,argv);
    QApplication a(argc, argv);
    QDesktopWidget dw;
    Window w;
    int x=dw.width()*0.55;
    int y=dw.height()*0.73;
    w.setFixedSize(x,y);
    w.setInitialImage();
    Dialog d;

    d.setModal(true);
    d.setFixedSize(x*.55,y*.5);
    if(d.exec()==QDialog::Accepted)
    {
        w.show();
        w.setImage();
    }

    return a.exec();
}
