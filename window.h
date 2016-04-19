#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSlider>



namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    int rotateAngle=0;
    int movePos=0;


    explicit Window(QWidget *parent = 0);
    ~Window();
    void setInitialImage();
    void setImage();


private slots:


    void on_zoomOut_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_zoomIn_clicked();

    void on_map_clicked();

    void on_movePX_clicked();

    void on_moveMX_clicked();

    void on_movePY_clicked();

    void on_moveMY_clicked();

    void on_rotatePX_clicked();

    void on_rotateMX_clicked();

    void on_rotateMY_clicked();

    void on_rotatePY_clicked();

    void on_rotatePZ_clicked();

    void on_rotateMZ_clicked();

    void on_closemain_clicked();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
