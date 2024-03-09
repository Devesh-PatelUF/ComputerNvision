#include <QtTest>
#include "../Senior_Project/mainwindow.h"

class mainWindowTest : public QObject
{
    Q_OBJECT

public:
    mainWindowTest();
    ~mainWindowTest();

private slots:
    void test_case1();
};

mainWindowTest::mainWindowTest() {}

mainWindowTest::~mainWindowTest() {}

void mainWindowTest::test_case1() {}

QTEST_APPLESS_MAIN(mainWindowTest)

#include "tst_mainwindowtest.moc"
