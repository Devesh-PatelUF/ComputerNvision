#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPalette>
#include <QDebug>
#include <QPixmap>
#include <QDir>


MainWindow::MainWindow(QWidget *parent, QString dirPath)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->dirPath = dirPath;
    ui->setupUi(this);

    ui->imageLabel->setScaledContents(true);




    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->definitionLabel->setVisible(false);
    ui->recaptureButton->setCheckable(true);
    ui->continueButton->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_captureButton_clicked()
{
    qDebug( "Capture button clicked" );

    QDir dir(dirPath);
    QString relativePath;
    relativePath = dir.relativeFilePath("C:/Users/deves/Desktop/College/Year 4/Semester 2/Senior Project/Project/Computer-nVision/Senior_Project/image/object_image.jpg");
    QPixmap pic(relativePath);
    ui->imageLabel->setPixmap(pic);

    ui->recaptureButton->setChecked(false);
    ui->continueButton->setChecked(false);

    ui->recaptureButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->captureButton->setVisible(false);

}


void MainWindow::on_recaptureButton_clicked(bool checked)
{
    if (checked) //act as recapture button
    {
        qDebug( "Recapture button clicked" );
    }
    else { //act as new object button
        qDebug( "New Object button clicked" );
        ui->recaptureButton->setText("Recapture");
        ui->continueButton->setText("Continue");
        ui->definitionLabel->setVisible(false);
        ui->imageLabel->setGeometry(210, 90, 800, 600);

    }
    ui->imageLabel->clear();
    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->captureButton->setVisible(true);
}


void MainWindow::on_continueButton_clicked(bool checked)
{
    if (checked) //act as continue button
    {
        qDebug( "Continue button clicked" );
        ui->recaptureButton->setChecked(true);
        ui->continueButton->setChecked(true);
        ui->definitionLabel->setVisible(true);
        ui->imageLabel->setGeometry(280,180, 704, 528);


        ui->recaptureButton->setText("New Object");
        ui->continueButton->setText("Replay Audio");
    }
    else //act as replay audio button
    {
        ui->continueButton->setChecked(true);
        qDebug( "Replay audio button clicked" );
    }
}

