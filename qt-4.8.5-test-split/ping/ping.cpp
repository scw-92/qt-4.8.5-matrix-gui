#include "ping.h"
#include "ui_ping.h"
#include <QMessageBox>

Ping::Ping(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ping)
{
    ui->setupUi(this);
    ui->hostname->setText("www.linux.org");
    myprocess = NULL;
}

Ping::~Ping()
{
    delete myprocess;
    delete ui;
}

void Ping::on_ping_clicked()
{
    if(ui->hostname->text() == QString(""))
    {
        QMessageBox::about(this,"error","hostname cannot be empty!");
        return;
    }

    if(myprocess)
        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start(QString("ping ")+ui->hostname->text());
    ui->result->append(QString("ping ")+ui->hostname->text());
    //myprocess->waitForFinished();
}

void Ping::result()
{
    QString abc = myprocess->readAllStandardOutput();
    ui->result->append(abc.trimmed());
    QString efg = myprocess->readAllStandardError();
    if(efg.length()>1)ui->result->append(efg.trimmed());
}

void Ping::on_stop_clicked()
{
    delete myprocess;
    myprocess = NULL;
}

void Ping::on_clear_clicked()
{
    ui->result->clear();
}

void Ping::closeEvent(QCloseEvent *)
{
    exit(0);
}

void Ping::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Ping::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}


