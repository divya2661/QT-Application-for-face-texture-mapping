#ifndef MDIALOG_H
#define MDIALOG_H
#include "glwidget.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QDialog>

namespace Ui {
class MDialog;
}

class MDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MDialog(QWidget *parent = 0);
    ~MDialog();

    int rotateAngle1=0;
    int movePos1=0;



private slots:
    void on_close_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);


    void on_zoomMapIn_clicked();

    void on_zoomMapOut_clicked();

    void on_moveMapPX_clicked();

    void on_moveMapMX_clicked();

    void on_moveMapPY_clicked();

    void on_moveMapMY_clicked();

    void on_rotateMapPX_clicked();

    void on_rotateMapMX_clicked();

    void on_rotateMapPY_clicked();

    void on_rotateMapMY_clicked();

    void on_rotateMapPZ_clicked();

    void on_rotateMapMZ_clicked();

    void on_light_clicked();

    void on_lightOf_clicked();

private:
    Ui::MDialog *ui;
};

#endif // MDIALOG_H
