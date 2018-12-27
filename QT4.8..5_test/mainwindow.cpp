#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 125px; }");

#ifdef __APLEX_QT_INFO__
    info = new Info();
    ui->tabWidget->addTab(info, "info");
#endif

#ifdef __APLEX_QT_LED__
    led = new Led();
    ui->tabWidget->addTab(led, "led");
#endif

#ifdef __APLEX_QT_GPIO__
    gpio = new MyGpio();
    ui->tabWidget->addTab(gpio, "gpio");
#endif

#ifdef __APLEX_QT_BUZZER__
    buzzer = new Buzzer();
    ui->tabWidget->addTab(buzzer, "buzzer");
#endif

#ifdef __APLEX_QT_BACKLIGHT__
    backlight = new Backlight();
    ui->tabWidget->addTab(backlight, "backlight");
#endif

#ifdef __APLEX_QT_EEPROM__
    eeprom = new Eeprom();
    ui->tabWidget->addTab(eeprom, "eeprom");
#endif

#ifdef __APLEX_QT_NETWORK__
    network= new Network();
    ui->tabWidget->addTab(network, "network");
#endif

#ifdef __APLEX_QT_IFCONFIG__
    aplex_ifconfig = new dpifconfig();
    ui->tabWidget->addTab(aplex_ifconfig, "ifconfig");
#endif

#ifdef __APLEX_QT_PING__
    ping= new Ping();
    ui->tabWidget->addTab(ping, "ping");
#endif

#ifdef __APLEX_QT_RTCTEST__
    rtc = new RtcTest();
    ui->tabWidget->addTab(rtc, "rtc");
#endif

#ifdef __APLEX_QT_USB__
    usb = new Usb();
    ui->tabWidget->addTab(usb, "usb");
#endif

#ifdef __APLEX_QT_SD__
    sd = new Sd();
    ui->tabWidget->addTab(sd, "SD");
#endif

#ifdef __APLEX_QT_UART__
    uart= new Uart();
    ui->tabWidget->addTab(uart, "uart");
#endif

#ifdef __APLEX_QT_WATCHDOG__
    watchdog = new Watchdog();
    ui->tabWidget->addTab(watchdog, "watchdog");
#endif

#ifdef __APLEX_QT_CANTEST__
    can = new CanTest();
    ui->tabWidget->addTab(can, "can");
#endif

#ifdef __APLEX_QT_AUDIO__
    audio= new Audio();
    ui->tabWidget->addTab(audio, "audio");
#endif

#ifdef __APLEX_QT_VERSION__
    version1 = new version();
    ui->tabWidget->addTab(version1, "version");
#endif

#ifdef __APLEX_QT_PERF__
    onoff = new OnOff();
    ui->tabWidget->addTab(onoff, "OnOff");
    if (access("/on-off-file", F_OK) == 0) {
        ui->tabWidget->setCurrentWidget(onoff);
    }

    burnCpu = new BurnCpu();
    ui->tabWidget->addTab(burnCpu, "burnCpu");
#endif
}

MainWindow::~MainWindow()
{
#ifdef __APLEX_QT_INFO__
    delete info;
#endif
#ifdef __APLEX_QT_LED__
    delete led;
#endif

#ifdef __APLEX_QT_GPIO__
    delete gpio;
#endif

#ifdef __APLEX_QT_BUZZER__
    delete buzzer;
#endif

#ifdef __APLEX_QT_BACKLIGHT__
    delete backlight;
#endif

#ifdef __APLEX_QT_EEPROM__
    delete eeprom;
#endif

#ifdef __APLEX_QT_NETWORK__
    delete network;
#endif

#ifdef __APLEX_QT_IFCONFIG__
    delete aplex_ifconfig;
#endif

#ifdef __APLEX_QT_PING__
    delete ping;
#endif

#ifdef __APLEX_QT_RTCTEST__
    delete rtc;
#endif

#ifdef __APLEX_QT_USB__
    delete usb;
#endif

#ifdef __APLEX_QT_SD__
    delete sd;
#endif

#ifdef __APLEX_QT_UART__
    delete uart;
#endif

#ifdef __APLEX_QT_WATCHDOG__
    delete watchdog;
#endif

#ifdef __APLEX_QT_CANTEST__
    delete can;
#endif

#ifdef __APLEX_QT_AUDIO__
    delete audio;
#endif

#ifdef __APLEX_QT_VERSION__
    delete version1;
#endif

#ifdef __APLEX_QT_PERF__
    delete onoff;
    delete burnCpu;
#endif

    delete ui;
}
