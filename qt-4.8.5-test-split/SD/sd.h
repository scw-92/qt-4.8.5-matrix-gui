#ifndef SD_H
#define SD_H

#include <QWidget>
#include <QFileSystemModel>

namespace Ui {
class Sd;
}

class Sd : public QWidget
{
    Q_OBJECT

public:
    explicit Sd(QWidget *parent = 0);
    ~Sd();

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void on_detectButton_clicked();

    void on_umountButton_clicked();

private:
    QFileSystemModel model;
    Ui::Sd *ui;
};

#endif // MAINWINDOW_H
