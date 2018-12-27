#ifndef MYGPIO_H
#define MYGPIO_H

#include <stdlib.h>
#include <stdio.h>
#include <QPushButton>
#include <qobject.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <QWidget>
#include <QTimer>

namespace Ui {
class MyGpio;
}

class MyGpio : public QWidget
{
    Q_OBJECT
    
public:
    explicit MyGpio(QWidget *parent = 0);
    ~MyGpio();
    
public slots:
    void SotSetTime();
private slots:
    void on_pushButton_O_1_clicked();

    void on_pushButton_O_2_clicked();

    void on_pushButton_O_3_clicked();

    void on_pushButton_O_4_clicked();

private:
    Ui::MyGpio *ui;
    int io_out_1;
    int io_out_2;
    int io_out_3;
    int io_out_4;
    int io_in_1;
    int io_in_2;
    int io_in_3;
    int io_in_4;

    QTimer testTimer ;
};

#endif 
