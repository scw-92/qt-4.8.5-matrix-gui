#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QProcess>
#include <QTime>
#include <QDebug>


class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:
    void parserSignal(int iUsage);

public:

    int prev_total;
    int prev_idle;
public slots:
    void runParser()
    {
        QProcess p;
//    	int prev_total = 0;
//    	int prev_idle = 0;
//        while(1)
//        {
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
//            QTime t;
//            t.start();
//            while(t.elapsed()<1000);
//        }
            p.close();
    }
};

#endif // PARSER_H
