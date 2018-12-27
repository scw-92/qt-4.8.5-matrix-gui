#ifndef INFO_H
#define INFO_H

#include <QWidget>
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
#include <stdlib.h>
#include <stdio.h>

#include <QProcess>

namespace Ui {
class Info;
}

class Info : public QWidget
{
    Q_OBJECT
    
public:
    explicit Info(QWidget *parent = 0);
    ~Info();
    
private slots:
    void result();
    void on_pushButton_cpu_info_clicked();

    void on_pushButton_mem_info_clicked();

    void on_pushButton_storage_clicked();

private:
    Ui::Info *ui;
     QProcess *myprocess;
     void mouseMoveEvent ( QMouseEvent  * e );
};

#endif // MAINWINDOW_H
