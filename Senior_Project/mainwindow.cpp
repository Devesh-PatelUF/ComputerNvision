#include "mainwindow.h"
#include "./ui_mainwindow.h"


QTextToSpeech *speech = new QTextToSpeech();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    loadingVal = 0;

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
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->progressBar->setRange(0,100);
    updateLoading();

    //displaying the videofeed from the web
    view = new QWebEngineView;
    view->load(QUrl("http://192.168.1.214/"));
    view->setGeometry(225,90,800,600);
    view->setParent(ui->centralwidget);
    view->show();

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessComplete()));


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


        //saving to file
        QFile file("../image/gptImage.png");
        file.open(QIODevice::WriteOnly);
        QPixmap imageMap = ui->imageLabel->pixmap();
        imageMap.save(&file, "PNG");



        //DO CHATGPT STUFF FOR OBJECT IDENTIFICATION USING A PYTHON SCRIPT

        //QStringList params = QStringList() << "../Python/chatgptScript.py";
        QStringList params = QStringList() << "../Python/chatgptScript.py";
        process.start("python", params);

        //DO LOADING SCREEN STUFF HERE
        ui->loadingWindow->setVisible(true);
        ui->loadingText->setVisible(true);
        ui->progressBar->setVisible(true);
        for( int i = 0; i <=99; ++i ) {
            loadingVal = i;
            delay(60);
            updateLoading();
        }











    }
    else //act as replay audio button
    {
        //ui->objectNameLabel->setText("Sup bro!");
        QString text = ui->objectNameLabel->text() + ". " + ui->definitionLabel->text();

        //Say Name of Object
       // speech->say(ui->objectNameLabel->text());

        //Say Definition
        speech->say(text);

        ui->continueButton->setChecked(true);
        qDebug( "Replay audio button clicked" );
    }
}
void MainWindow::onProcessComplete()
{

    if(loadingVal != 99){
        for( int i = loadingVal; i <=100; ++i ) {
            loadingVal = i;
            delay(25);
            updateLoading();
        }
    }

    loadingVal = 100;
    updateLoading();
    delay(500);
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->progressBar->setVisible(false);
    loadingVal = 0;
    updateLoading();

    ui->recaptureButton->setChecked(true);
    ui->continueButton->setChecked(true);
    ui->definitionLabel->setVisible(true);
    ui->objectNameLabel->setVisible(true);
    ui->imageLabel->setGeometry(280,180, 704, 528);

    ui->recaptureButton->setChecked(true);
    ui->continueButton->setChecked(true);
    ui->definitionLabel->setVisible(true);
    ui->objectNameLabel->setVisible(true);
    ui->imageLabel->setGeometry(280,180, 704, 528);
    qDebug("testing");
    QString proc_stdout = process.readAllStandardOutput();
    qDebug(proc_stdout.toLatin1());

    QStringList lines = proc_stdout.split( ": ");
    ui->objectNameLabel->setText(lines[0]);
    ui->definitionLabel->setText(lines[1]);

    QString text = ui->objectNameLabel->text() + " " + ui->definitionLabel->text();

    //Say Name of Object
    //speech->say(ui->objectNameLabel->text());

    //Say Definition
    speech->say(text);

    ui->recaptureButton->setText("New Object");
    ui->continueButton->setText("Replay Audio");

}

void MainWindow::updateLoading(){
    ui->progressBar->setValue(loadingVal);
}

void MainWindow::delay(double time)
{
    QTime delay = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < delay)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

