#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "canTest.h"
#include "ui_canTest.h"
#include <QDebug>
#include <QMessageBox>

CanTest::CanTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanTest)
{
    ui->setupUi(this);

    btg = new QButtonGroup;
    btg->addButton(ui->can0,0);
    btg->addButton(ui->can1,1);
}

CanTest::~CanTest()
{
    stopcan(btg->checkedId());
    delete ui;
}

void CanTest::msg(QString str)
{
    ui->label->append(str);
}

void CanTest::on_send_clicked()
{
    char interface[10] = "can0";
    int family = PF_CAN, type = SOCK_RAW, proto = CAN_RAW, s, ret;
    struct sockaddr_can can_addr;
    struct can_frame my_frame;
    struct ifreq my_ifr;
    std::string  str = ui->edit->text().toStdString();

    s = ::socket(family, type, proto);
    if (s < 0) {
        perror("socket");
    }

    can_addr.can_family = family;
    strcpy(my_ifr.ifr_name, interface);
    if (ioctl(s, SIOCGIFINDEX, &my_ifr)) {
        perror("ioctl");
    }
    can_addr.can_ifindex = my_ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0) {
        perror("bind");
    }

    my_frame.can_id = 0x7ff;
    strcpy((char*)my_frame.data, str.c_str());
    my_frame.can_dlc = str.length();

    my_frame.can_id &= CAN_SFF_MASK;

    ret = write(s, &my_frame, sizeof(my_frame));
    if (ret == -1) {
        perror("write");
    }

    ::close(s);
}

void CanTest::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void CanTest::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void CanTest::closeEvent(QCloseEvent *)
{
     exit(0);
}

void CanTest::startcan(int v)
{
    QString command;
    command.append("canconfig can").append(QString::number(v)).append(" bitrate ").append(baudrate).append(" ctrlmode triple-sampling on");
    qDebug() << command;
    system(command.toLocal8Bit().constData());

    if(v == 0)
    {
        system("canconfig can0 start");
    }
    else
    {
        system("canconfig can1 start");
    }

    socket =  ::socket(PF_CAN,SOCK_RAW,CAN_RAW);

    struct ifreq ifr;
    strcpy((char *)(ifr.ifr_name),v == 0 ? "can0" : "can1");
    ioctl(socket,SIOCGIFINDEX,&ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(socket,(struct sockaddr*)&addr,sizeof(addr));

    t = NULL;

    t = new Thread(socket);

    connect(t,SIGNAL(msg(QString)),this,SLOT(msg(QString)));

    t->start();
}

void CanTest::stopcan(int v)
{
    if(t)
    {
        t->stop();
        t->deleteLater();
    }

    ::close(socket);

    if(v == 0)
        system("canconfig can0 stop");
    else
        system("canconfig can1 stop");
}

void CanTest::on_start_clicked()
{
    if ( this->ui->start->text().trimmed().compare("start") == 0 ) {
        canNumber = this->btg->checkedId();
        int baudrateNumber = this->ui->baudrate->currentIndex();

        switch (baudrateNumber) {
            case 0:
                baudrate = "5000";
                break;
            case 1:
                baudrate = "10000";
                break;
            case 2:
                baudrate = "20000";
                break;
            case 3:
                baudrate = "40000";
                break;
            case 4:
                baudrate = "50000";
                break;
            case 5:
                baudrate = "80000";
                break;
            case 6:
                baudrate = "100000";
                break;
            case 7:
                baudrate = "125000";
                break;
            case 8:
                baudrate = "200000";
                break;
            case 9:
                baudrate = "250000";
                break;
            case 10:
                baudrate = "400000";
                break;
            case 11:
                baudrate = "500000";
                break;
            case 12:
                baudrate = "666000";
                break;
            case 13:
                baudrate = "800000";
                break;
            case 14:
                baudrate = "1000000";
                break;
            default:
                baudrate = "1000000";
        }
        qDebug() << "canNumber" << canNumber << "baudrate: " << baudrate << endl;

        startcan(canNumber);
        this->ui->currentBaudrate->setText( QString().append("Current Baudrate : ").append(this->ui->baudrate->currentText()) );
        this->ui->start->setText("stop");
    } else {
        stopcan(canNumber);
        this->ui->start->setText("start");
    }
}
