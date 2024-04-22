#include "mainwindow.h"
#include "./ui_mainwindow.h"



//Speech object for text to speech
QTextToSpeech *speech = new QTextToSpeech();


//constructor, set default values, make objects, place them, initialize objects for later
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mode = "standard";


    loadingVal = 0;

    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setGeometry(225, 90, 800, 600);

    //default video feed url
    url = "http://192.168.231.63/";


    //setting default values
    ui->recaptureButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->definitionLabel->setVisible(false);
    ui->objectNameLabel->setVisible(true);
    ui->recaptureButton->setCheckable(true);
    ui->continueButton->setCheckable(true);
    ui->reloadButton_2->setCheckable(true);
    ui->imageLabel->setVisible(true);
    ui->definitionLabel->setWordWrap(true);
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->comboBox->setVisible(true);
    ui->progressBar->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->progressBar->setRange(0,100);
    ui->objectNameLabel->setText("Object Identifier");
    updateLoading();

    //displaying the videofeed from the web-
    view = new QWebEngineView;
    view->load(QUrl(url));
    view->setGeometry(225,90,800,600);
    view->setParent(ui->centralwidget);
    view->show();

    view->setZoomFactor(1.21);

    //displaying border
    ui->imageLabel->setVisible(true);
    ui->imageLabel->clear();
    ui->imageLabel->raise();
    //ui->textEdit->raise();

    //view->setStyleSheet("border-color: #0021A5; border-style: solid; border-width: 13px; border-radius: 15px;");


    //connecting signals from process complete to associated functions
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessComplete()));

    connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(onProcessError_()));


    // Set locale
    speech->setLocale(QLocale(QLocale::English, QLocale::LatinScript, QLocale::UnitedStates));

    //Get voices and display them in debug
    QList<QVoice> availableVoices = speech->availableVoices();
    QStringList voices;

    for (int i = 0; i < availableVoices.size(); ++i) {
        qDebug(availableVoices[i].name().toLatin1());
        voices.append(availableVoices[i].name());
    }
    speech->setVoice(availableVoices[0]);

    //setting items in voice selection widget
    ui->comboBox_2->addItems(voices);
}

//deconstructor delete all allocated objects
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


    ///setting differnet default positions for each widget in the UI
    /// positions are relative to the midpoint of the window
    /// height and width do not change
    /// offset from midpoint are pre-determined based on original position
    view->setGeometry(this->width()/2 - view->width()/2,
                      this->height()/2-360,
                      view->width(),
                      view->height());

    ui->captureButton->setGeometry(this->width()/2 - ui->captureButton->width()/2,
                                   this->height()/2 + 300,
                                   ui->captureButton->width(),
                                   ui->captureButton->height());

    // checking which buttons are enabled based on text being currently displayed
    if (ui->recaptureButton->text() == "New Object") {
        ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                    this->height()/2 - ui->imageLabel->height()/2,
                                    ui->imageLabel->width(),
                                    ui->imageLabel->height());


        ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                         80,
                                         ui->imageLabel->width(),
                                         ui->imageLabel->y() - ui->definitionLabel->y());
        //checking for different modes, changing based on the mode
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
    ui->comboBox_2->setGeometry(this->width()/2 - 570,
                              10,
                              ui->comboBox_2->width(),
                              ui->comboBox_2->height());
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
    ui->textEdit->setGeometry(this->width()/2 - ui->textEdit->width()/2,
                                 this->height()/2 - 200,
                                 ui->textEdit->width(),
                                 ui->textEdit->height());
    ui->reloadButton->setGeometry(this->width()/2 + 420,
                                  this->height()/2 - 350,
                                  ui->reloadButton->width(),
                                  ui->reloadButton->height());
    ui->reloadButton_2->setGeometry(this->width()/2 + 420,
                                  this->height()/2 - 275,
                                  ui->reloadButton_2->width(),
                                  ui->reloadButton_2->height());
    ui->reloadButton_3->setGeometry(this->width()/2 - 630,
                                  5,
                                  ui->reloadButton_3->width(),
                                  ui->reloadButton_3->height());
}


Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}


//function for changing UI when captur button is clicked
void MainWindow::on_captureButton_clicked()
{
    qDebug( "Capture button clicked" );

    //Take a "screenshot" of the webview, setting it as the image shown to the user
    QPixmap image;
    image = view->grab();

    ui->imageLabel->setPixmap(image);


    ui->recaptureButton->setChecked(false);
    ui->reloadButton->setVisible(false);
    ui->continueButton->setChecked(false);
    ui->objectNameLabel->setText("Is this picture correct?");
    ui->objectNameLabel->setVisible(true);

    ui->recaptureButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->captureButton->setVisible(false);
    ui->reloadButton_2->setVisible(false);

    ui->imageLabel->setVisible(true);
    view->hide();
}

//Function for when recapture button and New object button are clicked. Both are using the same UI push button
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
        speech->stop(); //stopping speech if its running

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
    ui->reloadButton_2->setVisible(true);
    ui->imageLabel->clear();
    ui->imageLabel->raise();
    view->show();
}

//Function for when the continue button or replay audio button are clicked. Both use the same UI push button
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



        //Running chatgpt script
        QStringList params = QStringList() << "../Python/chatgptScript.py" << mode;
        process.start("python", params);

        //Starting Loading Screen
        ui->imageLabel->lower();
        ui->loadingWindow->setVisible(true);
        ui->loadingText->setVisible(true);
        ui->progressBar->setVisible(true);

        //disabling any buttons visible
        ui->continueButton->setEnabled(false);
        ui->recaptureButton->setEnabled(false);
        ui->reloadButton_3->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);

        //Loading bar up to 99, with 1 ms delays
        for( int i = 0; i <=99; ++i ) {
            loadingVal = i;
            delay(60);
            updateLoading();
        }

        //if process takes more than 20 seconds, then it times out and we give an error message
        process.waitForFinished(20000);
        if(process.state() != QProcess::NotRunning)
        {
            qDebug("process timed out");
            process.kill();
            onProcessError_();
        }


    }
    else //act as replay audio button
    {
        QString text = ui->objectNameLabel->text() + ". " + ui->definitionLabel->text();

        //Say Name of Object

        //Say Definition
        speech->say(text);

        ui->continueButton->setChecked(true);
        qDebug( "Replay audio button clicked" );
    }
}

//Function for when chatgpt script finishes correctly
void MainWindow::onProcessComplete()
{

    //finishing the loading bar
    if(loadingVal != 99){
        for( int i = loadingVal; i <=100; ++i ) {
            loadingVal = i;
            delay(25);
            updateLoading();
        }
    }

    //updating and hiding the loading bar
    loadingVal = 100;
    updateLoading();
    delay(500);
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->progressBar->setVisible(false);
    loadingVal = 0;
    updateLoading();

    //showing new ui elements, hiding old ones, resizing, updating text

    ui->continueButton->setEnabled(true);
    ui->recaptureButton->setEnabled(true);
    ui->reloadButton_3->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
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

    //getting command line output from chatgpt script
    QString proc_stdout = process.readAllStandardOutput();
    qDebug(proc_stdout.toLatin1());



    //if standard mode, object name at top, definition below it
    if(mode == "standard"){
        //checking that the returned string from chatgpt is formatted correctly, if not error!
        if(proc_stdout.contains(":") == false)
        {
            ui->objectNameLabel->setText("Error");
            ui->definitionLabel->setText("There was an issue with identifying the object. Please try again! ");
        }
        else{
            //Splitting output for proper displaying in standard mode
            QStringList lines = proc_stdout.split( ": ");
            ui->objectNameLabel->setText(lines[0]);
            ui->definitionLabel->setText(lines[1]);
        }

        //Text to Speech
        QString text = ui->objectNameLabel->text() + " " + ui->definitionLabel->text();
        speech->say(text);

    }
    //displaying output string in one text box if in verbose mode
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

    //Say Definition
    ui->recaptureButton->setText("New Object");
    ui->continueButton->setText("Replay Audio");

}

//Helper function for updating the progress bar's value
void MainWindow::updateLoading(){
    ui->progressBar->setValue(loadingVal);
}

//Helper function to create a delay. Time is the miliseconds that will be delayed. NOTE: it feezes runtime so use with small, unnoticable values
void MainWindow::delay(double time)
{
    QTime delay = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < delay)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


//ComboBox function, updating the mode when it switches from standard to verbose
void MainWindow::on_comboBox_activated(int index)
{
    mode = ui->comboBox->currentText().toLower();
    qDebug(mode.toLatin1());
}

//Reload button function. Delete old view, make a new one with the current url
void MainWindow::on_reloadButton_clicked()
{
    QRect temp = view->geometry();
    delete view;
    view = new QWebEngineView;
    view->load(QUrl(url));
    view->setGeometry(temp);
    view->setParent(ui->centralwidget);
    view->show();
    view->lower();

    view->setZoomFactor(1.21);
}

//function for when process finishes with an error
void MainWindow::onProcessError_()
{
    //Finish the loading screen
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

    //get to next screen so error message can be displayed. Same as onProcessComplete()
    ui->loadingWindow->setVisible(false);
    ui->loadingText->setVisible(false);
    ui->progressBar->setVisible(false);
    loadingVal = 0;
    updateLoading();

    ui->continueButton->setEnabled(true);
    ui->recaptureButton->setEnabled(true);
    ui->reloadButton_3->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);

    ui->imageLabel->raise();
    ui->recaptureButton->setChecked(true);
    ui->comboBox->setVisible(false);
    ui->continueButton->setChecked(true);
    ui->definitionLabel->setVisible(true);
    ui->objectNameLabel->setVisible(true);

    ui->imageLabel->setGeometry(this->width()/2 - ui->imageLabel->width()/2,
                                this->height()/2 - ui->imageLabel->height()/2,
                                ui->imageLabel->width(),
                                ui->imageLabel->height());
    ui->definitionLabel->setGeometry(ui->imageLabel->x(),
                                     80,
                                     ui->imageLabel->width(),
                                     ui->imageLabel->y() - ui->definitionLabel->y());


    //Get error message string
    QString proc_stdout = process.readAllStandardError();


    //checking error type, type is python file missing
    if(proc_stdout.contains("No such file or directory") && proc_stdout.contains("python: can't open file")) {
        ui->objectNameLabel->setText("Error: Python File Not Found");
        ui->definitionLabel->setText("The python file could not be opened as the specified directory or file does not exist.");
    }

    //checking error type, type is gptImage file missing/was never saved
    else if(proc_stdout.contains("No such file or directory: '../image/gptImage.png'")) {
        ui->objectNameLabel->setText("Error: Image File Not Found");
        ui->definitionLabel->setText("The image file could not be opened as the image file is missing. Verify the program has permission to make or open new files.");
    }

    //checking error type, type is one of the 2 necesary modules are missing
    else if(proc_stdout.contains("ModuleNotFoundError")) {
        ui->objectNameLabel->setText("Error: Missing Necessary Modules");
        ui->definitionLabel->setText("Missing necessary modules to run python script verify that openAI and request modules have been installed.");
    }

    //checking error type, type is necessary permissions for script to run sucessfully are missing
    else if(proc_stdout.contains("PermissionError")) {
        ui->objectNameLabel->setText("Error: Python Missing Permissions");
        ui->definitionLabel->setText("Python does not have the necessary permissions to open files");
    }

    //checking error type, type is python is not found/installed
    else if(proc_stdout.contains("python") && proc_stdout.contains("not found")) {
        ui->objectNameLabel->setText("Error: Python Not Installed");
        ui->definitionLabel->setText("Please verify that python has been installed correctly and is accessible through command line.");
    }

    //default error message for if there is an unknown error
    else
    {
        ui->objectNameLabel->setText("Error");
        ui->definitionLabel->setText("There was an issue with identifying the object. Please try again! ");
    }

    qDebug(proc_stdout.toLatin1());


    ui->recaptureButton->setText("New Object");
    ui->continueButton->setText("Replay Audio");

    qDebug("error occurred with identification");
}

//Function for setting button. Opens the url box if it is not opened, closes it if it is open already
void MainWindow::on_reloadButton_2_clicked(bool checked)
{
    if(checked) {
        ui->textEdit->raise();
        ui->textEdit->setVisible(true);
        ui->textEdit->setText(url);
        //qDebug("reload button 2 clicked");
    }

    else if(!checked) {
        ui->textEdit->setVisible(false);
        url = ui->textEdit->toPlainText();
        qDebug(url.toLatin1());
    }
}

//changing the voice of the text to speech when the combo box is used
void MainWindow::on_comboBox_2_activated(int index)
{
    QList<QVoice> availableVoices = speech->availableVoices();
    speech->setVoice(availableVoices[index]);
    qDebug(availableVoices[index].name().toLatin1());
}

//Function for when sound button is clicked
void MainWindow::on_reloadButton_3_clicked()
{
    speech->say("Hello");
}

