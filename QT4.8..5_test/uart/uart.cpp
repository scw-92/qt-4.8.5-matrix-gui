#include "uart.h"
#include "ui_uart.h"

Uart::Uart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Uart)
{
 //   int re;
    ui->setupUi(this);

    connect(&testTimer,SIGNAL(timeout()),this,SLOT(SotSetTime()));

    autosend_flag = 0;
    auto_send_flag = 0;
    receive_flag = 1;
    count = 0;
    receive_flag = 1;

    testTimer.start(1);
}

Uart::~Uart()
{
    testTimer.stop();
    ::close(fd);
    delete ui;
}


int Uart::open_uart_port(int fd,int comport)
{
    if (comport==1)
    {
        fd = open( "/dev/ttyO1", O_RDWR|O_NOCTTY|O_NDELAY);
        if (-1 == fd)
        {
            ui->label->setText("open uart port error");
            return(-1);
        }
        else
        {
            printf("open ttyO1 .....\n");
        }
    }
#if 0
        else if(comport==2)
        {    fd = open( "/dev/ttyO1", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                ui->label->setText("open uart port error");
                return(-1);
            }
            else
            {
                printf("open ttyO1 .....\n");
            }
        }
        else if (comport==3)
        {
            fd = open( "/dev/ttyO2", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                ui->label->setText("open uart port error");
                return(-1);
            }
            else
            {
                printf("open ttyO2 .....\n");
            }
        }

        else if (comport==4)
        {
            fd = open( "/dev/ttyO4", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                ui->label->setText("open uart port error");
                return(-1);
            }
            else
            {
                printf("open ttyO4 .....\n");
            }
        }
#endif

    if(fcntl(fd, F_SETFL, 0)<0)
    {
        printf("fcntl failed!\n");
    }
    else
    {
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
    }
    //判断便准输入是否是一个终端的设备
    if(isatty(STDIN_FILENO)==0)
    {
        printf("standard input is not a terminal device\n");
    }
    else
    {
        printf("isatty success!\n");
    }
    printf("fd-open=%d\n",fd);
    return fd;
}
int Uart::set_uart_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{

    struct termios newtio,oldtio;
       if  ( tcgetattr( fd,&oldtio)  !=  0)
       {
           perror("SetupSerial 1");
           return -1;
       }
       bzero( &newtio, sizeof( newtio ) );
       newtio.c_cflag  |=  CLOCAL | CREAD;
       newtio.c_cflag &= ~CSIZE;

       switch( nBits )
       {
       case 7:
           newtio.c_cflag |= CS7;
           break;
       case 8:
           newtio.c_cflag |= CS8;
           break;
       }

       switch( nBits )
          {
          case 7:
              newtio.c_cflag |= CS7;
              break;
          case 8:
              newtio.c_cflag |= CS8;
              break;
          }

          switch( nEvent )
          {
          case 'O':                     //奇校验
              newtio.c_cflag |= PARENB;
              newtio.c_cflag |= PARODD;
              newtio.c_iflag |= (INPCK | ISTRIP);
              break;
          case 'E':                     //偶校验
              newtio.c_iflag |= (INPCK | ISTRIP);
              newtio.c_cflag |= PARENB;
              newtio.c_cflag &= ~PARODD;
              break;
          case 'N':                    //无校验
              newtio.c_cflag &= ~PARENB;
              break;
      }


          switch( nSpeed )
              {
          case 300:
              cfsetispeed(&newtio, B300);   //设置输入波特率
              cfsetospeed(&newtio, B300);   //设置输出波特率
              break;
          case 600:
              cfsetispeed(&newtio, B600);
              cfsetospeed(&newtio, B600);
              break;

              case 1200:
                  cfsetispeed(&newtio, B1200);
                  cfsetospeed(&newtio, B1200);
                  break;
              case 2400:
                  cfsetispeed(&newtio, B2400);
                  cfsetospeed(&newtio, B2400);
                  break;
              case 4800:
                  cfsetispeed(&newtio, B4800);
                  cfsetospeed(&newtio, B4800);
                  break;
              case 9600:
                  cfsetispeed(&newtio, B9600);
                  cfsetospeed(&newtio, B9600);
                  break;
              case 19200:
                  cfsetispeed(&newtio, B19200);
                  cfsetospeed(&newtio, B19200);
                  break;
              case 115200:
                  cfsetispeed(&newtio, B115200);
                  cfsetospeed(&newtio, B115200);
                  break;
              default:
                  cfsetispeed(&newtio, B9600);
                  cfsetospeed(&newtio, B9600);
                  break;
      }
          if( nStop == 1 )
          {
              newtio.c_cflag &=  ~CSTOPB;
          }
          else if ( nStop == 2 )
          {
              newtio.c_cflag |=  CSTOPB;
          }
          newtio.c_cc[VTIME]  = 0;
          newtio.c_cc[VMIN] = 0;
          tcflush(fd,TCIFLUSH);
          if((tcsetattr(fd,TCSANOW,&newtio))!=0)
          {
              perror("com set error");
              return -1;
          }
          printf("set done!\n");
          return 0;
}
//发送
void Uart::on_pushButton_send_clicked()
{
//    int i;

    if (fd <=0)
    {
        value = "open device error!";
        ui->label->setText(value);
        return ;
    }

    ui->label->setText("0123456789");
    write(fd,"0123456789\r\n",12);
}



//接收
void Uart::SotSetTime()
{
     int i,re;

    if (receive_flag )
    {
        re = read(fd,buffer,17);
        if (re <= 0)
            return;
         value = "";
        for (i=0;i < re;i++)
        {

            //value += QString::number(buffer[i],16) + " ";
            value.append(buffer[i]);
        }
         ui->textEdit->append(value);
    }
}
//清除接受框的内容
void Uart::on_pushButton_receive_2_clicked()
{
    value = "";
    ui->textEdit->setText(value);
}

#define SERIAL_LOOP     55
#define SERIAL_485      56
#define SERIAL_232      57
#define SERIAL_422      58


void Uart::on_pushButton_open_clicked()
{
    static int cli_flag = 0;
    int re;
    int tmp;
    int comport = 0,baudrate = 0,nbit = 0, nstop = 0;
    char parity = 'N';
    //串口的端口号
    tmp = ui->portNameComboBox->currentIndex();
    switch(tmp)
    {
        case 0: comport = 1; break;
        //case 1: comport = 2; break;
        //case 2: comport = 3; break;
        //case 3: comport = 4; break;
    }

    //波特率
    tmp = ui->baudRateComboBox->currentIndex();
    switch(tmp)
    {

        case 0: baudrate = 1200; break;
        case 1: baudrate = 2400; break;
        case 2: baudrate = 4800; break;
        case 3: baudrate = 9600; break;
        case 4: baudrate = 19200; break;
        case 5: baudrate = 115200; break;
    }
    //数据位
    tmp = ui->dataBitsComboBox->currentIndex();
    switch(tmp)
    {
        case 0: nbit = 8; break;
        case 1: nbit = 8; break;
    }
    //停止位
    tmp = ui->stopBitsComboBox->currentIndex();
    switch(tmp)
    {
        case 0: nstop = 1; break;
        case 1: nstop = 2; break;
    }
    //校验位
    tmp = ui->parityComboBox->currentIndex();
    switch(tmp)
    {
       case 0 : parity = 'N';break;
       case 1 : parity = 'O';break;
       case 2 : parity = 'E';break;
    }

    if (cli_flag == 0)
    {
        if((fd=open_uart_port(fd,comport))<0)
        {
            fd  = 0;
            return;
        }
        re = set_uart_opt(fd,baudrate,nbit,parity,nstop);
        if (re < 0 )
        {
            ::close(fd);
            fd = 0;
        }
        else
        {
              cli_flag = 1;
              value = "close";
              ui->pushButton_open->setText(value);
        }

    }
    else
    {
        ::close(fd);
        cli_flag = 0;
        value = "open";
        ui->pushButton_open->setText(value);
    }

}
#define SERIAL_LOOP     55
#define SERIAL_485      56
#define SERIAL_232      57
#define SERIAL_422      58

#define SS_FNAME    "/dev/serial_ctl"


void Uart::on_pushButton_loop_clicked()
{
    int pf;
     char tmp =SERIAL_LOOP;
     pf = open( SS_FNAME, O_RDWR);
     write(pf,&tmp,1);
     ::close(pf);

}


void Uart::on_pushButton_232_clicked()
{
    int pf;
    char tmp =SERIAL_232;
    pf = open( SS_FNAME, O_RDWR);
    write(pf,&tmp,1);
    ::close(pf);

}

void Uart::on_pushButton_485_clicked()
{
    int pf;
    char tmp = SERIAL_485;
    pf = open( SS_FNAME, O_RDWR);
    write(pf,&tmp,1);
    ::close(pf);

}

void Uart::on_pushButton_422_clicked()
{
    int pf;
    char tmp =SERIAL_422;
    pf = open( SS_FNAME, O_RDWR);
    write(pf,&tmp,1);
    ::close(pf);

}
