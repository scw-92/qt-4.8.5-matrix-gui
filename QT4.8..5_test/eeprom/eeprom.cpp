#include "eeprom.h"
#include "ui_eeprom.h"
#include <QDebug>
#include <stdio.h>
#include <fcntl.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFrame>
#include <QtCore>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <unistd.h>


#define BUFSIZE  32768
#define FILENAME "/dev/eeprom"

Eeprom::Eeprom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eeprom)
{
    ui->setupUi(this);

    connect(ui->wbutton, SIGNAL(clicked()),this, SLOT(writemsg()));
    connect(ui->rbutton, SIGNAL(clicked()),this, SLOT(readmsg()));

    fd = open("/sys/devices/platform/ocp/44e0b000.i2c/i2c-0/0-0050/eeprom", O_RDWR | O_APPEND);
	if (fd < 0) {
		perror("open eeprom device:");
		exit(1);
	}
}

Eeprom::~Eeprom()
{
    ::close(fd);
    delete ui;
}

void Eeprom::writemsg()
{
	int ret;
	QString wbuf =ui->wframe->toPlainText(); 
	wbuf = ui->wframe->toPlainText(); 
	len = wbuf.length();
	QByteArray ba = wbuf.toLatin1();
	char *str =ba.data();

	if(wbuf.length() < BUFSIZE){
		if ((ret = lseek(fd, 6, SEEK_SET)) < 0) {
            QMessageBox::about(this,"error","lseek error");
			return;
		}
		if ((ret = write(fd, str, len)) < 0) {
            QMessageBox::about(this,"error","write error");
			return;
		}				
	}

    QMessageBox::about(this,"ok","write success");
}

void Eeprom::readmsg()
{
	int ret;	
	char rbuf[BUFSIZE] = "";
	if(len < BUFSIZE){
		if ((ret = lseek(fd, 6, SEEK_SET)) < 0) {
            QMessageBox::about(this,"error","lseek error");
			return;
		}
		if((ret = read(fd, rbuf, len)) < 0) {
            QMessageBox::about(this,"error","read error");
			return;
		}
		ui->label->setText(rbuf);
	}
}

void Eeprom::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Eeprom::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Eeprom::closeEvent(QCloseEvent *)
{
    exit(0);
}
