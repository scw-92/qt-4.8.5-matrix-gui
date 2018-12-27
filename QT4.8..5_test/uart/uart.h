#ifndef UART_H
#define UART_H

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
#include <linux/spi/spidev.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <QTimer>
#include <QWidget>

namespace Ui {
class Uart;
}

class Uart : public QWidget
{
    Q_OBJECT
    
public:
    explicit Uart(QWidget *parent = 0);
    int open_uart_port(int fd,int comport);
    int set_uart_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
    ~Uart();
public slots:
    void SotSetTime();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_receive_2_clicked();

    void on_pushButton_open_clicked();



    void on_pushButton_loop_clicked();

    void on_pushButton_232_clicked();

    void on_pushButton_485_clicked();

    void on_pushButton_422_clicked();

private:
    Ui::Uart *ui;
    int fd;
    int autosend_flag;
    int count;
    int auto_send_flag;
    int receive_flag;
    char buffer[17];
    QTimer testTimer ;

    QString value;
};

#endif // UART_H
