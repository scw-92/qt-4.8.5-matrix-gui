#include "info.h"
#include "ui_info.h"
#include <QMouseEvent>

Info::Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    myprocess = NULL;
}

Info::~Info()
{
    delete myprocess;
    delete ui;
}

void Info::on_pushButton_cpu_info_clicked()
{
    if(myprocess)
        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start("cat /proc/cpuinfo");
    ui->result->clear();

}
void Info::result()
{
    QString abc = myprocess->readAllStandardOutput();
    ui->result->append(abc.trimmed());
    QString efg = myprocess->readAllStandardError();
    if(efg.length()>1)ui->result->append(efg.trimmed());

}

void Info::on_pushButton_mem_info_clicked()
{
    if(myprocess)
        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start("cat /proc/meminfo");
    ui->result->clear();
}

void Info::on_pushButton_storage_clicked()
{
    if(myprocess)
        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start("df -h");
    ui->result->clear();
}
void Info::mouseMoveEvent ( QMouseEvent  * e )
{
    ui->label->setText("X-->"+QString::number(e->x())+" Y-->"+QString::number(e->y()));
}
