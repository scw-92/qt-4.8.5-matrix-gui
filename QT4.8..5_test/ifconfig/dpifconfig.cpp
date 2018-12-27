#include "dpifconfig.h"
#include "ui_dpifconfig.h"

dpifconfig::dpifconfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dpifconfig)
{
    ui->setupUi(this);
}

dpifconfig::~dpifconfig()
{
    delete ui;
}

void dpifconfig::on_pushButton_ifconfig_clicked()
{
    char aplex_commond[512] = " ifconfig -a ";

    ui->textBrowser_ifconfig->clear();
    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start(aplex_commond);
}
void dpifconfig::result()
{
    QString aplex_ip =  myprocess->readAllStandardOutput();
    ui->textBrowser_ifconfig->setText(aplex_ip);

    QString aplex_err = myprocess->readAllStandardError();
    if(aplex_err.length() > 1)
    {
       ui->textBrowser_ifconfig->setText(aplex_err);
    }
}

void dpifconfig::on_pushButton_testip_clicked()
{
    ui->textBrowser_ifconfig->clear();
    //::system("ifconfig eth0 192.168.12.11");
}
