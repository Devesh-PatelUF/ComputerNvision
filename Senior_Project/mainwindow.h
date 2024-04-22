#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myudp.h"

#include <QMainWindow>
#include <QTextToSpeech>
#include <QGraphicsScene>
#include <QTimer>




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

private:
    Ui::MainWindow* ui;
    QGraphicsView* view;
    MyUDP* my_udp;
    QTimer* time;

};
#endif // MAINWINDOW_H
