#include "usb.h"
#include "ui_usb.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QTreeView>
#include <QDir>
#include <QDebug>


Usb::Usb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usb)
{
    ui->setupUi(this);

    ui->show_dir->setModel(&model);

    model.setRootPath("/media/sda1");
    ui->show_dir->setRootIndex(model.index("/media/sda1"));
    // Demonstrating look and feel features
    ui->show_dir->setAnimated(false);
    ui->show_dir->setIndentation(20);
    ui->show_dir->setSortingEnabled(true);
    ui->show_dir->setColumnWidth(0, 250);
}

Usb::~Usb()
{
    ::system("umount /dev/sda1");
    ::system("sync");
    delete ui;

}

void Usb::on_button_mount_clicked()
{
    ::system("umount /media/sda1");

    QFileInfo fileInfo("/dev/sda1");
    if( fileInfo.exists() ) {

        while(!QFileInfo("/media/sda1").exists()) {
            ::system("mkdir /media/sda1");
            qDebug() << "/dev/sda1 exists" << endl;
        }

        ::system("mount /dev/sda1 /media/sda1");
        model.setRootPath("/media");
        model.setRootPath("/media/sda1");
        ui->show_dir->setRootIndex(model.index("/media/sda1"));
        qDebug() << "/dev/sda1 exists" << endl;
    } else {

        sleep(2);
        while(!QFileInfo("/media/sda1").exists()) {
            ::system("mkdir /media/sda1");
            qDebug() << "/dev/sda1 not exists" << endl;
        }

        model.setRootPath("/media/sda1");
        ui->show_dir->setRootIndex(model.index("/media/sda1"));
        QMessageBox::warning(this, "WARNING", "Please check your SD card has plugin slot.");
        qDebug() << "/dev/sda1 not exists" << endl;
    }
}

void Usb::on_button_umount_clicked()
{
    ::system("umount /media/sda1");
}
