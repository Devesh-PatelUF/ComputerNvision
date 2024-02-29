#include "mainwindow.h"

#include <QPalette>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w = new MainWindow(nullptr);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    w.setPalette(pal);




    w.show();
    return a.exec();
}
