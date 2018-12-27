#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <QWidget>

namespace Ui {
class Backlight;
}

class Backlight : public QWidget
{
    Q_OBJECT
    
public:
    explicit Backlight(QWidget *parent = 0);
    ~Backlight();
    
private:
    Ui::Backlight *ui;
    int bl_fd;

private slots:
    void on_slider_valueChanged(int value);

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);

};

#endif // MAINWINDOW_H
