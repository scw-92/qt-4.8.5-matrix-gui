#include "rtcTest.h"
#include "ui_rtcTest.h"
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <stdio.h>
RtcTest::RtcTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtcTest)
{
    ui->setupUi(this);

    connect(&testTimer, SIGNAL(timeout()), this, SLOT(SotSetTime()));
    testTimer.start(1000);
    set_flag = 0;
    y_i = 0;
    m_i = 0;
    d_i = 0;
    h_i = 0;
    mi_i = 0;
    s_i = 0;
    set_id = 0;
    y = m = d = h = mi = s = 0;
}

RtcTest::~RtcTest()
{
    testTimer.stop();
    delete ui;
}

void RtcTest::SotSetTime()
{
    QDate d = QDate::currentDate();
    QTime t = QTime::currentTime();

    if (set_flag == 0)
    {
        ui->pushButton_y->setText(QString::number(d.year()));
        ui->pushButton_m->setText(QString::number(d.month()));
        ui->pushButton_d->setText(QString::number(d.day()));
        ui->pushButton_h->setText(QString::number(t.hour()));
        ui->pushButton_mi->setText(QString::number(t.minute()));
        ui->pushButton_s->setText(QString::number(t.second()));
    }
}
void RtcTest::on_pushButton_10_clicked()
{
    QString value;
    char buf[128];
    memset(buf,0,128);

    if (set_flag == 0)
    {
         set_flag = 1;

         ui->pushButton_10->setText("Set ON");
         ui->label->setText(" ");
         y = m = d = h = mi = s = 0;
         ui->pushButton_y->setText("");
         ui->pushButton_m->setText("");
         ui->pushButton_d->setText("");
         ui->pushButton_h->setText("");
         ui->pushButton_mi->setText("");
         ui->pushButton_d->setText("");
         ui->pushButton_s->setText("");
    }
    else
    {
        value = "";
        if ((m>12) || (m ==0))
        {
            value = "format error"; ;
        }
        if ((d>31) || (m ==0))
        {
            value = "format error"; ;
        }
        if ((h>23))
        {
            value = "format error"; ;
        }
        if ((mi>60) || (mi ==0))
        {
            value = "format error"; ;
        }
        if ((s>60) || (m ==0))
        {
            value = "format error"; ;
        }
        if (value.isEmpty())
        {
            set_flag = 0;
            ui->pushButton_10->setText("Set OFF");
            sprintf(buf,"date -s '%4d-%02d-%02d %02d:%02d:%02d'",y,m,d,h,mi,s);
            system(buf);
            system("hwclock -w");
            //system("/etc/init.d/save-rtc.sh");
        }
        ui->label->setText(value);
        y = m = d = h = mi = s = 0;
        ui->pushButton_y->setText("");
        ui->pushButton_m->setText("");
        ui->pushButton_d->setText("");
        ui->pushButton_h->setText("");
        ui->pushButton_mi->setText("");
        ui->pushButton_d->setText("");
        ui->pushButton_s->setText("");
    }

}
void RtcTest::on_pushButton_y_clicked()
{
    if (set_flag == 1)
    {
        set_id = YY;
        y_i  = 0;
        ui->pushButton_y->setText(" ");
        y = 0;
    }
}

void RtcTest::on_pushButton_m_clicked()
{
    if (set_flag == 1)
    {
        set_id = MO;
        m_i  = 0;
        ui->pushButton_m->setText(" ");
        m = 0;
    }
}

void RtcTest::on_pushButton_d_clicked()
{
    if (set_flag == 1)
    {
        set_id = DD;
        d_i = 0;
        ui->pushButton_d->setText(" ");
        d = 0;
    }
}

void RtcTest::on_pushButton_h_clicked()
{
    if (set_flag == 1)
    {
        set_id = HH;
        h_i = 0;
        ui->pushButton_h->setText(" ");
        h = 0;
    }
}

void RtcTest::on_pushButton_mi_clicked()
{
    if (set_flag == 1)
    {
        set_id = MI;
        mi_i = 0;
        ui->pushButton_mi->setText(" ");
        mi = 0;
    }
}

void RtcTest::on_pushButton_s_clicked()
{
    if (set_flag == 1)
    {
        set_id = SS;
        s_i = 0;
        ui->pushButton_s->setText(" ");
        s = 0;
    }
}

void RtcTest::on_pushButton_1_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 1;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 1;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 1;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 1;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 1;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 1;ui->pushButton_s->setText(QString::number(s));} break;
    }
}



void RtcTest::on_pushButton_2_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 2;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 2;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 2;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 2;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 2;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 2;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_3_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 3;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 3;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 3;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 3;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 3;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 3;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_4_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 4;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 4;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 4;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 4;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 4;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 4;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_6_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 6;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 6;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 6;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 6;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 6;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 6;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_5_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 5;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 5;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 5;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 5;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 5;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 5;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_7_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 7;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 7;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 7;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 7;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 7;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 7;ui->pushButton_s->setText(QString::number(s));} break;
    }
}

void RtcTest::on_pushButton_8_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 8;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 8;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 8;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 8;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 8;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 8;ui->pushButton_s->setText(QString::number(s));} break;
    }
}
void RtcTest::on_pushButton_9_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 9;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 9;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 9;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 9;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 9;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 9;ui->pushButton_s->setText(QString::number(s));} break;
    }
}


void RtcTest::on_pushButton_0_clicked()
{
    if (set_flag == 0)
        return;

    switch(set_id)
    {
        case YY:  if (y_i < 4)
         {   y_i++;y = y*10;y += 0;ui->pushButton_y->setText(QString::number(y));} break;
        case MO:  if (m_i < 2)
         {   m_i++;m = m*10;m += 0;ui->pushButton_m->setText(QString::number(m));} break;
        case DD:  if (d_i < 2)
         {   d_i++;d = d*10;d += 0;ui->pushButton_d->setText(QString::number(d));} break;
        case HH:  if (h_i < 2)
         {   h_i++;h = h*10;h += 0;ui->pushButton_h->setText(QString::number(h));} break;
        case MI:  if (mi_i < 2)
         {   mi_i++;mi = mi*10;mi += 0;ui->pushButton_mi->setText(QString::number(mi));} break;
        case SS:  if (s_i < 2)
         {   s_i++;s = s*10;s += 0;ui->pushButton_s->setText(QString::number(s));} break;
    }
}
