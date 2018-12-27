#ifndef BUZZER_H
#define BUZZER_H

#include <QWidget>

namespace Ui {
class Buzzer;
}

class Buzzer : public QWidget
{
    Q_OBJECT

public:
    explicit Buzzer(QWidget *parent = 0);
    ~Buzzer();

protected:
    void resizeEvent(QResizeEvent *);
    void moveEvent(QMoveEvent *);

private slots:
    void set_buzzer_freq(int);

    void on_slider_valueChanged(int value);

    void on_spinBox_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::Buzzer *ui;
    int fd;
};

#endif // BUZZER_H
