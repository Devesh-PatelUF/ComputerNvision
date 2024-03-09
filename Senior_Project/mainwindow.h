#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>

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
};
#endif // MAINWINDOW_H
