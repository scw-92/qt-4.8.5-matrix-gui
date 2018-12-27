#include "backlight.h"
#include "ui_backlight.h"
#include <fcntl.h>
#include <stdio.h>
//#include <qpushbutton.h>
#include <sys/types.h>
#include <unistd.h>
#include <QDebug>
Backlight::Backlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backlight)
{
    ui->setupUi(this);

    char buf[10] = {0};

    bl_fd = ::open("/sys/class/backlight/backlight/brightness", O_RDWR|O_NONBLOCK);
    if(bl_fd < 0)
    {
        perror("open brightness error");
    }

    ::read(bl_fd, buf, sizeof(buf));
    ::lseek(bl_fd, 0, SEEK_SET);

    ui->slider->setValue((new QString(buf))->toInt());
}

Backlight::~Backlight( )
{
    ::close(bl_fd);
    delete ui;
}

void Backlight::moveEvent(QMoveEvent *)
{   
    this->move(QPoint(0,0));
}

void Backlight::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Backlight::on_slider_valueChanged(int value)
{
    char buf[20] = {0};
    sprintf(buf, "%d", value);
    ::write(bl_fd, buf, sizeof(buf));
}
