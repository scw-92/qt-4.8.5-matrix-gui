#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QPushButton>
#include <QThread>
#include <QTime>


namespace Ui {
class MainWindow;
}

class Parser : public QObject
{
    Q_OBJECT

signals:
    void parserSignal(int iUsage);

public:
    void runParser()
    {
        QProcess p;
        int prev_total = 0;
        int prev_idle = 0;
        while(1)
        {
            p.start("sh", QStringList() << "-c" << "cat /proc/stat | head -n1 | sed 's/cpu //'");
            p.waitForFinished(-1);

            QString p_stdout = p.readAllStandardOutput();

            QStringList list1 = p_stdout.split(" ");

            //qDebug() << p_stdout;

            int user = list1[1].toInt();
            int system = list1[2].toInt();
            int nice = list1[3].toInt();
            int idle = list1[4].toInt();
            int wait = list1[5].toInt();
            int irq = list1[6].toInt();
            int srq = list1[7].toInt();
            int zero = list1[8].toInt();

            int total=( user + system + nice + idle + wait + irq + srq + zero);

            int diff_idle = idle-prev_idle;

            int diff_total = (total-prev_total);

            int usage=((( 1000 * ( (diff_total - diff_idle)) / diff_total+5) ) / 10);

            emit parserSignal(usage);

            prev_total = total;
            prev_idle = idle;
            //usleep (1);
            QTime t;
            t.start();
            while(t.elapsed()<1000);
        }
    }
};

//bool runFlag = true;

class HeatMachineThread : public QThread
{
private:
    void run()
    {
        int i = 0;
        //while ( runFlag )
        while ( true )
            i++;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    HeatMachineThread *heatMachineThead;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void usageSlot(int iUsage);
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
