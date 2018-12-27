#include "burnCpu.h"
#include "ui_burnCpu.h"
#include <QDebug>
#include <QTimer>
/*
Parser *myParser;
class MyFirstThread : public QThread
{
private:
    void run()
    {
        QTimer *testTimer = new QTimer(this);
        //将定时器超时信号与槽(功能函数)联系起来
        connect( testTimer,SIGNAL(timeout()), myParser, SLOT(runParser()) );
        //开始运行定时器，定时时间间隔为1000ms
        testTimer->start(1000);
//          myParser->runParser();
    }
};
*/
//MyFirstThread *thread;

BurnCpu::BurnCpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BurnCpu)
{
    ui->setupUi(this);
    runFlag = false;
//    myParser = new Parser();

//    MyFirstThread *thread = new MyFirstThread();
//    thread->start();

//    QObject::connect(myParser, SIGNAL(parserSignal(int)), this, SLOT(usageSlot(int)));
//    connect(myParser, SIGNAL(parserSignal(int)), this, SLOT(usageSlot(int)));
}

BurnCpu::~BurnCpu()
{
//    delete myParser;
    delete ui;
}

void BurnCpu::usageSlot(int iUsage)
{
    QString usageString = QString::number(iUsage);
    usageString += "%";
    ui->label->setText(usageString);
}

void BurnCpu::on_pushButton_clicked()
{

    QString state = ui->pushButton->text();
    if (state == "START") {
        ui->pushButton->setText("STOP");
        runFlag = true;
        heatMachineThead = new HeatMachineThread();
        connect(this, SIGNAL(controlState(bool)), heatMachineThead, SLOT(changeState(bool)));
        qDebug() << "start";
        heatMachineThead->runState = true;
//        emit controlState(true);
        heatMachineThead->start();
    } else if (state == "STOP") {
        ui->pushButton->setText("START");
        runFlag = false;
        heatMachineThead->quit();
        heatMachineThead->runState = false;
//        emit controlState(false);
//        if ((heatMachineThead->quit()) == 0)
//            qDebug() << "close thread fail";
//        heatMachineThead->terminate();
//        heatMachineThead->wait();
        qDebug() << "destory";
//        delete heatMachineThead;
    }
}
