#ifndef PING_H
#define PING_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class Ping;
}

class Ping : public QWidget
{
    Q_OBJECT
    
public:
    explicit Ping(QWidget *parent = 0);
    ~Ping();
    
private slots:
    void on_ping_clicked();

    void on_stop_clicked();

    void on_clear_clicked();

    void result();

private:
    Ui::Ping *ui;
    QProcess *myprocess;
protected:
    void closeEvent(QCloseEvent *);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
