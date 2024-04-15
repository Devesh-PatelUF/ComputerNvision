#include <QtTest>
#include <QTextStream>
#include "../Senior_Project/mainwindow.h"
#include "ui_mainwindow.h"

class mainWindowTest : public QObject
{
    Q_OBJECT

public:
    mainWindowTest();
    ~mainWindowTest();
private:
    MainWindow* mainWindow;

private slots:
    void test_window_open();
    void test_window_size();



    //testing sizes of the UI Elements
    void test_capture_button_properties();
    void test_recapture_button_properties();
    void test_continue_button_properties();
    void test_combo_box_properties();
    void test_combo_box2_properties();
    void test_reloadButton_properties();
    void test_reloadButton2_properties();
    void test_reloadButton3_properties();
    void test_loadingText_properties();
    void test_loadingWindow_properties();
    void test_textEdit_properties();
    void test_objectNameLabel_properties();
    void test_progressBar_properties();
    void test_imageLabel_properties();
    void test_defintionLabel_properties();



    //testing behavior when a button is clicked to see if the correct UI Elements are present
    void test_capture_button_click();
    void test_recapture_button_click();
    void test_continue_button_click();
    void test_newObject_button_click();
    void test_replayAudio_button_click();
};

mainWindowTest::mainWindowTest()
{
    mainWindow = new MainWindow;
    mainWindow->show();
}

mainWindowTest::~mainWindowTest() {
    delete mainWindow;
}

void mainWindowTest::test_window_open()
{
    QVERIFY(mainWindow->isVisible());
    QVERIFY(mainWindow->isEnabled());
}
void mainWindowTest::test_window_size()
{

    QVERIFY(mainWindow->height() == 900);
    QVERIFY(mainWindow->width() == 1280);
}
void mainWindowTest::test_capture_button_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->captureButton->height() == 115);
    QVERIFY(ui->captureButton->width() == 446);
}
void mainWindowTest::test_recapture_button_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->recaptureButton->height() == 115);
    QVERIFY(ui->recaptureButton->width() == 446);
}
void mainWindowTest::test_continue_button_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->continueButton->height() == 115);
    QVERIFY(ui->continueButton->width() == 446);
}

void mainWindowTest::test_combo_box_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->comboBox->height() == 41);
    QVERIFY(ui->comboBox->width() == 161);
}

void mainWindowTest::test_combo_box2_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->comboBox_2->height() == 41);
    QVERIFY(ui->comboBox_2->width() == 231);
}

void mainWindowTest::test_reloadButton_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->reloadButton->height() == 51);
    QVERIFY(ui->reloadButton->width() == 51);
}

void mainWindowTest::test_reloadButton2_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->reloadButton_2->height() == 51);
    QVERIFY(ui->reloadButton_2->width() == 51);
}

void mainWindowTest::test_reloadButton3_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->reloadButton_3->height() == 50);
    QVERIFY(ui->reloadButton_3->width() == 51);
}

void mainWindowTest::test_loadingText_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->loadingText->height() == 51);
    QVERIFY(ui->loadingText->width() == 341);
}

void mainWindowTest::test_loadingWindow_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->loadingWindow->height() == 121);
    QVERIFY(ui->loadingWindow->width() == 361);
}

void mainWindowTest::test_textEdit_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->textEdit->height() == 51);
    QVERIFY(ui->textEdit->width() == 361);
}

void mainWindowTest::test_objectNameLabel_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->objectNameLabel->height() == 51);
    QVERIFY(ui->objectNameLabel->width() == 821);
}

void mainWindowTest::test_progressBar_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->progressBar->height() == 31);
    QVERIFY(ui->progressBar->width() == 361);
}

void mainWindowTest::test_imageLabel_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->imageLabel->height() == 600);
    QVERIFY(ui->imageLabel->width() == 800);
}

void mainWindowTest::test_defintionLabel_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->definitionLabel->height() == 111);
    QVERIFY(ui->definitionLabel->width() == 801);
}


void mainWindowTest::test_capture_button_click()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->captureButton, Qt::LeftButton);

    QVERIFY(ui->imageLabel->isVisible());
    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->recaptureButton->isVisible());
    QVERIFY(ui->continueButton->isVisible());
    QVERIFY(!(ui->captureButton->isVisible()));
    QVERIFY(ui->comboBox->isVisible());
    QVERIFY(ui->comboBox_2->isVisible());
    QVERIFY(ui->reloadButton_3->isVisible());
    QVERIFY(!(ui->reloadButton->isVisible()));
    QVERIFY(!(ui->reloadButton_2->isVisible()));
    QVERIFY(ui->objectNameLabel->text().compare("Is this picture correct?")==0);


}


void mainWindowTest::test_recapture_button_click() {
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->captureButton, Qt::LeftButton);
    QTest::mouseClick(ui->recaptureButton, Qt::LeftButton);
    QVERIFY(ui->imageLabel->isVisible());
    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->captureButton->isVisible());
    QVERIFY(ui->comboBox->isVisible());
    QVERIFY(ui->comboBox_2->isVisible());
    QVERIFY(ui->reloadButton->isVisible());
    QVERIFY(ui->reloadButton_2->isVisible());
    QVERIFY(ui->reloadButton_3->isVisible());
    QVERIFY(ui->objectNameLabel->text().compare("Object Identifier")==0);
}

void mainWindowTest::test_continue_button_click() {
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->captureButton, Qt::LeftButton);
    QTest::mouseClick(ui->continueButton, Qt::LeftButton);
    QVERIFY(ui->imageLabel->isVisible());
    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->definitionLabel->isVisible());
    QVERIFY(ui->recaptureButton->isVisible());
    QVERIFY(ui->continueButton->isVisible());
    QVERIFY(!(ui->comboBox->isVisible()));
    QVERIFY(ui->comboBox_2->isVisible());
    QVERIFY(ui->reloadButton_3->isVisible());
    QVERIFY(!(ui->reloadButton->isVisible()));
    QVERIFY(!(ui->reloadButton_2->isVisible()));

}
void mainWindowTest::test_newObject_button_click() {
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->continueButton, Qt::LeftButton);
    QTest::mouseClick(ui->recaptureButton, Qt::LeftButton);
    QVERIFY(ui->imageLabel->isVisible());
    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->captureButton->isVisible());
    QVERIFY(ui->captureButton->isVisible());
    QVERIFY(ui->comboBox->isVisible());
    QVERIFY(ui->comboBox_2->isVisible());
    QVERIFY(ui->reloadButton->isVisible());
    QVERIFY(ui->reloadButton_2->isVisible());
    QVERIFY(ui->reloadButton_3->isVisible());
    QVERIFY(ui->objectNameLabel->text().compare("Object Identifier")==0);
}
void mainWindowTest::test_replayAudio_button_click() {
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->captureButton, Qt::LeftButton);
    QTest::mouseClick(ui->continueButton, Qt::LeftButton);
    QVERIFY(ui->imageLabel->isVisible());
    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->definitionLabel->isVisible());
    QVERIFY(ui->recaptureButton->isVisible());
    QVERIFY(ui->continueButton->isVisible());
    QVERIFY(!(ui->comboBox->isVisible()));
    QVERIFY(ui->comboBox_2->isVisible());
    QVERIFY(ui->reloadButton_3->isVisible());
    QVERIFY(!(ui->reloadButton->isVisible()));
    QVERIFY(!(ui->reloadButton_2->isVisible()));
}

QTEST_MAIN(mainWindowTest)

#include "tst_mainwindowtest.moc"
