#include "mdialog.h"
#include "ui_mdialog.h"
#include "glwidget.h"
#include <QDebug>

MDialog::MDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MDialog)
{
    ui->setupUi(this);
}

MDialog::~MDialog()
{
    delete ui;
}

void MDialog::on_close_clicked()
{
    this->close();
}

void MDialog::on_horizontalSlider_sliderMoved(int position)
{
    rotateAngle1 = position;
}

void MDialog::on_horizontalSlider_2_sliderMoved(int position)
{
    movePos1 = position;
    //qDebug()<<movePos1<<'\n';
}

void MDialog::on_zoomMapIn_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusZdistance1(movePos1);
}

void MDialog::on_zoomMapOut_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusZdistance1(movePos1);
}

void MDialog::on_moveMapPX_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusXdistance1(movePos1);
}

void MDialog::on_moveMapMX_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusXdistance1(movePos1);
}

void MDialog::on_moveMapPY_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusYdistance1(movePos1);
}

void MDialog::on_moveMapMY_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusYdistance1(movePos1);
}

void MDialog::on_rotateMapPX_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusXrotation1(rotateAngle1);
}

void MDialog::on_rotateMapMX_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusXrotation1(rotateAngle1);
}

void MDialog::on_rotateMapPY_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusYrotation1(rotateAngle1);
}

void MDialog::on_rotateMapMY_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusYrotation1(rotateAngle1);
}

void MDialog::on_rotateMapPZ_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->plusZrotation1(rotateAngle1);
}

void MDialog::on_rotateMapMZ_clicked()
{
    GLWidget1 *glw = new GLWidget1;
    glw->minusZrotation1(rotateAngle1);
}

void MDialog::on_light_clicked()
{
   GLWidget1 *glw = new GLWidget1;
   glw->lightOnOf();
}

void MDialog::on_lightOf_clicked()
{
     GLWidget1 *glw = new GLWidget1;
     glw->disableLight();
}
