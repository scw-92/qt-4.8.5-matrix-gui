#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "led.h"
#include "ui_led.h"

#define IO_VAULE_H          55
#define IO_VAULE_L          56

Led::Led(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Led)
{
    ui->setupUi(this);
    system("echo 29  > /sys/class/gpio/export");
    system("echo out > /sys/class/gpio/gpio29/direction ");
}

Led::~Led()
{
    system("echo 29  > /sys/class/gpio/unexport");
    delete ui;
}

void Led::on_pushButton_clicked()
{
    static int flag = 0;
    if (flag == 0)
    {
        system("echo 1 > /sys/class/gpio/gpio29/value");
        ui->pushButton->setText("LED_ON");
        flag = 1;
    }
    else
    {
        system("echo 0 > /sys/class/gpio/gpio29/value");
        ui->pushButton->setText("LED_OFF");
        flag = 0;
    }
}
