#include <QtTest>
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



    //testing size, position
    void test_capture_button_properties();
    void test_recapture_button_properties();
    void test_continue_button_properties();


    //testing all behavior when a button is clicked. i.e. does it change size of other stuff, does it hide other stuff, does it change text
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
    QVERIFY(ui->captureButton->x() == 410);
    QVERIFY(ui->captureButton->y() == 730);
}
void mainWindowTest::test_recapture_button_properties() \
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->recaptureButton->height() == 115);
    QVERIFY(ui->recaptureButton->width() == 446);
    QVERIFY(ui->recaptureButton->x() == 110);
    QVERIFY(ui->recaptureButton->y() == 730);
}
void mainWindowTest::test_continue_button_properties()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QVERIFY(ui->continueButton->height() == 115);
    QVERIFY(ui->continueButton->width() == 446);
    QVERIFY(ui->continueButton->x() == 710);
    QVERIFY(ui->continueButton->y() == 730);
}


void mainWindowTest::test_capture_button_click()
{
    Ui::MainWindow* ui = mainWindow->getUi();
    QTest::mouseClick(ui->captureButton, Qt::LeftButton);


    QVERIFY(ui->objectNameLabel->isVisible());
    QVERIFY(ui->recaptureButton->isVisible());
    QVERIFY(ui->continueButton->isVisible());
    QVERIFY(!(ui->captureButton->isVisible()));
    QVERIFY(ui->objectNameLabel->text().compare("Is this picture correct?")==0);




}
void mainWindowTest::test_recapture_button_click() {}
void mainWindowTest::test_continue_button_click() {}
void mainWindowTest::test_newObject_button_click() {}
void mainWindowTest::test_replayAudio_button_click() {}

QTEST_MAIN(mainWindowTest)

#include "tst_mainwindowtest.moc"
