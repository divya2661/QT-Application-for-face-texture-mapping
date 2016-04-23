#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    int wrl_empty_error=1;
    int image_empty_error=1;

private slots:
    void on_openWrl_clicked();

    void on_openImg_clicked();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
