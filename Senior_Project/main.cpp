#include "mainwindow.h"

#include <QPalette>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w = new MainWindow(nullptr, a.applicationDirPath());
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::darkBlue);
    w.setPalette(pal);




    w.show();
    return a.exec();
}
