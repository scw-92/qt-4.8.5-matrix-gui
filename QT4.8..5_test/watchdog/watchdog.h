#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QWidget>
#include <QBasicTimer>

namespace Ui {
class Watchdog;
}

class Watchdog : public QWidget
{
    Q_OBJECT
    
public:
    explicit Watchdog(QWidget *parent = 0);
    ~Watchdog();
    
protected:
    void timerEvent(QTimerEvent *);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Watchdog *ui;
    QBasicTimer timer;
    int fd;
    int times;
};

#endif // MAINWINDOW_H
