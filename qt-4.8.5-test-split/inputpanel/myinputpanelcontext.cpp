#include "myinputpanelcontext.h"
#include "myinputpanel.h"
#include <QDebug>

MyInputPanelContext::MyInputPanelContext()
{
    inputPanel = new MyInputPanel;
    connect(inputPanel, SIGNAL(characterGenerated(QChar)), SLOT(sendCharacter(QChar)));
}

//! [0]

MyInputPanelContext::~MyInputPanelContext()
{
    delete inputPanel;
}

//! [1]

bool MyInputPanelContext::filterEvent(const QEvent* event)
{   //点击输入栏时发生，软件盘弹出事件
    if (event->type() == QEvent::RequestSoftwareInputPanel) {
        updatePosition();//更新位置
        inputPanel->show();//显示
        return true;
    } else if (event->type() == QEvent::CloseSoftwareInputPanel) {
        inputPanel->hide();
        return true;
    }
    return false;
}

//! [1]

QString MyInputPanelContext::identifierName()
{
    return "MyInputPanelContext";
}

void MyInputPanelContext::reset()
{
}

bool MyInputPanelContext::isComposing() const
{
    return false;
}

QString MyInputPanelContext::language()
{
    return "en_US";
}

//! [2]

void MyInputPanelContext::sendCharacter(QChar character)
{
   // QPointer<QWidget> w = focusWidget();
    //获取输入窗口指针
     QPointer<QWidget> w = inputPanel->getFocusedWidget();

    if (!w)
        return;
    qDebug() << "send"<<endl;
    qDebug() << "character" << character << endl;

    if(character == 8)
        qDebug() << "8"  << endl;
    //发送按键值直接到输入窗口
    //QKeyEvent参数：按键类型，编码，修饰符，最后才是发送值
    QKeyEvent keyPress(QEvent::KeyPress, character.unicode(), Qt::NoModifier, QString(character));
    QApplication::sendEvent(w, &keyPress);//w为事件接收者

    if (!w)
        return;//
    //发送释放信号
    QKeyEvent keyRelease(QEvent::KeyRelease, character.unicode(), Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyRelease);
}

//! [2]

//! [3]

void MyInputPanelContext::updatePosition()
{
    QWidget *widget = focusWidget();//返回有光标的窗口部件的指针，这里是两个QLineEdit窗口部件的指针
    if (!widget)
        return;
    QCursor cursor;
    QPoint focus = cursor.pos();

   // QRect widgetRect = widget->rect();//返回窗口部件的矩形对象
    //QPoint panelPos = QPoint(widgetRect.left()+10, widgetRect.bottom() + 12);//以输入光标点处的x,y坐标，来确定输入面板的放置位置信息
    QPoint panelPos = QPoint(focus.x() + 16, focus.y() +20);//以输入光标点处的x,y坐标，来确定输入面板的放置位置信息
   // qDebug() << panelPos <<endl;
  //  panelPos = widget->mapToGlobal(panelPos);
    qDebug() << panelPos <<endl;
    inputPanel->move(panelPos);//移到设置点处
}
