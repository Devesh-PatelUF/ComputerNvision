/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *captureButton;
    QPushButton *recaptureButton;
    QPushButton *continueButton;
    QLabel *objectNameLabel;
    QLabel *definitionLabel;
    QLabel *imageLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 900);
        MainWindow->setMinimumSize(QSize(1280, 900));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #f3957c\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        captureButton = new QPushButton(centralwidget);
        captureButton->setObjectName("captureButton");
        captureButton->setEnabled(true);
        captureButton->setGeometry(QRect(410, 730, 446, 115));
        captureButton->setMinimumSize(QSize(0, 115));
        QFont font;
        font.setPointSize(28);
        captureButton->setFont(font);
        captureButton->setStyleSheet(QString::fromUtf8("QPushBuuton{\n"
"	border: 1px solid;\n"
"	border-radius: 57px;\n"
"	border-color: blue;\n"
"}\n"
"\n"
"QPushButton:enabled {\n"
"	border-radius: 57px;\n"
"	background-color: #0021A5;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #6b87f1;\n"
"	color: #fffffe;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: #E1f4FF;\n"
"	color: #0c2f70\n"
"}"));
        recaptureButton = new QPushButton(centralwidget);
        recaptureButton->setObjectName("recaptureButton");
        recaptureButton->setGeometry(QRect(110, 730, 446, 115));
        recaptureButton->setFont(font);
        recaptureButton->setStyleSheet(QString::fromUtf8("QPushBuuton{\n"
"	border: 1px solid;\n"
"	border-radius: 50px;\n"
"	border-color: blue;\n"
"}\n"
"\n"
"QPushButton:enabled {\n"
"	border-radius: 57px;\n"
"	background-color: #0021A5;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #6b87f1;\n"
"	color: #fffffe;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: #E1f4FF;\n"
"	color: #0c2f70\n"
"}"));
        continueButton = new QPushButton(centralwidget);
        continueButton->setObjectName("continueButton");
        continueButton->setEnabled(true);
        continueButton->setGeometry(QRect(710, 730, 446, 115));
        continueButton->setFont(font);
        continueButton->setStyleSheet(QString::fromUtf8("QPushBuuton{\n"
"	border: 1px solid;\n"
"	border-radius: 50px;\n"
"	border-color: blue;\n"
"}\n"
"\n"
"QPushButton:enabled {\n"
"	border-radius: 57px;\n"
"	background-color: #0021A5;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #6b87f1;\n"
"	color: #fffffe;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: #E1f4FF;\n"
"	color: #0c2f70\n"
"}"));
        objectNameLabel = new QLabel(centralwidget);
        objectNameLabel->setObjectName("objectNameLabel");
        objectNameLabel->setGeometry(QRect(470, 0, 361, 51));
        objectNameLabel->setFont(font);
        definitionLabel = new QLabel(centralwidget);
        definitionLabel->setObjectName("definitionLabel");
        definitionLabel->setGeometry(QRect(210, 60, 801, 111));
        QFont font1;
        font1.setPointSize(16);
        definitionLabel->setFont(font1);
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setGeometry(QRect(210, 90, 800, 600));
        imageLabel->setFrameShape(QFrame::Box);
        imageLabel->setLineWidth(2);
        MainWindow->setCentralWidget(centralwidget);
        recaptureButton->raise();
        continueButton->raise();
        objectNameLabel->raise();
        definitionLabel->raise();
        imageLabel->raise();
        captureButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        captureButton->setText(QCoreApplication::translate("MainWindow", "Capture", nullptr));
        recaptureButton->setText(QCoreApplication::translate("MainWindow", "Recapture", nullptr));
        continueButton->setText(QCoreApplication::translate("MainWindow", "Continue", nullptr));
        objectNameLabel->setText(QCoreApplication::translate("MainWindow", "Object Identifier", nullptr));
        definitionLabel->setText(QCoreApplication::translate("MainWindow", "Definition", nullptr));
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
