#include "myGpio.h"
#include "ui_myGpio.h"
#include <string.h>


static char Readval(const char *dir)
{
    int fd, retval;
    char val;

    fd = ::open(dir, O_RDONLY);
    if (fd < 0)
    {
        ::perror("open value");
        return '2';
    }

    retval = ::read(fd, &val, 1);
    if (retval < 0)
    {
        ::perror("read value");
        return '2';
    }

    ::close(fd);

    return val;
}


MyGpio::MyGpio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyGpio)
{
    ui->setupUi(this);
    connect(&testTimer, SIGNAL(timeout()), this, SLOT(SotSetTime()));
    testTimer.start(10);

    ::system("echo 44  > /sys/class/gpio/export");
    ::system("echo 45  > /sys/class/gpio/export");
    ::system("echo 46  > /sys/class/gpio/export");
    ::system("echo 47  > /sys/class/gpio/export");
    ::system("echo 110 > /sys/class/gpio/export");
    ::system("echo 111 > /sys/class/gpio/export");
    ::system("echo 112 > /sys/class/gpio/export");
    ::system("echo 113 > /sys/class/gpio/export");

    ::system("echo in > /sys/class/gpio/gpio44/direction");
    ::system("echo in > /sys/class/gpio/gpio45/direction");
    ::system("echo in > /sys/class/gpio/gpio46/direction");
    ::system("echo in > /sys/class/gpio/gpio47/direction");
    ::system("echo out > /sys/class/gpio/gpio110/direction");
    ::system("echo out > /sys/class/gpio/gpio111/direction");
    ::system("echo out > /sys/class/gpio/gpio112/direction");
    ::system("echo out > /sys/class/gpio/gpio113/direction");

}

MyGpio::~MyGpio()
{
    ::system("echo 44  > /sys/class/gpio/unexport");
    ::system("echo 45  > /sys/class/gpio/unexport");
    ::system("echo 46  > /sys/class/gpio/unexport");
    ::system("echo 47  > /sys/class/gpio/unexport");
    ::system("echo 110 > /sys/class/gpio/unexport");
    ::system("echo 111 > /sys/class/gpio/unexport");
    ::system("echo 112 > /sys/class/gpio/unexport");
    ::system("echo 113 > /sys/class/gpio/unexport");

    delete ui;
}


void MyGpio::SotSetTime()
{
    char val;

    val = Readval("/sys/class/gpio/gpio44/value");
    if (val == '1')
        ui->label_I_1->setText("IO_IN_1_H");
    else if (val == '0')
        ui->label_I_1->setText("IO_IN_1_L");
    else
        ui->label_I_1->setText("IO_IN_1_E");

    val = Readval("/sys/class/gpio/gpio45/value");
    if (val == '1')
        ui->label_I_2->setText("IO_IN_2_H");
    else if (val == '0')
        ui->label_I_2->setText("IO_IN_2_L");
    else
        ui->label_I_2->setText("IO_IN_2_E");

    val = Readval("/sys/class/gpio/gpio46/value");
    if (val == '1')
        ui->label_I_3->setText("IO_IN_3_H");
    else if (val == '0')
        ui->label_I_3->setText("IO_IN_3_L");
    else
        ui->label_I_3->setText("IO_IN_3_E");

    val = Readval("/sys/class/gpio/gpio47/value");
    if (val == '1')
        ui->label_I_4->setText("IO_IN_4_H");
    else if (val == '0')
        ui->label_I_4->setText("IO_IN_4_L");
    else
        ui->label_I_4->setText("IO_IN_4_E");
}

void MyGpio::on_pushButton_O_1_clicked()
{
    if ( io_out_1 == 1)
    {
        ::system("echo 1 > /sys/class/gpio/gpio110/value");
        ui->pushButton_O_1->setText("IO_OUT_1_H");
        io_out_1 = 0;
    }
    else
    {
        ::system("echo 0 > /sys/class/gpio/gpio110/value");
        ui->pushButton_O_1->setText("IO_OUT_1_L");
        io_out_1 = 1;
    }
}

void MyGpio::on_pushButton_O_2_clicked()
{
    if ( io_out_2 == 1)
    {
        ::system("echo 1 > /sys/class/gpio/gpio111/value");
        ui->pushButton_O_2->setText("IO_OUT_2_H");
        io_out_2 = 0;
    }
    else
    {
        ::system("echo 0 > /sys/class/gpio/gpio111/value");
        ui->pushButton_O_2->setText("IO_OUT_2_L");
        io_out_2 = 1;
    }
}

void MyGpio::on_pushButton_O_3_clicked()
{
    if ( io_out_3 == 1)
    {
        ::system("echo 1 > /sys/class/gpio/gpio112/value");
        ui->pushButton_O_3->setText("IO_OUT_3_H");
        io_out_3 = 0;
    }
    else
    {
        ::system("echo 0 > /sys/class/gpio/gpio112/value");
        ui->pushButton_O_3->setText("IO_OUT_3_L");
        io_out_3 = 1;
    }
}

void MyGpio::on_pushButton_O_4_clicked()
{
    if ( io_out_4 == 1)
    {
        ::system("echo 1 > /sys/class/gpio/gpio113/value");
        ui->pushButton_O_4->setText("IO_OUT_4_H");
        io_out_4 = 0;
    }
    else
    {
        ::system("echo 0 > /sys/class/gpio/gpio113/value");
        ui->pushButton_O_4->setText("IO_OUT_4_L");
        io_out_4 = 1;
    }
}
