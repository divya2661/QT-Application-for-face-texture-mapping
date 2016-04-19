#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "glwidget.h"
#include "glwidget1.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_openWrl_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),tr("Text Files (*.wrl)"));
    if (!fName.isEmpty()) {


        std::string file = fName.toUtf8().constData();
        ui->wrlPath->setText(fName);
        WrlFileName = file;
        WrlFileName1 = file;
    }
}

void Dialog::on_openImg_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),tr("Text Files (*.bmp)"));
    if (!fName.isEmpty()) {

        ui->imagePath->setText(fName);
        imagename = fName;
    }
}
