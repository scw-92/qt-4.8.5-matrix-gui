#ifndef CANTEST_H
#define CANTEST_H

#include <QWidget>
#include <QProcess>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include "thread.h"
#include <QButtonGroup>

namespace Ui {
class CanTest;
}

class CanTest : public QWidget
{
    Q_OBJECT
    
public:
    explicit CanTest(QWidget *parent = 0);
    ~CanTest();
protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
private slots:
    void on_send_clicked();
    void msg(QString str);
    void stopcan(int v);
    void startcan(int v);
    void on_start_clicked();

private:
    Ui::CanTest *ui;
    int socket;
    struct sockaddr_can addr;
    Thread *t;
    QButtonGroup* btg;
    int canNumber;
    QString baudrate;
};

#endif // MAINWINDOW_H
