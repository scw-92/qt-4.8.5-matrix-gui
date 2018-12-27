#ifndef BURNCPU_H
#define BURNCPU_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QPushButton>
#include <QThread>
#include <QTime>
#include "parser.h"

namespace Ui {
class BurnCpu;
}

//bool runFlag = true;
class HeatMachineThread : public QThread
{
    Q_OBJECT
public:
    bool runState;
private:
    void run()
    {
        qDebug() << "enter while -----";
        while ( runState ) {
            if (runState == false)
                qDebug() << "state is false -----";
        }
        qDebug() << "leave while ----";
    }
public slots:
    void changeState(bool state) {
        runState = state;
        qDebug() << "get state ------";
        qDebug() << runState;
    }
};

class BurnCpu : public QWidget
{
    Q_OBJECT

public:
    bool runFlag;
    explicit BurnCpu(QWidget *parent = 0);
    ~BurnCpu();

private:
    HeatMachineThread *heatMachineThead;

signals:
    void controlState(bool);

public slots:
    void usageSlot(int iUsage);

private slots:
    void on_pushButton_clicked();

private:
    Ui::BurnCpu *ui;
};


#endif // MAINWINDOW_H
