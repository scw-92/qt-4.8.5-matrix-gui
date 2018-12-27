#include "version.h"
#include "ui_version.h"
#include "../network/interface.h"


version::version(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::version)
{
    QString ver = "\n\n\nversion 1.0";
    QString info = "This application contains :\n\
            information, gpio, buzzer, backlight, eeprom,\n\
            network, ping, rtc, usb, SD, uart, can.\n\n\
            Date:  November 2, 2016\nCompany:  Aplex";

    ui->setupUi(this);
    //ui->label_ver->setText(ver);
    ui->label_logo->setPixmap(QPixmap("/usr/share/web/lighttpd/webpages/apps/images/aplex_logo.png"));
    //ui->label_info->setText(info);

    ui->textBrowser->viewport()->setAutoFillBackground(false);
    ui->textBrowser->setFrameStyle(QFrame::NoFrame);
}

version::~version()
{
    delete ui;
}
