#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QApplication>

#include <QTextCodec>
#include "./inputpanel/myinputpanel.h"
#include "./inputpanel/myinputpanelcontext.h"
#include "./burncpu/parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyInputPanelContext *ic = new MyInputPanelContext;
    a.setInputContext(ic);//将输入上下文与应用程序关联

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    MainWindow w;

    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    w.showMaximized();

    return a.exec();
}
