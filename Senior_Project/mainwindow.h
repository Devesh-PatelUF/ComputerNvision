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
    Ui::MainWindow* getUi(); //TESTING ONLY FUNCTION. NEED FOR TESTING PROJECT. DO NOT USE OTHERWISE
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;


private slots:
    void on_captureButton_clicked();

    void on_recaptureButton_clicked(bool checked);

    void on_continueButton_clicked(bool checked);

    void onProcessComplete();


    void onProcessError_();

    void on_comboBox_activated(int index);

    void on_reloadButton_clicked();

    void on_reloadButton_2_clicked(bool checked);

    void on_comboBox_2_activated(int index);

    void on_reloadButton_3_clicked();

private:
    Ui::MainWindow* ui;
    QWebEngineView* view;
    QProcess process;
    int loadingVal;

    void updateLoading();
    void delay(double time);

    QString mode;
    QString url;
};
#endif // MAINWINDOW_H
