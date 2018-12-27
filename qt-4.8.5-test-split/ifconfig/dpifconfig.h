#ifndef DPIFCONFIG_H
#define DPIFCONFIG_H

#include <QWidget>
#include <QWidget>
#include <QProcess>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QString>

namespace Ui {
class dpifconfig;
}

class dpifconfig : public QWidget
{
    Q_OBJECT

public:
    explicit dpifconfig(QWidget *parent = 0);
    ~dpifconfig();

private slots:
    void on_pushButton_ifconfig_clicked();
    void result();

    void on_pushButton_testip_clicked();

private:
    Ui::dpifconfig *ui;
    QProcess *myprocess;
};

#endif // DPIFCONFIG_H
