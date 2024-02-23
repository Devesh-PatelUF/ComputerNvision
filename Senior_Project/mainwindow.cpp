#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette pal = ui->ImagePlaceholder->palette();

    // set black background
    pal.setColor(QPalette::Window, Qt::white);
    ui->ImagePlaceholder->setAutoFillBackground(true);
    ui->ImagePlaceholder->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}
