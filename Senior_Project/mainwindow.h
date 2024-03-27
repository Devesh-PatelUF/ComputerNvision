#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>
#include <QWebEngineView>
#include <QTextToSpeech>
#include <QMouseEvent>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow* getUi();
    ~MainWindow();



private slots:
    void on_captureButton_clicked();

    void on_recaptureButton_clicked(bool checked);

    void on_continueButton_clicked(bool checked);

    void onProcessComplete();

private:
    Ui::MainWindow* ui;
    QWebEngineView* view;
    QProcess process;
    int loadingVal;

    void updateLoading();
    void delay(double time);
};
#endif // MAINWINDOW_H
