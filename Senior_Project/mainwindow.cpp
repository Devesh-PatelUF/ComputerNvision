





#include "mainwindow.h"
#include "./ui_mainwindow.h"


QTextToSpeech *speech = new QTextToSpeech();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mode = "standard";


    loadingVal = 0;

    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setGeometry(225, 90, 800, 600);






    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->definitionLabel->setVisible(false);
    ui->objectNameLabel->setVisible(true);
    ui->recaptureButton->setCheckable(true);
    ui->continueButton->setCheckable(true);
    ui->imageLabel->setVisible(true);
    ui->definitionLabel->setWordWrap(true);
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->comboBox->setVisible(true);
    ui->progressBar->setVisible(false);
    ui->progressBar->setRange(0,100);
    ui->objectNameLabel->setText("Object Identifier");
    updateLoading();

    //displaying the videofeed from the web
    view = new QWebEngineView;
    view->load(QUrl("http://192.168.231.63/"));
    view->setGeometry(225,90,800,600);
    view->setParent(ui->centralwidget);
    view->show();

    view->setZoomFactor(1.21);


    ui->imageLabel->setVisible(true);
    ui->imageLabel->clear();
    ui->imageLabel->raise();
    //view->setStyleSheet("border-color: #0021A5; border-style: solid; border-width: 13px; border-radius: 15px;");

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessComplete()));


    // Set locale.
    speech->setLocale(QLocale(QLocale::English, QLocale::LatinScript, QLocale::UnitedStates));
}

MainWindow::~MainWindow()
{
    delete view;
    delete ui;
    delete speech;

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //float x = 0.0;
    //float y = 0.0;
    view->setGeometry(this->width()/2 - view->width()/2,
                      this->height()/2-360,
                      view->width(),
                      view->height());

    ui->captureButton->setGeometry(this->width()/2 - ui->captureButton->width()/2,
                                   this->height()/2 + 300,
                                   ui->captureButton->width(),
                                   ui->captureButton->height());
    //x = this->width()/ui->continueButton->width();
    //y = this->width()/ui->continueButton->width();
    //if text == new object


    if (ui->recaptureButton->text() == "New Object") {
        ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                    this->height()/2 - ui->imageLabel->height()/2,
                                    ui->imageLabel->width(),
                                    ui->imageLabel->height());


        ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                         80,
                                         ui->imageLabel->width(),
                                         ui->imageLabel->y() - ui->definitionLabel->y());
        if(mode == "verbose")
        {
            ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                             ui->objectNameLabel->y(),
                                             ui->imageLabel->width(),
                                             ui->imageLabel->y() - ui->definitionLabel->y());
        }

    }

    else {
        ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                    this->height()/2 - 360,
                                    ui->imageLabel->width(),
                                    ui->imageLabel->height());


    }

    ui->continueButton->setGeometry(this->width()/2 + 75,
                                    this->height()/2 + 300,
                                    ui->continueButton->width(),
                                    ui->continueButton->height());

    ui->recaptureButton->setGeometry(this->width()/2 - 521,
                                     this->height()/2 + 300,
                                     ui->recaptureButton->width(),
                                     ui->recaptureButton->height());
    ui->objectNameLabel->setGeometry(this->width()/2 - ui->objectNameLabel->width()/2,
                                     10,
                                     ui->objectNameLabel->width(),
                                     ui->objectNameLabel->height());
    ui->comboBox->setGeometry(this->width()/2 - 600,
                                     150,
                                     ui->comboBox->width(),
                                     ui->comboBox->height());
    ui->progressBar->setGeometry(this->width()/2 - ui->progressBar->width()/2,
                                 this->height()/2 + 60,
                                 ui->progressBar->width(),
                                 ui->progressBar->height());
    ui->loadingWindow->setGeometry(this->width()/2 - ui->loadingWindow->width()/2,
                                   this->height()/2 - ui->loadingWindow->height()/2,
                                   ui->loadingWindow->width(),
                                   ui->loadingWindow->height());
    ui->loadingText->setGeometry(this->width()/2 - ui->loadingText->width()/2,
                                 this->height()/2 - ui->loadingText->height()/2,
                                 ui->loadingText->width(),
                                 ui->loadingText->height());
    ui->reloadButton->setGeometry(this->width()/2 + 420,
                                  this->height()/2 - 350,
                                  ui->reloadButton->width(),
                                  ui->reloadButton->height());
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
    ui->reloadButton->setVisible(false);
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
        ui->definitionLabel->move(ui->definitionLabel->x(),60);
        ui->imageLabel->setGeometry(225, 90, 800, 600); //////////////////////////
        ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                    this->height()/2 - 360,
                                    ui->imageLabel->width(),
                                    ui->imageLabel->height());
        speech->stop();

    }
    ui->objectNameLabel->setVisible(true);
    ui->imageLabel->clear();
    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->captureButton->setVisible(true);
    ui->comboBox->setVisible(true);
    ui->objectNameLabel->setText("Object Identifier");

    ui->imageLabel->setVisible(true);
    ui->reloadButton->setVisible(true);
    ui->imageLabel->clear();
    ui->imageLabel->raise();
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
        QStringList params = QStringList() << "../Python/chatgptScript.py" << mode;
        process.start("python", params);

        //DO LOADING SCREEN STUFF HERE
        ui->imageLabel->lower();
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

    ui->imageLabel->raise();
    ui->recaptureButton->setChecked(true);
    ui->comboBox->setVisible(false);
    ui->continueButton->setChecked(true);
    ui->definitionLabel->setVisible(true);
    ui->objectNameLabel->setVisible(true);
    ui->imageLabel->setGeometry(280,180, 704, 528);/////////////////////////////////////////////////
    ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                this->height()/2 - ui->imageLabel->height()/2,
                                ui->imageLabel->width(),
                                ui->imageLabel->height());
    ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                     80,
                                     ui->imageLabel->width(),
                                     ui->imageLabel->y() - ui->definitionLabel->y());

    qDebug("testing");
    QString proc_stdout = process.readAllStandardOutput();
    qDebug(proc_stdout.toLatin1());



    if(mode == "standard"){
        if(proc_stdout.contains(":") == false)
        {
            ui->objectNameLabel->setText("Error");
            ui->definitionLabel->setText("There was an issue with identifying the object. Please try again! ");
        }
        else{
            QStringList lines = proc_stdout.split( ": ");
            ui->objectNameLabel->setText(lines[0]);
            ui->definitionLabel->setText(lines[1]);
        }

        QString text = ui->objectNameLabel->text() + " " + ui->definitionLabel->text();
        speech->say(text);

    }
    else{

        ui->definitionLabel->move(ui->definitionLabel->x(), ui->objectNameLabel->y());
        ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                         ui->definitionLabel->y(),
                                         ui->imageLabel->width(),
                                         ui->imageLabel->y() - ui->definitionLabel->y());

        ui->definitionLabel->setText(proc_stdout);
        ui->objectNameLabel->setVisible(false);

        QString text = ui->definitionLabel->text();
        speech->say(text);
    }

    //Say Name of Object
    //speech->say(ui->objectNameLabel->text());

    //Say Definition
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


void MainWindow::on_comboBox_activated(int index)
{
    mode = ui->comboBox->currentText().toLower();
    qDebug(mode.toLatin1());
}



void MainWindow::on_reloadButton_clicked()
{
    QRect temp = view->geometry();
    delete view;
    view = new QWebEngineView;
    view->load(QUrl("http://192.168.231.63/"));
    view->setGeometry(temp);
    view->setParent(ui->centralwidget);
    view->show();
    view->lower();

    view->setZoomFactor(1.21);
}

