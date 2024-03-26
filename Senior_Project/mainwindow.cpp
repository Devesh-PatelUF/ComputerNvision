#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextToSpeech>
#include <QMouseEvent>
#include <QProcess>
#include <QString>
#include <QFile>



QTextToSpeech *speech = new QTextToSpeech();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setGeometry(225, 90, 800, 600);





    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->definitionLabel->setVisible(false);
    ui->objectNameLabel->setVisible(false);
    ui->recaptureButton->setCheckable(true);
    ui->continueButton->setCheckable(true);
    ui->imageLabel->setVisible(false);
    ui->definitionLabel->setWordWrap(true);

    //displaying the videofeed from the web
    view = new QWebEngineView;
    view->load(QUrl("http://192.168.1.214/"));
    view->setGeometry(225,90,800,600);
    view->setParent(ui->centralwidget);
    view->show();


    // Set locale.
    speech->setLocale(QLocale(QLocale::English, QLocale::LatinScript, QLocale::UnitedStates));
}

MainWindow::~MainWindow()
{
    delete view;
    delete ui;
}


Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_captureButton_clicked()
{
    qDebug( "Capture button clicked" );

    QString relativePath;
    relativePath = "../Senior_Project/image/object_image.jpg";

    QPixmap image;
    image = view->grab();

    QPixmap pic(relativePath);
    ui->imageLabel->setPixmap(image);
    //for using the relative path
    //ui->imageLabel->setPixmap(relativePath);


    ui->recaptureButton->setChecked(false);
    ui->continueButton->setChecked(false);
    ui->objectNameLabel->setText("Is this picture correct?");
    ui->objectNameLabel->setVisible(true);

    ui->recaptureButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->captureButton->setVisible(false);

    ui->imageLabel->setVisible(true);
    view->hide();
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
        ui->objectNameLabel->setVisible(false);
        ui->definitionLabel->setVisible(false);
        ui->imageLabel->setGeometry(225, 90, 800, 600);

    }
    ui->objectNameLabel->setText("Object Name");
    ui->objectNameLabel->setVisible(false);
    ui->imageLabel->clear();
    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->captureButton->setVisible(true);
    ui->objectNameLabel->setText("Take another picture!");

    ui->imageLabel->setVisible(false);
    view->show();
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


        //saving to file
        QFile file("../image/gptImage.png");
        file.open(QIODevice::WriteOnly);
        QPixmap imageMap = ui->imageLabel->pixmap();
        imageMap.save(&file, "PNG");



        //DO CHATGPT STUFF FOR OBJECT IDENTIFICATION USING A PYTHON SCRIPT

        QStringList params = QStringList() << "../Python/chatgptScript.py";
        QProcess process;
        process.start("python", params);

        process.waitForFinished(-1); // will wait forever until finished


        QString proc_stdout = process.readAllStandardOutput();
        qDebug(proc_stdout.toLatin1());
        QString proc_stderr = process.readAllStandardError();
        qDebug(proc_stderr.toLatin1());

        QStringList lines = proc_stdout.split( ": ");
        ui->objectNameLabel->setText(lines[0]);
        ui->definitionLabel->setText(lines[1]);

        //ui->definitionLabel->adjustSize();










        QString text = ui->objectNameLabel->text() + " " + ui->definitionLabel->text();

        //Say Name of Object
        //speech->say(ui->objectNameLabel->text());

        //Say Definition
        speech->say(text);

        ui->recaptureButton->setText("New Object");
        ui->continueButton->setText("Replay Audio");
    }
    else //act as replay audio button
    {
        //ui->objectNameLabel->setText("Sup bro!");
        QString text = ui->objectNameLabel->text() + " " + ui->definitionLabel->text();

        //Say Name of Object
       // speech->say(ui->objectNameLabel->text());

        //Say Definition
        speech->say(text);

        ui->continueButton->setChecked(true);
        qDebug( "Replay audio button clicked" );
    }
}

