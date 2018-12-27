#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "interface.h"
#include "qipaddressedit.h"
#include "qipaddressedititem.h"
#include <QList>
#include <QProcess>
#include <QCloseEvent>

namespace Ui {
class Network;
}

class Network : public QWidget
{
    Q_OBJECT
    
public:
    explicit Network(QWidget *parent = 0);
    ~Network();
    
private:
    Ui::Network *ui;
    QList<Interface*> ints;
    QProcess *proc;
    bool flag;
public slots:
    void on_sel_changed(const QString &text);
    void on_toggled();
    void on_ok_clicked();
    void refreshInterfaces();
    void readConfigs();
    void writeConfigs();
    void state(bool dhcp);
    void proc_finished();
protected:
    void closeEvent(QCloseEvent * evt);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
