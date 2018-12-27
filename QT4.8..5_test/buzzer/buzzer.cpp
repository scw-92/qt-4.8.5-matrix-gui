#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "buzzer.h"
#include "ui_buzzer.h"
#include <QMessageBox>
#include <QFile>
#include <stdlib.h>


#define PWM_IOCTL_SET_FREQ	1
#define PWM_IOCTL_STOP		0

Buzzer::Buzzer(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::Buzzer)
{
    ui->setupUi(this);
    system(" echo 0 > /sys/class/pwm/pwmchip1/export");
}

Buzzer::~Buzzer()
{
    system("echo 0 > /sys/class/pwm/pwmchip1/pwm0/enable");
    system(" echo 0 > /sys/class/pwm/pwmchip1/unexport");
    delete ui;
}

/* set duty_cycle  */
void Buzzer::set_buzzer_freq(int freq)
{
    int duty_fd, retval;

    system("echo 200000 >  /sys/class/pwm/pwmchip1/pwm0/period ");

    QString chen_val = QString::number(freq, 10);
    QByteArray ba = chen_val.toLatin1();
    char *val = ba.data();

    duty_fd = open("/sys/class/pwm/pwmchip1/pwm0/duty_cycle", O_WRONLY);
    if(duty_fd < 0)
    {
        perror("duty_fd");
        exit(0);
    }
    retval = ::write(duty_fd, (const char *)val, sizeof(val));
    if(retval < 0)
    {
        perror("write duty");
    }
    ::close(duty_fd);
}

void Buzzer::on_slider_valueChanged(int value)
{
    QString nextState = ui->pushButton->text();
    if (nextState == "STOP") {
        set_buzzer_freq(value);
    }
    ui->spinBox->setValue(value);
}

void Buzzer::on_spinBox_valueChanged(int value)
{
    QString state = ui->pushButton->text();
    if (state == "STOP") {
        set_buzzer_freq(value);
    }
    ui->slider->setValue(value);
}

void Buzzer::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Buzzer::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Buzzer::on_pushButton_clicked()
{
    int freq;
    QString state = ui->pushButton->text();
    if (state == "START") {
        ui->pushButton->setText("STOP");
        system("echo 1 >  /sys/class/pwm/pwmchip1/pwm0/enable ");
        freq = ui->slider->value();
        set_buzzer_freq(freq);
    } else if (state == "STOP") {
        ui->pushButton->setText("START");
        system("echo 0 >  /sys/class/pwm/pwmchip1/pwm0/enable ");
    }
}
