#include "mainwindow.h"
#include <QApplication>
#include <QThread>

Parser myParser;

class MyFirstThread : public QThread
{
private:
    void run()
    {
        myParser.runParser();
    }
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MyFirstThread t1;
    t1.start();

    QObject::connect(&myParser, SIGNAL(parserSignal(int)), &w, SLOT(usageSlot(int)));


    return a.exec();
}
