#include "sd.h"
#include "ui_sd.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QTreeView>
#include <QDir>
#include <QDebug>

#define SDDETECT  		56

Sd::Sd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sd)
{
    ui->setupUi(this);

    ui->showDir->setModel(&model);

    model.setRootPath("/media/mmcblk1p1");
    ui->showDir->setRootIndex(model.index("/media/mmcblk1p1"));
    // Demonstrating look and feel features
    ui->showDir->setAnimated(false);
    ui->showDir->setIndentation(20);
    ui->showDir->setSortingEnabled(true);
    ui->showDir->setColumnWidth(0, 250);
}

Sd::~Sd()
{
    ::system("umount  /media/mmcblk1p1");
    delete ui;
}
void Sd::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Sd::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Sd::closeEvent(QCloseEvent *)
{
    exit(0);
}

void Sd::on_detectButton_clicked()
{
    /**
     * simulate the hardware detect for sd
     */
    //int fd = open("/dev/sdDetect", O_RDWR);
    //ioctl(fd, SDDETECT, 1);
    //::close(fd);

    //sleep(6);
    ::system("umount /media/mmcblk1p1");

    QFileInfo fileInfo("/dev/mmcblk1p1");
    if( fileInfo.exists() ) {

        while(!QFileInfo("/media/mmcblk1p1").exists()) {
            ::system("mkdir /media/mmcblk1p1");
            qDebug() << "/dev/mmcblk1p1 exists" << endl;
        }

        ::system("mount /dev/mmcblk1p1 /media/mmcblk1p1");
        model.setRootPath("/media");
        model.setRootPath("/media/mmcblk1p1");
        ui->showDir->setRootIndex(model.index("/media/mmcblk1p1"));
        qDebug() << "/dev/mmcblk1p1 exists" << endl;
    } else {

        sleep(4);
        while(!QFileInfo("/media/mmcblk1p1").exists()) {
            ::system("mkdir /media/mmcblk1p1");
            qDebug() << "/dev/mmcblk1p1 not exists" << endl;
        }

        model.setRootPath("/media");
        model.setRootPath("/media/mmcblk1p1");
        ui->showDir->setRootIndex(model.index("/media/mmcblk1p1"));
        QMessageBox::warning(this, "WARNING", "Please check your SD card has plugin slot.");
        qDebug() << "/dev/mmcblk1p1 not exists" << endl;
    }
}

void Sd::on_umountButton_clicked()
{
    ::system("umount /media/mmcblk1p1");
}
