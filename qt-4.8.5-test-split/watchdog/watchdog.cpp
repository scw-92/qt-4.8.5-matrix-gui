#include "watchdog.h"
#include "ui_watchdog.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
#include <QMessageBox>

Watchdog::Watchdog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Watchdog)
{
    ui->setupUi(this);

    fd = 0;
    times = 0;
}

Watchdog::~Watchdog()
{
    ::close(fd);
    delete ui;
}

void Watchdog::timerEvent(QTimerEvent *)
{
    int dummy;
    QString str;

    times++;

    if(ui->checkBox->isChecked())
        ::ioctl(fd,WDIOC_KEEPALIVE,&dummy);

    ui->times->setText(str.sprintf("%d",times));
}

void Watchdog::on_pushButton_clicked()
{
    if(ui->pushButton->text() == QString("open watchdog"))
    {
        ui->pushButton->setText("close watchdog");
        ui->checkBox->setDisabled(true);

        fd = ::open("/dev/watchdog",O_WRONLY);
        if(fd < 0)
        {
            QMessageBox::about(this,"error","open watchdog failure");
            exit(-1);
        }

        times = 0;
        ui->times->setText("0");
        timer.start(1000,this);
    }
    else
    {
        ui->pushButton->setText("open watchdog");
        ui->checkBox->setEnabled(true);
        timer.stop();
        ::close(fd);
    }
}

void Watchdog::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Watchdog::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Watchdog::closeEvent(QCloseEvent *)
{
    exit(0);
}

