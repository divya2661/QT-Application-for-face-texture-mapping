#include <iostream>
#include "window.h"
#include "ui_window.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "glwidget.h"
#include "glwidget1.h"
#include "mdialog.h"
#include "dialog.h"
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>

Window::Window(QWidget *parent):QMainWindow(parent),ui(new Ui::Window)
{
    ui->setupUi(this);
    //qDebug()<<imagename<<'\n';
}


Window::~Window()
{
    delete ui;
}


void Window::setInitialImage()
{
    QPixmap pix(":/face_image002.jpg");
    ui->label_pic->setPixmap(pix);
} int rotateAngle1;
int movePos1;

void Window::setImage()
{
    if(textureError==1)
    {
        ui->map->setEnabled(false);
    }
    else
    {

        QPixmap pix(imagename);
        ui->label_pic->setPixmap(pix);
    }

}

void Window::on_map_clicked()
{
    MDialog md;
    QDesktopWidget dw;
    int x = dw.width()*0.44;
    int y = dw.height()*0.64;
    md.setFixedSize(x,y);
    md.setModal(true);
    md.exec();
}

void Window::on_horizontalSlider_sliderMoved(int position)
{
    rotateAngle = position;
}

void Window::on_horizontalSlider_2_sliderMoved(int position)
{
    movePos = position;
}

void Window::on_zoomOut_clicked()
{

    GLWidget *glw = new GLWidget;
    glw->plusZdistance(movePos);
}

void Window::on_zoomIn_clicked()
{

    GLWidget *glw = new GLWidget;
    glw->minusZdistance(movePos);
}

void Window::on_movePX_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->plusXdistance(movePos);
}

void Window::on_moveMX_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->minusXdistance(movePos);
}

void Window::on_movePY_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->plusYdistance(movePos);
}

void Window::on_moveMY_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->minusYdistance(movePos);
}

void Window::on_rotatePX_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->plusXrotation(rotateAngle);
}

void Window::on_rotateMX_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->minusXrotation(rotateAngle);
}

void Window::on_rotatePY_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->plusYrotation(rotateAngle);
}

void Window::on_rotateMY_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->minusYrotation(rotateAngle);
}

void Window::on_rotatePZ_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->plusZrotation(rotateAngle);
}

void Window::on_rotateMZ_clicked()
{
    GLWidget *glw = new GLWidget;
    glw->minusZrotation(rotateAngle);
}

void Window::on_closemain_clicked()
{

    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}
