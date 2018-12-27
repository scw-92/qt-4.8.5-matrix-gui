#include "myinputpanel.h"
#include "ui_myinputpanelform.h"

MyInputPanel::MyInputPanel()
    : QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint),  //工具窗口
    //lastFocusedWidget(0),
    ui(new Ui::MyInputPanel)
{
    lastFocusedWidget = 0;
    caps_lock = 0;
    punctuation = 0;
    pun_flag = false;
    ui->setupUi(this);

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
    keyMapping();

}
MyInputPanel::~MyInputPanel()
{
//  disconnect(signalMapper, 0, 0, 0);
    disconnect(qApp, 0, 0, 0);
    delete ui;
}

bool MyInputPanel::event(QEvent *e)
{
    switch (e->type()) {
//! [1]
    case QEvent::WindowActivate:
        if (lastFocusedWidget)//激活最后一次有光标的窗口
            lastFocusedWidget->activateWindow();
        break;
//! [1]
    default:
        break;
    }

    return QWidget::event(e);//其它事件默认，必须要有
}

//! [2]

void MyInputPanel::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{   //如果非零，且不是输入面板inputpanel对象的子部件指针就保存
    //这里只保存需要输入窗口中的指针
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
        lastFocusedWidget = newFocus;
        qDebug() <<"FocusWidget Changed" << endl;//
    }
}

void MyInputPanel::buttonClicked(QWidget *w)
{
    //property函数返回属性为lylbuttonValue的对应值，这里为每个按键对应的ASCII
    //qvariant_cast(T)(value)将输入值value转换为T类型
    QChar chr = qvariant_cast<QChar>(w->property("lylbuttonValue"));
    //unsigned short temp = (unsigned short)(chr);
    //qDebug() << "temp" << temp <<endl;
    testAndsend(chr);
}

//返回主界面焦点处窗口指针
QWidget * MyInputPanel::getFocusedWidget()
{
    return lastFocusedWidget;
}

void MyInputPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)//按下时调用buttons函数来判断按键
    {
        QCursor cursor;
        cursor.setShape(Qt::SizeAllCursor);
        QApplication::setOverrideCursor(cursor); //暂时使用这种指针
        offset = event->globalPos() - pos();//用桌面全局坐标减去窗口坐标，得到需要移动坐标
    }
}

void MyInputPanel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)//移动中只能用buttons函数
    {
        QPoint newpoint;
        newpoint = event->globalPos() - offset;  //减去差值得到新位置
        move(newpoint);  //移动到新位置
    }
}

void MyInputPanel::mouseReleaseEvent(QMouseEvent *)
{
    QApplication::restoreOverrideCursor();  //恢复指针形状
}

void MyInputPanel::setbutton(int type)
{
    switch(type)
    {
        case 0:
        ui->panelButton_a->setText("a");
        ui->panelButton_b->setText("b");
        ui->panelButton_c->setText("c");
        ui->panelButton_d->setText("d");
        ui->panelButton_e->setText("e");
        ui->panelButton_f->setText("f");
        ui->panelButton_g->setText("g");
        ui->panelButton_h->setText("h");
        ui->panelButton_i->setText("i");
        ui->panelButton_j->setText("j");
        ui->panelButton_k->setText("k");
        ui->panelButton_l->setText("l");
        ui->panelButton_m->setText("m");
        ui->panelButton_n->setText("n");
        ui->panelButton_o->setText("o");
        ui->panelButton_p->setText("p");
        ui->panelButton_q->setText("q");
        ui->panelButton_r->setText("r");
        ui->panelButton_s->setText("s");
        ui->panelButton_t->setText("t");
        ui->panelButton_u->setText("u");
        ui->panelButton_v->setText("v");
        ui->panelButton_w->setText("w");
        ui->panelButton_x->setText("x");
        ui->panelButton_y->setText("y");
        ui->panelButton_z->setText("z");
        break;

        case 1:
        ui->panelButton_a->setText("A");
        ui->panelButton_b->setText("B");
        ui->panelButton_c->setText("C");
        ui->panelButton_d->setText("D");
        ui->panelButton_e->setText("E");
        ui->panelButton_f->setText("F");
        ui->panelButton_g->setText("G");
        ui->panelButton_h->setText("H");
        ui->panelButton_i->setText("I");
        ui->panelButton_j->setText("J");
        ui->panelButton_k->setText("K");
        ui->panelButton_l->setText("L");
        ui->panelButton_m->setText("M");
        ui->panelButton_n->setText("N");
        ui->panelButton_o->setText("O");
        ui->panelButton_p->setText("P");
        ui->panelButton_q->setText("Q");
        ui->panelButton_r->setText("R");
        ui->panelButton_s->setText("S");
        ui->panelButton_t->setText("T");
        ui->panelButton_u->setText("U");
        ui->panelButton_v->setText("V");
        ui->panelButton_w->setText("W");
        ui->panelButton_x->setText("X");
        ui->panelButton_y->setText("Y");
        ui->panelButton_z->setText("Z");
        break;

        case 2:
        ui->panelButton_a->setText("!");
        ui->panelButton_b->setText("''");
        ui->panelButton_c->setText("#");
        ui->panelButton_d->setText("$");
        ui->panelButton_e->setText("%");

        ui->panelButton_f->setText("(");
        ui->panelButton_g->setText(")");
        ui->panelButton_h->setText("*");
        ui->panelButton_i->setText("+");
        ui->panelButton_j->setText(",");
        ui->panelButton_k->setText("-");
        ui->panelButton_l->setText(".");
        ui->panelButton_m->setText("/");

        ui->panelButton_n->setText(":");
        ui->panelButton_o->setText(";");
        ui->panelButton_p->setText("<");
        ui->panelButton_q->setText("=");
        ui->panelButton_r->setText(">");
        ui->panelButton_s->setText("?");
        ui->panelButton_t->setText("@");

        ui->panelButton_u->setText("_");
        ui->panelButton_v->setText("`");

        ui->panelButton_w->setText("{");
        ui->panelButton_x->setText("|");
        ui->panelButton_y->setText("}");
        ui->panelButton_z->setText("~");
        break;
    }
}
void MyInputPanel::keyMapping()
{
    signalMapper.setMapping(ui->panelButton_0, ui->panelButton_0);
    signalMapper.setMapping(ui->panelButton_1, ui->panelButton_1);
    signalMapper.setMapping(ui->panelButton_2, ui->panelButton_2);
    signalMapper.setMapping(ui->panelButton_3, ui->panelButton_3);
    signalMapper.setMapping(ui->panelButton_4, ui->panelButton_4);
    signalMapper.setMapping(ui->panelButton_5, ui->panelButton_5);
    signalMapper.setMapping(ui->panelButton_6, ui->panelButton_6);
    signalMapper.setMapping(ui->panelButton_7, ui->panelButton_7);
    signalMapper.setMapping(ui->panelButton_8, ui->panelButton_8);
    signalMapper.setMapping(ui->panelButton_9, ui->panelButton_9);

    signalMapper.setMapping(ui->panelButton_a, ui->panelButton_a);
    signalMapper.setMapping(ui->panelButton_b, ui->panelButton_b);
    signalMapper.setMapping(ui->panelButton_c, ui->panelButton_c);
    signalMapper.setMapping(ui->panelButton_d, ui->panelButton_d);
    signalMapper.setMapping(ui->panelButton_e, ui->panelButton_e);
    signalMapper.setMapping(ui->panelButton_f, ui->panelButton_f);
    signalMapper.setMapping(ui->panelButton_g, ui->panelButton_g);
    signalMapper.setMapping(ui->panelButton_h, ui->panelButton_h);
    signalMapper.setMapping(ui->panelButton_i, ui->panelButton_i);
    signalMapper.setMapping(ui->panelButton_j, ui->panelButton_j);
    signalMapper.setMapping(ui->panelButton_k, ui->panelButton_k);
    signalMapper.setMapping(ui->panelButton_l, ui->panelButton_l);
    signalMapper.setMapping(ui->panelButton_m, ui->panelButton_m);
    signalMapper.setMapping(ui->panelButton_n, ui->panelButton_n);
    signalMapper.setMapping(ui->panelButton_o, ui->panelButton_o);
    signalMapper.setMapping(ui->panelButton_p, ui->panelButton_p);
    signalMapper.setMapping(ui->panelButton_q, ui->panelButton_q);
    signalMapper.setMapping(ui->panelButton_r, ui->panelButton_r);
    signalMapper.setMapping(ui->panelButton_s, ui->panelButton_s);
    signalMapper.setMapping(ui->panelButton_t, ui->panelButton_t);
    signalMapper.setMapping(ui->panelButton_u, ui->panelButton_u);
    signalMapper.setMapping(ui->panelButton_v, ui->panelButton_v);
    signalMapper.setMapping(ui->panelButton_w, ui->panelButton_w);
    signalMapper.setMapping(ui->panelButton_x, ui->panelButton_x);
    signalMapper.setMapping(ui->panelButton_y, ui->panelButton_y);
    signalMapper.setMapping(ui->panelButton_z, ui->panelButton_z);

    signalMapper.setMapping(ui->panelButton_Space, ui->panelButton_Space);
    signalMapper.setMapping(ui->panelButton_BS, ui->panelButton_BS);
    signalMapper.setMapping(ui->panelButton_Enter, ui->panelButton_Enter);
    signalMapper.setMapping(ui->panelButton_Caps, ui->panelButton_Caps);
    signalMapper.setMapping(ui->panelButton_pun, ui->panelButton_pun);

    //再将各按键对象和map函数建立信号与槽的关系
    connect(ui->panelButton_0, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_1, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_2, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_3, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_4, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_5, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_6, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_7, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_8, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_9, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));

    connect(ui->panelButton_a, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_b, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_c, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_d, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_e, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_f, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_g, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_h, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_i, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_j, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_k, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_l, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_m, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_n, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_o, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_p, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_q, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_r, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_s, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_t, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_u, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_v, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_w, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_x, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_y, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_z, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));

    connect(ui->panelButton_Space, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_BS, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_Enter, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_Caps, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(ui->panelButton_pun, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));

    connect(&signalMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(buttonClicked(QWidget*)));
}

void MyInputPanel::testAndsend(QChar chr)
{
    if(chr < 32)
       Modifier(chr);
    else if((chr >= 'a' && chr <= 'z') )//字母
    {
        char temp_pun = chr.toAscii(); //转换成ASCII码，注意QChar是16位的
        char temp_caps = temp_pun;
        if(punctuation == 1)
        {
            if(temp_pun >='a' && temp_pun <= 'e')  //转换成标点符号
                temp_pun = temp_pun - 64;
            else if(temp_pun >='f' && temp_pun <= 'm')
                temp_pun = temp_pun - 62;
            else if(temp_pun >='n' && temp_pun <= 't')
                temp_pun = temp_pun - 52;
            else if(temp_pun >='u' && temp_pun <= 'v')
                temp_pun = temp_pun - 22;
            else if(temp_pun >='w' && temp_pun <= 'z')
                temp_pun = temp_pun + 4;

            QChar pun(temp_pun);//再由char参数类型的构造函数，转换回QChar
            chr = pun;
            qDebug() << "pun" << pun <<endl;
            qDebug() << "temp_pun" << temp_pun <<endl;
            emit characterGenerated(chr);
        }
        else
        {
            if(caps_lock == 1)
                temp_caps -= 32;//由于QChar不能进行加减，所以只能先转换成ASCII的char来大小写运算
            QChar str(temp_caps);//再由char参数类型的构造函数，转换回QChar
            chr = str;
            qDebug() << "chr" << chr <<endl;
            emit characterGenerated(chr);
        }

    }

    else
     emit characterGenerated(chr);//将按键的ASCII码发送出去
}
void MyInputPanel::Modifier(QChar chr)
{
   if(chr == 8)                   //退格
   {
       QKeyEvent key_BS(QEvent::KeyPress,Qt::Key_Backspace, Qt::NoModifier);
       QApplication::sendEvent(lastFocusedWidget, &key_BS);//w为事件接收者
   }
   else if (chr == 13)           //回车
   {
       QKeyEvent key_Enter(QEvent::KeyPress,Qt::Key_Return, Qt::NoModifier);
       QApplication::sendEvent(lastFocusedWidget, &key_Enter);//w为事件接收者
   }
   else if(chr == 20)           //大写
   {
       caps_lock ++;
       if(caps_lock == 2)
           caps_lock = 0;
       setbutton(caps_lock);
       if(punctuation == 1)//如果发现标点没关，关闭标点
           punctuation = 0;
       qDebug() << "caps_lock=" << caps_lock <<endl;
   }
   else if(chr == 19)           //标点
   {
       punctuation ++;
       if(punctuation == 2)
           punctuation = 0;
       if(punctuation == 1)
           setbutton(2);
       else
           setbutton(caps_lock);
       qDebug() << "punctuation=" << punctuation <<endl;
   }
}
