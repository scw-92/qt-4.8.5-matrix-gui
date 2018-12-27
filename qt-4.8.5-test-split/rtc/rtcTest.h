#ifndef RTCTEST_H
#define RTCTEST_H

#define YY  1
#define MO  2
#define DD  3
#define HH  4
#define MI  5
#define SS  6


#include <QWidget>
#include <QTimer>

namespace Ui {
class RtcTest;
}

class RtcTest : public QWidget
{
    Q_OBJECT
    
public:
    explicit RtcTest(QWidget *parent = 0);
    ~RtcTest();
    private slots:
    void SotSetTime();
    
    void on_pushButton_y_clicked();

    void on_pushButton_m_clicked();

    void on_pushButton_d_clicked();

    void on_pushButton_h_clicked();

    void on_pushButton_mi_clicked();

    void on_pushButton_s_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_0_clicked();

private:
    Ui::RtcTest *ui;
    QTimer testTimer ;
    int set_flag;
    int set_id;

    int y_i;
    int m_i;
    int d_i;
    int h_i;
    int mi_i;
    int s_i;

    int y,m,d,h,mi,s;
};

#endif // MAINWINDOW_H
