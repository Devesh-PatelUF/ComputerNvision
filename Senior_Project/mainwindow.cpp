#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextToSpeech>
#include <QMouseEvent>

QTextToSpeech *speech = new QTextToSpeech();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->setScaledContents(true);




    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->definitionLabel->setVisible(false);
    ui->objectNameLabel->setVisible(false);
    ui->recaptureButton->setCheckable(true);
    ui->continueButton->setCheckable(true);

    // Set locale.
    speech->setLocale(QLocale(QLocale::English, QLocale::LatinScript, QLocale::UnitedStates));
}

MainWindow::~MainWindow()
{
    delete ui;
}


Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

void MainWindow::on_captureButton_clicked()
{
    qDebug( "Capture button clicked" );

    QString relativePath;
    relativePath = "../Senior_Project/image/object_image.jpg";

    QPixmap pic(relativePath);
    ui->imageLabel->setPixmap(pic);

    ui->recaptureButton->setChecked(false);
    ui->continueButton->setChecked(false);
    ui->objectNameLabel->setText("Is this picture correct?");
    ui->objectNameLabel->setVisible(true);

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
        ui->objectNameLabel->setVisible(true);
        ui->definitionLabel->setVisible(false);
        ui->imageLabel->setGeometry(210, 90, 800, 600);

    }
    ui->objectNameLabel->setText("Object Name");
    //ui->objectNameLabel->setVisible(false);
    ui->imageLabel->clear();
    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->captureButton->setVisible(true);
    ui->objectNameLabel->setText("Take another picture!");
}


void MainWindow::on_continueButton_clicked(bool checked)
{
    if (checked) //act as continue button
    {
        qDebug( "Continue button clicked" );
        ui->recaptureButton->setChecked(true);
        ui->continueButton->setChecked(true);
        ui->definitionLabel->setVisible(true);
        ui->objectNameLabel->setVisible(true);
        ui->imageLabel->setGeometry(280,180, 704, 528);

         ui->objectNameLabel->setText("Object");

        //Say Name of Object
        speech->say(ui->objectNameLabel->text());

        //Say Definition
        speech->say(ui->definitionLabel->text());

        ui->recaptureButton->setText("New Object");
        ui->continueButton->setText("Replay Audio");

        ui->recaptureButton->setVisible(true);
        ui->continueButton->setVisible(true);
    }
    else //act as replay audio button
    {

        ui->definitionLabel->setVisible(true);
        ui->objectNameLabel->setVisible(true);
        ui->objectNameLabel->setText("Object");
        ui->definitionLabel->setText("Definition");



        //Say Name of Object
        speech->say(ui->objectNameLabel->text());

        //Say Definition
        speech->say(ui->definitionLabel->text());
        ui->continueButton->setChecked(true);
        qDebug( "Replay audio button clicked" );
    }
}

