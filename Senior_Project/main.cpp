#include "mainwindow.h"

#include <QPalette>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    w.setPalette(pal);




    w.show();
    return a.exec();
}
