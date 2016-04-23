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
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
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
        ui->wrl_path->setText(fName);
        WrlFileName = file;
        WrlFileName1 = file;
        wrl_empty_error = 0;
        if(wrl_empty_error==0 && image_empty_error==0)
        {

            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

        }
    }
    else{
        ui->wrl_path->setText("Please select a wrl file");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void Dialog::on_openImg_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),tr("Text Files (*.bmp)"));
    if (!fName.isEmpty()) {

        ui->image_path->setText(fName);
        imagename = fName;
        imagename0 = fName;
        image_empty_error=0;
        if(wrl_empty_error==0 && image_empty_error==0)
        {

            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }

    }
    else
    {
        ui->image_path->setText("Please select a bmp Image");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
