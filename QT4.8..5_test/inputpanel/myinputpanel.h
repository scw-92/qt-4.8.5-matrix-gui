#ifndef MYINPUTPANEL_H
#define MYINPUTPANEL_H

#include <QtGui>
#include <QWidget>

namespace Ui {
class MyInputPanel;
}

class MyInputPanel : public QWidget
{
    Q_OBJECT
    
public:
     MyInputPanel();
     ~MyInputPanel();
     QWidget *getFocusedWidget();//获取有光标且需要输入的窗口指针

signals:
    void characterGenerated(QChar character);//字符产生，每个按键都要对应一个ASCII

protected://事件处理函数，这里只处理窗口激活事件，其它事件lfyw
    bool event(QEvent *e);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

private slots://保存上次要输入窗口的指针
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    void buttonClicked(QWidget *w);


private:
    void keyMapping();
    void setbutton(int type);

    void testAndsend(QChar chr);
       void Modifier(QChar chr);
    Ui::MyInputPanel *ui;
    QWidget *lastFocusedWidget;
    QSignalMapper signalMapper;//多信号的映射
    int caps_lock;
    int punctuation;
    bool pun_flag ;
    QPoint offset;
};

#endif // MYINPUTPANEL_H
