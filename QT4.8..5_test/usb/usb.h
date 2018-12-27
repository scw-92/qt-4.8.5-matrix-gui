#ifndef USB_H
#define USB_H

#include <QWidget>
#include <QFileSystemModel>

namespace Ui {
class Usb;
}

class Usb : public QWidget
{
    Q_OBJECT
    
public:
    explicit Usb(QWidget *parent = 0);
    ~Usb();
    
private slots:
    void on_button_mount_clicked();

    void on_button_umount_clicked();

private:
    Ui::Usb *ui;
    QFileSystemModel model;
};

#endif // MAINWINDOW_H
