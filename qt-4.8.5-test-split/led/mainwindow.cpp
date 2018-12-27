#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define IO_VAULE_H          55
#define IO_VAULE_L          56

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    static int flag = 0;
    char tmp = '1';
    int fd;
    fd = open("/dev/debug_led",O_RDWR);
    if (flag == 0)
    {
        tmp = IO_VAULE_H;
        ioctl(fd,tmp,1);
        ui->pushButton->setText("LED_ON");
        flag = 1;
    }
    else
    {
        tmp = IO_VAULE_L;
        ioctl(fd,tmp,1);
        ui->pushButton->setText("LED_OFF");
        flag = 0;
    }
    ::close(fd);
}
