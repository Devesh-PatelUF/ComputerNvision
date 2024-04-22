QT += testlib
QT += gui
QT       += core texttospeech
QT    += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_mainwindowtest.cpp ../Senior_Project/mainwindow.cpp

HEADERS += ../Senior_Project/mainwindow.h

FORMS += ../Senior_Project/mainwindow.ui
