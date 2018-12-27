#ifndef LED_H
#define LED_H

#include <QWidget>

namespace Ui {
class Led;
}

class Led : public QWidget
{
    Q_OBJECT

public:
    explicit Led(QWidget *parent = 0);
    ~Led();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Led *ui;
};

#endif // LED_H
